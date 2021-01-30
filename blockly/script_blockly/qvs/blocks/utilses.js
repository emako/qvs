'use strict';

/** Category List:
Collection
Color/Levels
Effects and Transitions
Script
*/

/// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
/// Logo
/// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

/// EraseAny
Blockly.Blocks['eraseany'] = {
    init: function() {
    this.appendDummyInput()
        .appendField("EraseAny")
        .appendField("lgd")
        .appendField(new Blockly.FieldTextInput(""), "lgd")
        .appendField("an")
        .appendField(new Blockly.FieldNumber('0', 0, 9, 0, (number) => {if (number < 0 || number > 9) return 0}), 'an')
        .appendField("fadein")
        .appendField(new Blockly.FieldNumber('0', 0, 2**53, 0, (number) => {if (number < 0) return 0}), 'fadein')
        .appendField("fadeout")
        .appendField(new Blockly.FieldNumber('0', 0, 2**53, 0, (number) => {if (number < 0) return 0}), 'fadeout')
        .appendField("start")
        .appendField(new Blockly.FieldNumber('0', 0, 2**53, 0, (number) => {if (number < 0) return 0}), 'start')
        .appendField("end")
        .appendField(new Blockly.FieldNumber('0', -1, 2**53, 0, (number) => {if (number < -1) return -1}), 'end');
    this.appendValueInput("load");
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(1);
    this.setTooltip("Be used for erase any transparent logo.\nYV12 and YV24 Only.");
    this.setHelpUrl("https://github.com/emako/qvs/blob/master/python/scripts/qvs.py");
    },
	contextMenu: new BlockContextMenu("Open Logo Data file", "Logo Data (*.lgd *.lgd2)", null),
};

Blockly.Python['eraseany'] = function(block) {
    let lgd = block.getFieldValue('lgd');
    let an = block.getFieldValue('an');
    let fadein = block.getFieldValue('fadein');
    let fadeout = block.getFieldValue('fadeout');
    let start = block.getFieldValue('start');
    let end = block.getFieldValue('end');
    if (end < 0) {
        end = 'None';
    }
    var code = qvs.format("{0} = qvs.EraseAny({0}, lgd=u'{1}', an={2}, fadein={3}, fadeout={4}, start={5}, end={6}, device_type='gpu', device_id=1)\n", blocksParams.searchTargetClip(block), qvs.unifySeparator(lgd), an, fadein, fadeout, start, end);
    return code;
};

/// AddLogo
Blockly.Blocks['addlogo'] = {
    init: function() {
    this.appendDummyInput()
        .appendField("AddLogo")
        .appendField("path")
        .appendField(new Blockly.FieldTextInput(""), "path")
        .appendField("w")
        .appendField(new Blockly.FieldNumber('0', 0, 2**53, 0, (number) => {if (number < 0) return 0}), 'w')
        .appendField("h")
        .appendField(new Blockly.FieldNumber('0', 0, 2**53, 0, (number) => {if (number < 0) return 0}), 'h')
        .appendField("an")
        .appendField(new Blockly.FieldNumber('0', 0, 9, 0, (number) => {if (number < 0 || number > 9) return 0}), 'an')
        .appendField("x")
        .appendField(new Blockly.FieldNumber('0', 0, 2**53, 0, (number) => {if (number < 0) return 0}), 'x')
        .appendField("y")
        .appendField(new Blockly.FieldNumber('0', 0, 2**53, 0, (number) => {if (number < 0) return 0}), 'y')
        .appendField("opacity")
        .appendField(new Blockly.FieldNumber('1', 0, 1, 0, (number) => {if (number < 0 || number > 1) return 0}), 'opacity')
        .appendField("aa")
        .appendField(new Blockly.FieldDropdown([["False", "False"], ["True", "True"]]), 'aa')
        .appendField("fadein")
        .appendField(new Blockly.FieldNumber('0', 0, 2**53, 0, (number) => {if (number < 0) return 0}), 'fadein')
        .appendField("fadeout")
        .appendField(new Blockly.FieldNumber('0', 0, 2**53, 0, (number) => {if (number < 0) return 0}), 'fadeout');
    this.appendValueInput("load");
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(1);
    this.setTooltip("Add image logo otherwise using *.lgd.");
    this.setHelpUrl("https://github.com/emako/qvs/blob/master/python/scripts/qvs.py");
    },
	contextMenu: new BlockContextMenu("Open Logo Data file", "Logo Data (*.lgd *.lgd2 *.png)", null),
};

