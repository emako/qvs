'use strict';

/** Category List:
Metrics and Analysis
*/

/// ViewNoise
Blockly.Blocks['viewnoise'] = {
	init: function() {
		this.appendDummyInput()
			.appendField("ViewNoise")
            .appendField("threshold")
            .appendField(new Blockly.FieldNumber('150', 0, 2**10, 0, (number) => {if (number < 0) return 0}), 'threshold')
            .appendField("optmode")
            .appendField(new Blockly.FieldNumber('1', 1, 0, 0, (number) => {if (number < 0 || number > 1) return 0}), 'optmode')
		this.setInputsInline(true);
		this.setPreviousStatement(true, null);
		this.setNextStatement(true, null);
		this.setColour(1);
		this.setTooltip("View the clip noise.");
		this.setHelpUrl("https://github.com/emako/qvs/tree/master/python/scripts");
	},
};

Blockly.Python['viewnoise'] = function(block) {
	let threshold = block.getFieldValue('threshold');
	let optmode = block.getFieldValue('optmode');
	var code = qvs.format("{0} = qvs.ViewNoise({0}, threshold={1}, optmode={2})\n", blocksParams.searchTargetClip(block), threshold, optmode);
	return code;
};

/// ViewDiff
Blockly.Blocks['viewdiff'] = {
	init: function() {
		this.appendDummyInput()
			.appendField("ViewDiff")
			.appendField("clipa")
			.appendField(new Blockly.FieldVariable('src'), 'clipa')
			.appendField("clipb")
			.appendField(new Blockly.FieldVariable('src'), 'clipb')
            .appendField("planes")
            .appendField(new Blockly.FieldTextInput('0'), 'planes')
            .appendField("threshold")
            .appendField(new Blockly.FieldNumber('1', 0, 2**10, 0, (number) => {if (number < 0) return 0}), 'threshold')
            .appendField("stack")
            .appendField(new Blockly.FieldCheckbox('FALSE'), 'stack')
		this.setInputsInline(true);
		this.setPreviousStatement(true, null);
		this.setNextStatement(true, null);
		this.setColour(1);
		this.setTooltip("A filter to check the difference of source clip and filtered clip.");
		this.setHelpUrl("https://github.com/emako/qvs/tree/master/python/scripts");
	},
};

Blockly.Python['viewdiff'] = function(block) {
    let clipa = block.getFieldVariableValue("clipa");
    let clipb = block.getFieldVariableValue("clipb");
	let planes = block.getFieldValue('planes');
	let stack = block.getFieldValue('stack') == "TRUE" ? "True" : "False";
	planes = Blockly.Python.arrayToCode(Blockly.Python.stringToArray(planes));
	let threshold = block.getFieldValue('threshold');
	var code = qvs.format("{0} = qvs.ViewDiff(clipa={1}, clipb={2}, planes={3}, threshold={4}, stack={5})\n", blocksParams.searchTargetClip(block), clipa, clipb, planes, threshold, stack);
	return code;
};

/// ViewFrameType
Blockly.Blocks['viewframetype'] = {
	init: function() {
		this.appendDummyInput()
			.appendField("ViewFrameType")
		this.setInputsInline(true);
		this.setPreviousStatement(true, null);
		this.setNextStatement(true, null);
		this.setColour(1);
		this.setTooltip("Display frame type, like 'I', 'P', 'B'.");
		this.setHelpUrl("https://github.com/emako/qvs/tree/master/python/scripts");
	},
};

/// ViewFrameType
Blockly.Blocks['viewframetype'] = {
	init: function() {
		this.appendDummyInput()
			.appendField("ViewFrameType")
		this.setInputsInline(true);
		this.setPreviousStatement(true, null);
		this.setNextStatement(true, null);
		this.setColour(1);
		this.setTooltip("Display frame type, like 'I', 'P', 'B'.");
		this.setHelpUrl("https://github.com/emako/qvs/tree/master/python/scripts");
	},
};

Blockly.Python['viewframetype'] = function(block) {
	var code = qvs.format("{0} = qvs.ViewFrameType({0})\n", blocksParams.searchTargetClip(block));
	return code;
};

/// ViewMediaInfo
Blockly.Blocks['viewmediainfo'] = {
	init: function() {
		this.appendDummyInput()
			.appendField("ViewMediaInfo")
            .appendField("path")
			.appendField(new Blockly.FieldTextInput(""), "path")
            .appendField("full")
			.appendField(new Blockly.FieldCheckbox('0'), 'full')
            .appendField("an")
			.appendField(new Blockly.FieldDropdown([["0", "0"], ["1", "1"], ["2", "2"], ["3", "3"], ["4", "4"], ["5", "5"], ["6", "6"], ["7", "7"], ["8", "8"], ["9", "9"]]), 'an')
		this.appendValueInput("load");
		this.setInputsInline(true);
		this.setPreviousStatement(true, null);
		this.setNextStatement(true, null);
		this.setColour(1);
		this.setTooltip("View the clip noise.");
		this.setHelpUrl("https://github.com/emako/qvs/tree/master/python/scripts");
	},
	contextMenu: new BlockContextMenu(),
};

