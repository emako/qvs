///////////////////////////////////////////////////////////////////////////
/// Overrides Field
///////////////////////////////////////////////////////////////////////////
Blockly.WorkspaceSvg.prototype.onMouseWheel_ = function(e) {
	// Don't scroll or zoom anything if drag is in progress.
	if (Blockly.Gesture.inProgress()) {
		e.preventDefault();
		e.stopPropagation();
		return;
	}
	var canWheelZoom = this.options.zoomOptions && this.options.zoomOptions.wheel;
	var canWheelMove = this.options.moveOptions && this.options.moveOptions.wheel;
	if (!canWheelZoom && !canWheelMove) {
		return;
	}

	var scrollDelta = Blockly.utils.getScrollDeltaPixels(e);
	if (canWheelZoom && (e.ctrlKey || !canWheelMove) && false /* Disable zoom using mouse wheel event. */) {
		// Zoom.
		// The vertical scroll distance that corresponds to a click of a zoom
		// button.
		var PIXELS_PER_ZOOM_STEP = 50;
		var delta = -scrollDelta.y / PIXELS_PER_ZOOM_STEP;
		var position = Blockly.utils.mouseToSvg(e, this.getParentSvg(),
			this.getInverseScreenCTM());
		this.zoom(position.x, position.y, delta);
	} else {
		// Scroll.
		var x = this.scrollX - scrollDelta.x;
		var y = this.scrollY - scrollDelta.y;

		if (e.shiftKey && !scrollDelta.x) {
		// Scroll horizontally (based on vertical scroll delta).
		// This is needed as for some browser/system combinations which do not
		// set deltaX.
		x = this.scrollX - scrollDelta.y;
		y = this.scrollY; // Don't scroll vertically
		}
		this.scroll(x, y);
	}
	e.preventDefault();
};

Blockly.BlockSvg.prototype.showContextMenu = function(e) {
	var menuOptions = this.generateContextMenu();
	
	/// Override code start.
	console.log(Blockly.Python[this.type](this));

	if (typeof(this.contextMenu.createContextMenu) == "function") {
		this.contextMenu.createContextMenu(menuOptions);
	}

	if (this.type == 'open') {
		menuOptions.forEach(menuOption => {
			if (menuOption.text == Blockly.Msg["ENABLE_BLOCK"]) {
				menuOption.enabled = qvs.enabled;
			}
		});
	}
	/// Override code end.

	if (menuOptions && menuOptions.length) {
		Blockly.ContextMenu.show(e, menuOptions, this.RTL);
		Blockly.ContextMenu.currentBlock = this;
	}
};

Blockly.BlockSvg.prototype.onMouseDown_ = function(e) {
	/// Override code start.
	if (e.button == 0 && this.type == 'open') {
		Blockly.selected = null;
		qvs.requestOpenFileName(this);
		e.cancelBubble = true;
		return;
	}
	/// Override code end.
	
	var gesture = this.workspace && this.workspace.getGesture(e);
	
	if (gesture) {
		gesture.handleBlockStart(e, this);
	}
};

Blockly.BlockSvg.prototype.showHelp = function() {
	var url = (typeof this.helpUrl == 'function') ? this.helpUrl() : this.helpUrl;
	if (url) {
		/// Override code start.
		qvs.openUrl(url);
		/// Override code end.
	}
};

Blockly.FieldDropdown.prototype.trimOptions_ = function() {
	var options = this.menuGenerator_;
	if (!Array.isArray(options)) {
		return;
	}
	var hasImages = false;

	// Localize label text and image alt text.
	for (var i = 0; i < options.length; i++) {
		var label = options[i][0];
		if (typeof label == 'string') {
			options[i][0] = Blockly.utils.replaceMessageReferences(label);
		} else {
			if (label.alt != null) {
				options[i][0].alt = Blockly.utils.replaceMessageReferences(label.alt);
			}
			hasImages = true;
		}
	}
	if (hasImages || options.length < 2) {
		return;  // Do nothing if too few items or at least one label is an image.
	}
	var strings = [];
	for (var i = 0; i < options.length; i++) {
		strings.push(options[i][0]);
	}
	var shortest = Blockly.utils.string.shortestStringLength(strings);
	var prefixLength = Blockly.utils.string.commonWordPrefix(strings, shortest);
	var suffixLength = Blockly.utils.string.commonWordSuffix(strings, shortest);
	if (!prefixLength && !suffixLength) {
		return;
	}

	/// Override code start.
	// Disable dropdown trimed to be labels.
	prefixLength = 0;
	suffixLength = 0;
	/// Override code end.

	if (shortest <= prefixLength + suffixLength) {
		// One or more strings will entirely vanish if we proceed.  Abort.
		return;
	}
	if (prefixLength) {
		this.prefixField = strings[0].substring(0, prefixLength - 1);
	}
	if (suffixLength) {
		this.suffixField = strings[0].substr(1 - suffixLength);
	}

	this.menuGenerator_ = Blockly.FieldDropdown.applyTrim_(options, prefixLength,
		suffixLength);
};