Blockly.Python['addlogo'] = function(block) {
    let path = block.getFieldValue('path');
    let w = block.getFieldValue('w');
    let h = block.getFieldValue('h');
    let an = block.getFieldValue('an');
    let x = block.getFieldValue('x');
    let y = block.getFieldValue('y');
    let opacity = block.getFieldValue('opacity');
    let aa = block.getFieldValue('aa');
    let fadein = block.getFieldValue('fadein');
    let fadeout = block.getFieldValue('fadeout');
    var code = qvs.format("{0} = qvs.AddLogo({0}, path=u'{1}', w={2}, h={3}, an={4}, x={5}, y={6}, opacity={7}, aa={8}, fadein={9}, fadeout={10})\n", blocksParams.searchTargetClip(block), qvs.unifySeparator(path), w, h, an, x, y, opacity, aa, fadein, fadeout);
    return code;
};

/// Morpho
Blockly.Blocks['morpho'] = {
    init: function() {
    this.appendDummyInput()
        .appendField("Morpho")
        .appendField("algorithm")
        .appendField(new Blockly.FieldDropdown([["Dilate", "Dilate"], ["Erode", "Erode"], ["Open", "Open"], ["Close", "Close"], ["TopHat", "TopHat"], ["BottomHat", "BottomHat"]]), 'algorithm')
        .appendField("size")
        .appendField(new Blockly.FieldNumber('5', 0, 2**10, 0, (number) => {if (number < 0 || number > 2**10) return 0}), 'size')
        .appendField("shape")
        .appendField(new Blockly.FieldDropdown([["Square", "0"], ["Diamond", "1"], ["Circle", "2"]]), 'shape')
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(1);
    this.setTooltip("A set of simple morphological filters. Useful for working with mask clips.");
    this.setHelpUrl("http://www.vapoursynth.com/doc/plugins/morpho.html");
    },
};

Blockly.Python['morpho'] = function(block) {
    let algorithm = block.getFieldValue('algorithm');
    let size = block.getFieldValue('size');
    let shape = block.getFieldValue('shape');
    var code = qvs.format("{0} = core.morpho.{1}({0}, size={2}, shape={3})\n", blocksParams.searchTargetClip(block), algorithm, size, shape);
    return code;
};

/// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
/// Standards
/// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

/// Overlay
Blockly.Blocks['overlay'] = {
	init: function() {
		this.appendDummyInput()
			.appendField("Overlay")
            .appendField("clipa")
			.appendField(new Blockly.FieldVariable('src'), 'clipa')
            .appendField("clipb")
			.appendField(new Blockly.FieldVariable(''), 'clipb')
            .appendField("x")
            .appendField(new Blockly.FieldNumber('0', 0, 2**10, 0, (number) => {if (number < 0) return 0}), 'x')
            .appendField("y")
            .appendField(new Blockly.FieldNumber('0', 0, 2**10, 0, (number) => {if (number < 0) return 0}), 'y')
            .appendField("mask")
			.appendField(new Blockly.FieldTextInput("None"), "mask")
            .appendField("opacity")
            .appendField(new Blockly.FieldNumber('1', 0, 1, 0, (number) => {if (number < 0 || number > 1) return 1}), 'opacity')
		this.setInputsInline(true);
		this.setPreviousStatement(true, null);
		this.setNextStatement(true, null);
		this.setColour(1);
		this.setTooltip("Puts clip overlay on top of clip base using different blend modes, and with optional x,y positioning, masking and opacity.");
		this.setHelpUrl("http://avisynth.nl/index.php/Overlay");
	},
};

Blockly.Python['overlay'] = function(block) {
	let clipa = block.getFieldVariableValue('clipa');
	let clipb = block.getFieldVariableValue('clipb');
	let x = block.getFieldValue('x');
	let y = block.getFieldValue('y');
	let mask = block.getFieldValue('mask');
    let opacity = block.getFieldValue('opacity');

    if (clipa == '' || clipb == '') {
        console.warn("overlay params failed. (clipa or clipb is empty.)");
    }
    
	var code = qvs.format("{0} = qvs.Overlay({1}, {2}, x={3}, y={4}, mask={5}, opacity={6})\n", blocksParams.searchTargetClip(block), clipa, clipb, x, y, mask, opacity);
	return code;
};

