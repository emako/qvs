'use strict';

/** Category List:
Anti-aliasing
Borders and Cropping
Collection
Color/Levels
Debanding
Deblocking
Dehaloing
Deinterlacing
Denoising
Deringing/Edge cleaning
Dot Crawl and Rainbows
Effects and Transitions
Frame Rate Conversion
Inverse Telecine
Line Darkening
Masking and Edge Detecting
Metrics and Analysis
Resizing and Format Conversion
Scripts
Sharpening
Source/Output
Subtitles
*/

document.write('<script src="blocks/anti_aliasing.js"></script>\n');
document.write('<script src="blocks/debanding.js"></script>\n');
document.write('<script src="blocks/deblocking.js"></script>\n');
document.write('<script src="blocks/dehaloing.js"></script>\n');
document.write('<script src="blocks/deinterlacing.js"></script>\n');
document.write('<script src="blocks/denoising.js"></script>\n');
document.write('<script src="blocks/derainbow.js"></script>\n');
document.write('<script src="blocks/deringing.js"></script>\n');
document.write('<script src="blocks/frame_rate.js"></script>\n');
document.write('<script src="blocks/inverse_telecine.js"></script>\n');
document.write('<script src="blocks/metrics_analysis.js"></script>\n');
document.write('<script src="blocks/resizing_format.js"></script>\n');
document.write('<script src="blocks/sharpening.js"></script>\n');
document.write('<script src="blocks/source_output.js"></script>\n');
document.write('<script src="blocks/subtitles.js"></script>\n');
document.write('<script src="blocks/utilses.js"></script>\n');

class BlockContextMenu {
	constructor(caption=null, filter=null, setOpenFileName=undefined) {
		if (caption != null)
		{
			this.caption = Blockly.Msg["$BLOCK_CONTEXT_MENU_CAPTION_OPEN_MEDIA_FILE"];
		}
		if (filter != null)
		{
			this.filter = Blockly.Msg["$BLOCK_CONTEXT_MENU_FILTER_OPEN_MEDIA_FILE"];
		}
		if (setOpenFileName != undefined)
		{
			this.setOpenFileName = setOpenFileName;
		}
	};
}

BlockContextMenu.prototype.createContextMenu = function(menuOptions) {
	var option = {
		enabled: qvs.enabled,
		text: Blockly.Msg["$BLOCK_CONTEXT_MENU_TEXT_OPEN_DDD"],
		callback:function() {
			qvs.requestOpenFileName(this);
		}.bind(this)
	};
	menuOptions.splice(0, 0, option);
};

BlockContextMenu.prototype.setOpenFileName = function(block, data) {
	if (block == null) {
		qvs.debug("block is null when want to modify params.");
		return;
	}
	try {
		Blockly.Field.prototype.setValue.call(block.inputList[0].fieldRow[1], data);
	}
	catch(err) {
		qvs.debug(err);
	}
};

var blocksParams = {
	preferQvs: true,
	searchTargetClip: function(block, nullable=false) {
		var clip = null;
		var parentBlock = block;
		for (;;) {
			parentBlock = parentBlock.parentBlock_;
			if (parentBlock == null || parentBlock == undefined) {
				break;
			}
			if (parentBlock.type == "clip_stat") {
				var variable = parentBlock.getField('variable');
				clip = variable.selectedOption_[0];
				break;
			}
		}
		if (clip == null) {
			if (!nullable) {
				clip = "src";
			}
			else {
				return null;
			}
		}
		return clip;
	},
};

/// open
Blockly.Blocks['open'] = {
	init: function() {
		this.appendDummyInput()
			.appendField("Open")
		this.setInputsInline(true)
		this.setOutput(true)
		this.setColour('rgb(116,200,141)')
		this.setTooltip('')
		this.setHelpUrl('')
		this.movable_ = false
		this.deletable_ = false
		this.disabled = !qvs.enabled
	}
}

Blockly.Python['open'] = function(block) {
	return 'open';
};

/// clip_stat
Blockly.Blocks['clip_stat'] = {
	init: function() {
		this.appendDummyInput()
			.appendField("set")
			.appendField(new Blockly.FieldVariable("src"), "variable")
			.appendField("to");
		this.appendStatementInput("inner_block");
		this.setInputsInline(false);
		this.setPreviousStatement(true, null);
		this.setNextStatement(true, null);
		this.setColour(270);
		this.setTooltip('Inner statments will return to this selected variable for target clip.');
		this.setHelpUrl('');
	}
};

Blockly.Python['clip_stat'] = function(block) {
    let variable = block.getField('variable').selectedOption_[0];
	var innerCode = Blockly.Python.statementToCode(block, "inner_block");

	var innerCodeLines = innerCode.split("\n");
	innerCode = "";
	innerCodeLines.forEach(function(line) {
		if (line.trim() != "") {
			innerCode += line.trim()+ "\n";
		}
	})

	var code = qvs.format("# set {0} to:\n{1}", variable, innerCode);
	return code;
};