///////////////////////////////////////////////////////////////////////////
/// Additional Functions Field
///////////////////////////////////////////////////////////////////////////
/**
 * Get variable name in block by field name.
 * @param {!Blockly.Block} block The block containing the input.
 * @param {string} name The name of the field.
 */
Blockly.Block.prototype.getFieldVariableValue = function(name) {
	var fieldValue = this.getFieldValue(name);
	var variable = "";
	try {
		variable = Blockly.getMainWorkspace().getVariableById(fieldValue);
		variable = variable.name;
	}
	catch {
	}
	return variable;
}

/**
 * Generate array representing the specified array input.
 * @param {array} array The array of the input.
 * @return {array} Generated array.
 */
Blockly.Blocks.createDropdownArray = function(array, convertor=null) {
	var newArray = [];
	for (var i = 0; i < array.length; i++) {
		var item = array[i];
		var newItem = (convertor == null) ? item : convertor(item);
		newArray.push([item, newItem]);
	}
	return newArray;
}

/**
 * Generate array representing the specified value input.
 * @param {!Blockly.Block} block The block containing the input.
 * @param {string} name The name of the input.
 * @return {array} Generated array.
 */
Blockly.Generator.prototype.valueToArray = function(block, name) {
	var array = [];
	var targetBlock = block.getInputTargetBlock(name);
	if (!targetBlock) {
			return array;
	}
	for (var i = 0; i < targetBlock.inputList.length; i++) {
			var addBlock = targetBlock.getInputTargetBlock('ADD' + i);
			if (!addBlock) {
					array.push(null);
					continue;
			}
			var add = this.blockToCode(addBlock);
			array.push(add[0]);
	}
	return array;
}

/**
 * Generate array representing the specified text input.
 * @param {string} text The text of the input.
 * @return {array} Generated array.
 */
Blockly.Python.stringToArray = function(text) {
	var array = text.replace(/[^\d+|,]/g, "").split(",");
	return array;
}

/**
 * Generate array representing the specified color input.
 * @param {string} color The color string of the input.
 * @param {boolean} nullable The color generated array can be set to null.
 * @return {array} Generated array.
 */
Blockly.Python.stringToColorArray = function(color, nullable=false) {
    if (color != "None") {
        var colors = Blockly.Python.stringToArray(color);
        if (colors[0] != '') {
            while (colors.length < 3) {
                colors.push('0');
            }
            for (var i = 0; i < colors.length; i++) {
                var colorNum = Number(colors[i]);

                if (colorNum != NaN) {
                    if (colorNum > 255) {
                        colorNum = 255;
                    }
                    else if (colorNum < 0) {
                        colorNum = 0;
                    }
                }
                else {
                    colorNum = 0;
                }
                colors[i] = String(colorNum);
            }
            color = Blockly.Python.arrayToCode(colors);
        }
        else {
			if (nullable) {
				color = null;
			}
			else {
				color = "None";
			}
        }
	}
	
	return color;
}

/**
 * Generate python representing the specified array input.
 * @param {array} array The array input.
 * @param {boolean} ignore_null Ignore null or undefined value when true.
 * @return {string} Generated code.
 */
Blockly.Python.arrayToCode = function(array, ignore_null = false) {
	let code = "[";
	for (var i = 0; i < array.length; i++) {
			if (array[i] == null || array[i] == undefined) {
				if (!ignore_null) {
					code += "None";
				}
				else {
					continue;
				}
			}
			else {
				code += array[i];
			}
			if (i != array.length - 1) {
				code += ", ";
			}
	}
	code += "]";
	return code;
}