/// Overlaymod
Blockly.Blocks['overlaymod'] = {
	init: function() {
		this.appendDummyInput()
			.appendField("Overlaymod")
            .appendField("clipa")
			.appendField(new Blockly.FieldVariable('src'), 'clipa')
            .appendField("clipb")
			.appendField(new Blockly.FieldVariable(''), 'clipb')
            .appendField("x")
            .appendField(new Blockly.FieldNumber('0', 1, 2**10, 0, (number) => {if (number < 1) return 1}), 'x')
            .appendField("y")
            .appendField(new Blockly.FieldNumber('0', 0, 2**10, 0, (number) => {if (number < 0) return 0}), 'y')
            .appendField("alpha")
			.appendField(new Blockly.FieldTextInput("None"), "alpha")
            .appendField("opacity")
            .appendField(new Blockly.FieldNumber('1', 0, 1, 0, (number) => {if (number < 0 || number > 1) return 1}), 'opacity')
            .appendField("aa")
            .appendField(new Blockly.FieldDropdown([["Off", "False"], ["On", "True"]]), 'aa')
		this.setInputsInline(true);
		this.setPreviousStatement(true, null);
		this.setNextStatement(true, null);
		this.setColour(1);
		this.setTooltip("Redesign the Overlaymod function to increase the opacity parameter.");
		this.setHelpUrl("https://github.com/emako/qvs/tree/master/python/scripts");
	},
};

Blockly.Python['overlaymod'] = function(block) {
	let clipa = block.getFieldVariableValue('clipa');
	let clipb = block.getFieldVariableValue('clipb');
	let x = block.getFieldValue('x');
	let y = block.getFieldValue('y');
	let alpha = block.getFieldValue('alpha');
    let opacity = block.getFieldValue('opacity');
    let aa = block.getFieldValue('aa');

    if (clipa == '' || clipb == '') {
        console.warn("overlaymod params failed. (clipa or clipb is empty.)");
    }
    
	var code = qvs.format("{0} = qvs.Overlaymod({1}, {2}, x={3}, y={4}, alpha={5}, opacity={6}, aa={7})\n", blocksParams.searchTargetClip(block), clipa, clipb, x, y, alpha, opacity, aa);
	return code;
};

/// StackVertical
Blockly.Blocks['stackvertical'] = {
	init: function() {
		this.appendDummyInput()
			.appendField("StackVertical")
			.appendField("clipa")
			.appendField(new Blockly.FieldVariable('src'), 'clipa')
			.appendField("clipb")
			.appendField(new Blockly.FieldVariable('src'), 'clipb')
		this.setInputsInline(true);
		this.setPreviousStatement(true, null);
		this.setNextStatement(true, null);
		this.setColour(1);
		this.setTooltip("Stacks all given clips together. The same format is a requirement. For StackVertical all clips also need to be the same width and for StackHorizontal all clips need to be the same height.\nThe frame properties are copied from the first clip.");
		this.setHelpUrl("http://www.vapoursynth.com/doc/functions/stack.html");
	},
};

Blockly.Python['stackvertical'] = function(block) {
    var clipa = block.getFieldVariableValue("clipa");
    var clipb = block.getFieldVariableValue("clipb");
	var code = qvs.format("{0} = core.std.StackVertical(clips=[{1}, {2}])\n", blocksParams.searchTargetClip(block), clipa, clipb);
	return code;
};

/// StackHorizontal
Blockly.Blocks['stackhorizontal'] = {
	init: function() {
		this.appendDummyInput()
			.appendField("StackHorizontal")
			.appendField("clipa")
			.appendField(new Blockly.FieldVariable('src'), 'clipa')
			.appendField("clipb")
			.appendField(new Blockly.FieldVariable('src'), 'clipb')
		this.setInputsInline(true);
		this.setPreviousStatement(true, null);
		this.setNextStatement(true, null);
		this.setColour(1);
		this.setTooltip("Stacks all given clips together. The same format is a requirement. For StackVertical all clips also need to be the same width and for StackHorizontal all clips need to be the same height.\nThe frame properties are copied from the first clip.");
		this.setHelpUrl("http://www.vapoursynth.com/doc/functions/stack.html");
	},
};

Blockly.Python['stackhorizontal'] = function(block) {
    var clipa = block.getFieldVariableValue("clipa");
    var clipb = block.getFieldVariableValue("clipb");
	var code = qvs.format("{0} = core.std.StackHorizontal(clips=[{1}, {2}])\n", blocksParams.searchTargetClip(block), clipa, clipb);
	return code;
};

