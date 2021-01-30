var qvs = {
    app: null,
    enabled: typeof(qt) != typeof(undefined),
    template: null,
    selectedBlock: null,
    init: function() {
        if (qvs.enabled) {
            qvs.initWebChannel();
        }
    },
    initWebChannel: function() {
		new QWebChannel(qt.webChannelTransport, function(channel) {
            qvs.app = channel.objects.app;
            qvs.app.dataChanged.connect(function (arg) {
                qvs.app.debug(qvs.format("blockly recv data={0}", arg));
                var message = JSON.parse(arg);

                if (message != null) {
                    switch (message.cmd) {
                        case "getOpenFileName":
                            if (typeof(qvs.selectedBlock.contextMenu.setOpenFileName) == "function") {
                                qvs.selectedBlock.contextMenu.setOpenFileName(qvs.selectedBlock, message.filename);
                            }
                            else {
                                qvs.printNotImplemented("setOpenFileName");
                            }
                            break;
                    }
                }
            });
			qvs.app.debug("Web channel setup completed.");
        });
    },
    format: function(src) {
        if (arguments.length == 0) {
            return null;
        }
        var args = Array.prototype.slice.call(arguments, 1);
        return src.replace(/\{(\d+)\}/g, function(m, i) {
            return args[i];
        });
    },
    replace: function(beforeName, beforeStr, afterStr) {
        var arr = beforeName.split(beforeStr);
        var afterName = '';
        for(var i = 0; i < arr.length; i++){
            afterName += arr[i] + afterStr;
        }
        afterName = afterName.substring(0, afterName.length - 1);
        return afterName;
    },
    unifySeparator: function dd(path) {
        return qvs.replace(path, '\\', '/');
    },
    debug: function(msg) {
        if (qvs.enabled) {
            qvs.app.debug(msg);
        }
        else {
            console.log(msg);
        }
    },
    code: function() {
        var code = Blockly.Python.workspaceToCode(Code.workspace);

        if (qvs.template != null) {
            code = qvs.format(qvs.template, code);
        }
        return code;
    },
    updateCode: function() {
        if (qvs.enabled) {
            qvs.app.updateCode(qvs.code());
        }
    },
    getFileExtension: function (filePath) {
        var startIndex = filePath.lastIndexOf(".");
        if(startIndex != -1) {
            return filePath.substring(startIndex + 1, filePath.length).toLowerCase();
        }
        else return "";
    },
    getOpenFileName: function(caption, filter, type = '') {
        if (qvs.enabled) {
            qvs.app.getOpenFileName(JSON.stringify({
                caption: caption,
                filter: filter,
                type: type,
            }));
        }
        else {
            qvs.printNotImplemented("getOpenFileName");
        }
    },
    requestOpenFileName: function(block) {
        if (Blockly.selected == null) {
            qvs.selectedBlock = block.parentBlock_;
          }
          else {
            qvs.selectedBlock = Blockly.selected;
          }
          qvs.getOpenFileName(qvs.selectedBlock.contextMenu.caption || "", qvs.selectedBlock.contextMenu.filter || "", qvs.selectedBlock.type || "");
    },
    printNotImplemented: function(funcName) {
        qvs.debug(qvs.format("Function of '{0}' is not implemented.", funcName));
    },
    openUrl: function(url) {
        if (qvs.enabled) {
            qvs.app.openUrl(url);
        }
        else {
            window.open(url);
        }
    },
}

document.write('<script src="template.js"></script>\n');
if (qvs.enabled) {
    document.write('<script src="qrc:///qtwebchannel/qwebchannel.js"></script>\n');
}
else {
    console.log("Script Blockly started without qt engine, so some functions are invalid.");
}

window.qvs = qvs;
window.onload = function() {
    qvs.init();
}