Blockly.Python['viewmediainfo'] = function(block) {
	let path = block.getFieldValue('path');
	let full = block.getFieldValue('full') == "TRUE" ? "True" : "False";
	let an = block.getFieldValue('an');
	var code = qvs.format("{0} = qvs.ViewMediaInfo({0}, path=u'{1}', full={2}, an={3})\n", blocksParams.searchTargetClip(block), qvs.unifySeparator(path), full, an);
	return code;
};

/// ViewFrameNum
Blockly.Blocks['viewframenum'] = {
	init: function() {
		this.appendDummyInput()
			.appendField("ViewFrameNum")
            .appendField("alignment")
			.appendField(new Blockly.FieldDropdown([["0", "0"], ["1", "1"], ["2", "2"], ["3", "3"], ["4", "4"], ["5", "5"], ["6", "6"], ["7", "7"], ["8", "8"], ["9", "9"]]), 'alignment')
		this.setInputsInline(true);
		this.setPreviousStatement(true, null);
		this.setNextStatement(true, null);
		this.setColour(1);
		this.setTooltip("View the clip frame number.");
		this.setHelpUrl("http://www.vapoursynth.com/doc/functions/framenum.html");
	},
};

Blockly.Python['viewframenum'] = function(block) {
	let alignment = block.getFieldValue('alignment');
	alignment = Number(alignment)
	if (alignment <= 0 || alignment > 9) {
		alignment = 7;
	}
	var code = qvs.format("{0} = qvs.ViewFrameNum({0}, alignment={1})\n", blocksParams.searchTargetClip(block), alignment);
	return code;
};

/// ViewFrameNumAndTime
Blockly.Blocks['viewframenumandtime'] = {
	init: function() {
		this.appendDummyInput()
			.appendField("ViewFrameNumAndTime")
            .appendField("x")
            .appendField(new Blockly.FieldNumber('0', -(2**10), 2**10, 0, number => number), 'x')
            .appendField("y")
            .appendField(new Blockly.FieldNumber('0', -(2**10), 2**10, 0, number => number), 'y')
            .appendField("alignment")
			.appendField(new Blockly.FieldDropdown([["0", "0"], ["1", "1"], ["2", "2"], ["3", "3"], ["4", "4"], ["5", "5"], ["6", "6"], ["7", "7"], ["8", "8"], ["9", "9"]]), 'alignment')
		this.setInputsInline(true);
		this.setPreviousStatement(true, null);
		this.setNextStatement(true, null);
		this.setColour(1);
		this.setTooltip("View the clip frame number and timecode.");
		this.setHelpUrl("https://github.com/jeremypoulter/vsutils/blob/master/vsutils.py");
	},
};

Blockly.Python['viewframenumandtime'] = function(block) {
	let x = block.getFieldValue('x');
	let y = block.getFieldValue('y');
	let alignment = block.getFieldValue('alignment');
	alignment = Number(alignment)
	if (alignment <= 0 || alignment > 9) {
		alignment = 7;
	}
	var code = qvs.format("{0} = qvs.ViewFrameNumAndTime({0}, x={1}, y={2}, alignment={3})\n", blocksParams.searchTargetClip(block), x, y, alignment);
	return code;
};

/// ViewFrameNumAndTime
Blockly.Blocks['viewcoreinfo'] = {
	init: function() {
		this.appendDummyInput()
			.appendField("ViewCoreInfo")
            .appendField("alignment")
			.appendField(new Blockly.FieldDropdown([["0", "0"], ["1", "1"], ["2", "2"], ["3", "3"], ["4", "4"], ["5", "5"], ["6", "6"], ["7", "7"], ["8", "8"], ["9", "9"]]), 'alignment')
		this.setInputsInline(true);
		this.setPreviousStatement(true, null);
		this.setNextStatement(true, null);
		this.setColour(1);
		this.setTooltip("View the clip frame number and timecode.");
		this.setHelpUrl("https://github.com/jeremypoulter/vsutils/blob/master/vsutils.py");
	},
};

Blockly.Python['viewcoreinfo'] = function(block) {
	let clip = blocksParams.searchTargetClip(block, true);
	let alignment = block.getFieldValue('alignment');
	if (clip == null) {
		clip = "None";
	}
	alignment = Number(alignment)
	if (alignment <= 0 || alignment > 9) {
		alignment = 7;
	}
	var code = qvs.format("{0} = core.text.CoreInfo({1}, alignment={2})\n", blocksParams.searchTargetClip(block), clip, alignment);
	return code;
};