/// StackVertical-Array
Blockly.Blocks['stackvertical_array'] = {
	init: function() {
		this.appendDummyInput()
			.appendField("StackVertical")
            .appendField("clips")
        this.appendValueInput("clips")
            .setCheck("Array");
		this.setInputsInline(true);
		this.setPreviousStatement(true, null);
		this.setNextStatement(true, null);
		this.setColour(1);
		this.setTooltip("Stacks all given clips together. The same format is a requirement. For StackVertical all clips also need to be the same width and for StackHorizontal all clips need to be the same height.\nThe frame properties are copied from the first clip.");
		this.setHelpUrl("http://www.vapoursynth.com/doc/functions/stack.html");
	},
};

Blockly.Python['stackvertical_array'] = function(block) {
	// See also:
	// Blockly.Python.valueToCode(block, "clips", Blockly.Python.ORDER_NONE);
    var clipsArray = Blockly.Python.valueToArray(block, "clips");
    var clipsCode = Blockly.Python.arrayToCode(clipsArray, true);
	var code = qvs.format("{0} = core.std.StackVertical({1})\n", blocksParams.searchTargetClip(block), clipsCode);
	return code;
};

/// StackHorizontal-Array
Blockly.Blocks['stackhorizontal_array'] = {
	init: function() {
		this.appendDummyInput()
			.appendField("StackHorizontal")
            .appendField("clips")
        this.appendValueInput("clips")
            .setCheck("Array");
		this.setInputsInline(true);
		this.setPreviousStatement(true, null);
		this.setNextStatement(true, null);
		this.setColour(1);
		this.setTooltip("Stacks all given clips together. The same format is a requirement. For StackVertical all clips also need to be the same width and for StackHorizontal all clips need to be the same height.\nThe frame properties are copied from the first clip.");
		this.setHelpUrl("http://www.vapoursynth.com/doc/functions/stack.html");
	},
};

Blockly.Python['stackhorizontal_array'] = function(block) {
	// See also:
	// Blockly.Python.valueToCode(block, "clips", Blockly.Python.ORDER_NONE);
    var clipsArray = Blockly.Python.valueToArray(block, "clips");
    var clipsCode = Blockly.Python.arrayToCode(clipsArray, true);
	var code = qvs.format("{0} = core.std.StackHorizontal({1})\n", blocksParams.searchTargetClip(block), clipsCode);
	return code;
};

/// TurnLeft
Blockly.Blocks['turnleft'] = {
	init: function() {
		this.appendDummyInput()
			.appendField("TurnLeft")
		this.setInputsInline(true);
		this.setPreviousStatement(true, null);
		this.setNextStatement(true, null);
		this.setColour(1);
		this.setTooltip("Turns the frames in a clip ±90,180 degrees.");
		this.setHelpUrl("http://www.vapoursynth.com/doc/avisynthcomp.html?highlight=turnleft");
	},
};

Blockly.Python['turnleft'] = function(block) {
	var code = qvs.format("{0} = qvs.TurnLeft({0})\n", blocksParams.searchTargetClip(block));
	return code;
};

/// TurnRight
Blockly.Blocks['turnright'] = {
	init: function() {
		this.appendDummyInput()
			.appendField("TurnRight")
		this.setInputsInline(true);
		this.setPreviousStatement(true, null);
		this.setNextStatement(true, null);
		this.setColour(1);
		this.setTooltip("Turns the frames in a clip ±90,180 degrees.");
		this.setHelpUrl("http://www.vapoursynth.com/doc/avisynthcomp.html?highlight=turnright");
	},
};

Blockly.Python['turnright'] = function(block) {
	var code = qvs.format("{0} = qvs.TurnRight({0})\n", blocksParams.searchTargetClip(block));
	return code;
};

/// Turn180
Blockly.Blocks['turn180'] = {
	init: function() {
		this.appendDummyInput()
			.appendField("Turn180")
		this.setInputsInline(true);
		this.setPreviousStatement(true, null);
		this.setNextStatement(true, null);
		this.setColour(1);
		this.setTooltip("Turns the frames in a clip 180 degrees (to the left, not to the right).");
		this.setHelpUrl("http://www.vapoursynth.com/doc/functions/turn180.html");
	},
};

Blockly.Python['turn180'] = function(block) {
	var code = qvs.format("{0} = core.std.Turn180({0})\n", blocksParams.searchTargetClip(block));
	return code;
};

/// FlipVertical
Blockly.Blocks['flipvertical'] = {
	init: function() {
		this.appendDummyInput()
			.appendField("FlipVertical")
		this.setInputsInline(true);
		this.setPreviousStatement(true, null);
		this.setNextStatement(true, null);
		this.setColour(1);
		this.setTooltip("Flips the clip in the vertical direction.");
		this.setHelpUrl("http://www.vapoursynth.com/doc/functions/flip.html?highlight=flipvertical#std.FlipVertical");
	},
};

Blockly.Python['flipvertical'] = function(block) {
	var code = qvs.format("{0} = core.std.FlipVertical({0})\n", blocksParams.searchTargetClip(block));
	return code;
};

/// FlipVertical
Blockly.Blocks['fliphorizontal'] = {
	init: function() {
		this.appendDummyInput()
			.appendField("FlipHorizontal")
		this.setInputsInline(true);
		this.setPreviousStatement(true, null);
		this.setNextStatement(true, null);
		this.setColour(1);
		this.setTooltip("Flips the clip in the horizontal direction.");
		this.setHelpUrl("http://www.vapoursynth.com/doc/functions/flip.html?highlight=flipvertical#std.FlipHorizontal");
	},
};

Blockly.Python['fliphorizontal'] = function(block) {
	var code = qvs.format("{0} = core.std.FlipHorizontal({0})\n", blocksParams.searchTargetClip(block));
	return code;
};

/// FadeIn
Blockly.Blocks['fadein'] = {
	init: function() {
		this.appendDummyInput()
			.appendField("FadeIn")
            .appendField("num_frames")
            .appendField(new Blockly.FieldNumber('0', 0, 2**52, 0, (number) => {if (number < 0) return 0}), 'num_frames')
            .appendField("color")
            .appendField(new Blockly.FieldTextInput('255, 255, 255'), 'color')
            .appendField("fps")
            .appendField(new Blockly.FieldNumber('0', 0, 10, 0, (number) => {if (number < 0) return 0}), 'fps')
		this.setInputsInline(true);
		this.setPreviousStatement(true, null);
		this.setNextStatement(true, null);
		this.setColour(1);
		this.setTooltip("FadeIn	blends progressively from color at the beginning.");
		this.setHelpUrl("http://avisynth.nl/index.php/FadeIn");
	},
};

Blockly.Python['fadein'] = function(block) {
	let num_frames = block.getFieldValue('num_frames');
	let color = block.getFieldValue('color');
	let fps = block.getFieldValue('fps');

	color = Blockly.Python.arrayToCode(Blockly.Python.stringToArray(color));
	if (fps <= 0) {
		fps = "None";
	}
	var code = qvs.format("{0} = qvs.FadeIn({0}, num_frames={1}, color={2}, fps={3})\n", blocksParams.searchTargetClip(block), num_frames, color, fps);
	return code;
};

/// FadeOut
Blockly.Blocks['fadeout'] = {
	init: function() {
		this.appendDummyInput()
			.appendField("FadeOut")
            .appendField("num_frames")
            .appendField(new Blockly.FieldNumber('0', 0, 2**52, 0, (number) => {if (number < 0) return 0}), 'num_frames')
            .appendField("color")
            .appendField(new Blockly.FieldTextInput('255, 255, 255'), 'color')
            .appendField("fps")
            .appendField(new Blockly.FieldNumber('0', 0, 10, 0, (number) => {if (number < 0) return 0}), 'fps')
		this.setInputsInline(true);
		this.setPreviousStatement(true, null);
		this.setNextStatement(true, null);
		this.setColour(1);
		this.setTooltip("FadeOut blends progressively to color at the end.");
		this.setHelpUrl("http://avisynth.nl/index.php/FadeOut");
	},
};

Blockly.Python['fadeout'] = function(block) {
	let num_frames = block.getFieldValue('num_frames');
	let color = block.getFieldValue('color');
	let fps = block.getFieldValue('fps');

	color = Blockly.Python.arrayToCode(Blockly.Python.stringToArray(color));
	if (fps <= 0) {
		fps = "None";
	}
	var code = qvs.format("{0} = qvs.FadeOut({0}, num_frames={1}, color={2}, fps={3})\n", blocksParams.searchTargetClip(block), num_frames, color, fps);
	return code;
};

/// Dissolve
Blockly.Blocks['dissolve'] = {
	init: function() {
		this.appendDummyInput()
			.appendField("Dissolve")
            .appendField("clipa")
			.appendField(new Blockly.FieldVariable('src'), 'clipa')
            .appendField("clipb")
			.appendField(new Blockly.FieldVariable('src'), 'clipb')
            .appendField("overlap")
            .appendField(new Blockly.FieldNumber('24', 0, 2**52, 0, (number) => {if (number < 0) return 0}), 'overlap')
            .appendField("fps")
            .appendField(new Blockly.FieldNumber('0', 0, 10, 0, (number) => {if (number < 0) return 0}), 'fps')
		this.setInputsInline(true);
		this.setPreviousStatement(true, null);
		this.setNextStatement(true, null);
		this.setColour(1);
		this.setTooltip("Dissolve is like AlignedSplice, except that the clips are combined with some overlap.");
		this.setHelpUrl("http://avisynth.nl/index.php/Dissolve");
	},
};

Blockly.Python['dissolve'] = function(block) {
	let clipa = block.getFieldVariableValue('clipa');
	let clipb = block.getFieldVariableValue('clipb');
	let overlap = block.getFieldValue('overlap');
	let fps = block.getFieldValue('fps');
	if (fps <= 0) {
		fps = "None";
	}
	var code = qvs.format("{0} = qvs.Dissolve(clipa={1}, clipb={2}, overlap={3}, fps={4})\n", blocksParams.searchTargetClip(block), clipa, clipb, overlap, fps);
	return code;
};

/// Tweak
Blockly.Blocks['tweak'] = {
	init: function() {
		this.appendDummyInput()
			.appendField("Tweak")
            .appendField("hue")
            .appendField(new Blockly.FieldNumber('0', -180, 180, 0, (number) => {if (number < -180 || number > 180) return 0}), 'hue')
            .appendField("saturation")
            .appendField(new Blockly.FieldNumber('1', 0, 10, 0, (number) => {if (number < 0 || number > 10) return 0}), 'saturation')
            .appendField("bright")
            .appendField(new Blockly.FieldNumber('0', 0, 10, 0, (number) => {if (number < 0 || number > 10) return 0}), 'bright')
            .appendField("contrast")
            .appendField(new Blockly.FieldNumber('0', 0, 10, 0, (number) => {if (number < 0 || number > 10) return 0}), 'contrast')
		this.setInputsInline(true);
		this.setPreviousStatement(true, null);
		this.setNextStatement(true, null);
		this.setColour(1);
		this.setTooltip("This is a very basic port of the built-in Avisynth filter Tweak. \nInternally, it uses std.Lut and std.Expr to carry out the adjustments. \n8..16 bit integer and 32 bit float sample types are supported.");
		this.setHelpUrl("https://github.com/dubhater/vapoursynth-adjust");
	},
};

Blockly.Python['tweak'] = function(block) {
	let hue = block.getFieldValue('hue');
	let saturation = block.getFieldValue('saturation');
	let bright = block.getFieldValue('bright');
	let contrast = block.getFieldValue('contrast');
	var code = qvs.format("{0} = qvs.Tweak({0}, hue={1}, saturation={2}, bright={3}, contrast={4})\n", blocksParams.searchTargetClip(block), hue, saturation, bright, contrast);
	return code;
};

/// Levels
Blockly.Blocks['levels'] = {
	init: function() {
		this.appendDummyInput()
			.appendField("Levels")
            .appendField("min_in")
            .appendField(new Blockly.FieldNumber('0', -(2**52), 2**52, 0, (number) => {if (number < -(2**52) || number > 2**52) return 0}), 'min_in')
            .appendField("max_in")
            .appendField(new Blockly.FieldNumber('255', -(2**52), 2**52, 0, (number) => {if (number < -(2**52) || number > 2**52) return 0}), 'max_in')
            .appendField("gamma")
            .appendField(new Blockly.FieldNumber('1.0', -(2**52), 2**52, 0, (number) => {if (number < -(2**52) || number > 2**52) return 1}), 'gamma')
            .appendField("min_out")
            .appendField(new Blockly.FieldNumber('0', -(2**52), 2**52, 0, (number) => {if (number < -(2**52) || number > 2**52) return 0}), 'min_out')
            .appendField("max_out")
            .appendField(new Blockly.FieldNumber('255', -(2**52), 2**52, 0, (number) => {if (number < -(2**52) || number > 2**52) return 0}), 'max_out')
            .appendField("planes")
            .appendField(new Blockly.FieldTextInput('0, 1, 2'), 'planes')
		this.setInputsInline(true);
		this.setPreviousStatement(true, null);
		this.setNextStatement(true, null);
		this.setColour(1);
		this.setTooltip("Adjusts brightness, contrast, and gamma.");
		this.setHelpUrl("http://www.vapoursynth.com/doc/functions/levels.html");
	},
};

Blockly.Python['levels'] = function(block) {
	let min_in = block.getFieldValue('min_in');
	let max_in = block.getFieldValue('max_in');
	let gamma = block.getFieldValue('gamma');
	let min_out = block.getFieldValue('min_out');
	let max_out = block.getFieldValue('max_out');
	let planes = block.getFieldValue('planes');
	planes = Blockly.Python.arrayToCode(Blockly.Python.stringToArray(planes));
	var code = qvs.format("{0} = core.std.Levels({0}, min_in={1}, max_in={2}, gamma={3}, min_out={4}, max_out={5}, planes={6})\n", blocksParams.searchTargetClip(block), min_in, max_in, gamma, min_out, max_out, planes);
	return code;
};

/// Invert
Blockly.Blocks['invert'] = {
	init: function() {
		this.appendDummyInput()
			.appendField("Invert")
            .appendField("planes")
            .appendField(new Blockly.FieldTextInput('0, 1, 2'), 'planes')
		this.setInputsInline(true);
		this.setPreviousStatement(true, null);
		this.setNextStatement(true, null);
		this.setColour(1);
		this.setTooltip("Inverts the pixel values. Specifically, it subtracts the value of the input pixel from the format’s maximum allowed value.");
		this.setHelpUrl("http://www.vapoursynth.com/doc/functions/invert.html");
	},
};

Blockly.Python['invert'] = function(block) {
	let planes = block.getFieldValue('planes');
	planes = Blockly.Python.arrayToCode(Blockly.Python.stringToArray(planes));
	var code = qvs.format("{0} = core.std.Invert({0}, planes={1})\n", blocksParams.searchTargetClip(block), planes);
	return code;
};

/// BoxBlur
Blockly.Blocks['boxblur'] = {
	init: function() {
		this.appendDummyInput()
			.appendField("BoxBlur")
            .appendField("planes")
            .appendField(new Blockly.FieldTextInput('0, 1, 2'), 'planes')
            .appendField("hradius")
            .appendField(new Blockly.FieldNumber('1', 0, 2**53, 0, (number) => {if (number < 0) return 0}), 'hradius')
            .appendField("hpasses")
            .appendField(new Blockly.FieldNumber('1', 1, 2**53, 0, (number) => {if (number < 1) return 1}), 'hpasses')
            .appendField("vradius")
            .appendField(new Blockly.FieldNumber('1', 0, 2**53, 0, (number) => {if (number < 0) return 0}), 'vradius')
            .appendField("vpasses")
            .appendField(new Blockly.FieldNumber('1', 1, 2**53, 0, (number) => {if (number < 1) return 1}), 'vpasses')
		this.setInputsInline(true);
		this.setPreviousStatement(true, null);
		this.setNextStatement(true, null);
		this.setColour(1);
		this.setTooltip("Performs a box blur which is fast even for large radius values. \nUsing multiple passes can be used to fairly cheaply approximate a gaussian blur. \nA radius of 0 means no processing is performed.");
		this.setHelpUrl("http://www.vapoursynth.com/doc/functions/boxblur.html");
	},
};

Blockly.Python['boxblur'] = function(block) {
	let planes = block.getFieldValue('planes');
	let hradius = block.getFieldValue('hradius');
	let hpasses = block.getFieldValue('hpasses');
	let vradius = block.getFieldValue('vradius');
	let vpasses = block.getFieldValue('vpasses');
	planes = Blockly.Python.arrayToCode(Blockly.Python.stringToArray(planes));
	var code = qvs.format("{0} = core.std.BoxBlur({0}, planes={1}, hradius={2}, hpasses={3}, vradius={4}, vpasses={5})\n", blocksParams.searchTargetClip(block), planes, hradius, hpasses, vradius, vpasses);
	return code;
};

/// Limiter
Blockly.Blocks['limiter'] = {
	init: function() {
		this.appendDummyInput()
			.appendField("Limiter")
            .appendField("min")
            .appendField(new Blockly.FieldTextInput('0, 0, 0'), 'min')
            .appendField("max")
            .appendField(new Blockly.FieldTextInput('255, 255, 255'), 'max')
            .appendField("planes")
            .appendField(new Blockly.FieldTextInput('0, 1, 2'), 'planes')
		this.setInputsInline(true);
		this.setPreviousStatement(true, null);
		this.setNextStatement(true, null);
		this.setColour(1);
		this.setTooltip("Limits the pixel values to the range [min, max].");
		this.setHelpUrl("http://www.vapoursynth.com/doc/functions/limiter.html");
	},
};

Blockly.Python['limiter'] = function(block) {
	let min = block.getFieldValue('min');
	let max = block.getFieldValue('max');
	let planes = block.getFieldValue('planes');
	min = Blockly.Python.arrayToCode(Blockly.Python.stringToArray(min));
	max = Blockly.Python.arrayToCode(Blockly.Python.stringToArray(max));
	planes = Blockly.Python.arrayToCode(Blockly.Python.stringToArray(planes));
	var code = qvs.format("{0} = core.std.Limiter({0}, min={1}, max={2}, planes={3})\n", blocksParams.searchTargetClip(block), min, max, planes);
	return code;
};

/// Expr
Blockly.Blocks['expr'] = {
	init: function() {
		this.appendDummyInput()
			.appendField("Expr")
		this.appendDummyInput()
            .appendField("clips")
		this.appendValueInput("clips")
			.setCheck("Array")
		this.appendDummyInput()
            .appendField("expr")
		this.appendValueInput("expr")
			.setCheck("Array")
		this.appendDummyInput()
			.appendField("format")
			.appendField(new Blockly.FieldDropdown(Blockly.Blocks.createDropdownArray(getFormatConstants(true))), 'format')
		this.setInputsInline(true);
		this.setPreviousStatement(true, null);
		this.setNextStatement(true, null);
		this.setColour(1);
		this.setTooltip("Expr evaluates an expression per pixel for up to 26 input clips. \nThe expression, expr, is written using reverse polish notation and can be specified for each plane individually.");
		this.setHelpUrl("http://www.vapoursynth.com/doc/functions/expr.html");
	},
};

Blockly.Python['expr'] = function(block) {
	// See also:
	// Blockly.Python.valueToCode(block, "clips", Blockly.Python.ORDER_NONE);
    let clips = Blockly.Python.valueToArray(block, "clips");
	clips = Blockly.Python.arrayToCode(clips, true);

    let expr = Blockly.Python.valueToArray(block, "expr");
	expr = Blockly.Python.arrayToCode(expr, true);
	
	let format = block.getFieldValue('format');
	var code = qvs.format("{0} = core.std.Expr(clips={1}, expr={2}, format={3})\n", blocksParams.searchTargetClip(block), clips, expr, format);
	return code;
};

/// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
/// Miscs
/// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

/// Prewitt
Blockly.Blocks['prewitt'] = {
	init: function() {
		this.appendDummyInput()
			.appendField("Prewitt")
            .appendField("planes")
            .appendField(new Blockly.FieldTextInput('0, 1, 2'), 'planes')
            .appendField("scale")
            .appendField(new Blockly.FieldNumber('1', 0, 2**53, 0, (number) => {if (number < 0) return 0}), 'scale')
		this.setInputsInline(true);
		this.setPreviousStatement(true, null);
		this.setNextStatement(true, null);
		this.setColour(1);
		this.setTooltip("Creates an edge mask using the Prewitt operator.");
		this.setHelpUrl("http://www.vapoursynth.com/doc/functions/prewitt_sobel.html");
	},
};

Blockly.Python['prewitt'] = function(block) {
	let planes = block.getFieldValue('planes');
	let scale = block.getFieldValue('scale');
	planes = Blockly.Python.arrayToCode(Blockly.Python.stringToArray(planes));
	var code = qvs.format("{0} = core.std.Prewitt({0}, planes={1}, scale={2})\n", blocksParams.searchTargetClip(block), planes, scale);
	return code;
};

/// Sobel
Blockly.Blocks['sobel'] = {
	init: function() {
		this.appendDummyInput()
			.appendField("Sobel")
            .appendField("planes")
            .appendField(new Blockly.FieldTextInput('0, 1, 2'), 'planes')
            .appendField("scale")
            .appendField(new Blockly.FieldNumber('1', 0, 2**53, 0, (number) => {if (number < 0) return 0}), 'scale')
		this.setInputsInline(true);
		this.setPreviousStatement(true, null);
		this.setNextStatement(true, null);
		this.setColour(1);
		this.setTooltip("Creates an edge mask using the Sobel operator.");
		this.setHelpUrl("http://www.vapoursynth.com/doc/functions/prewitt_sobel.html");
	},
};

Blockly.Python['sobel'] = function(block) {
	let planes = block.getFieldValue('planes');
	let scale = block.getFieldValue('scale');
	planes = Blockly.Python.arrayToCode(Blockly.Python.stringToArray(planes));
	var code = qvs.format("{0} = core.std.Sobel({0}, planes={1}, scale={2})\n", blocksParams.searchTargetClip(block), planes, scale);
	return code;
};
