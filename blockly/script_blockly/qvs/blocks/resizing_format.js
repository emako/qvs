'use strict';

/** Category List:
Borders and Cropping
Resizing and Format Conversion
*/

/// Resize
Blockly.Blocks['resize'] = {
    init: function() {
        this.appendDummyInput()
            .appendField("Resize")
            .appendField("algorithm")
            .appendField(new Blockly.FieldDropdown([["Bilinear", "Bilinear"], ["Bicubic", "Bicubic"], ["Point", "Point"], ["Lanczos", "Lanczos"], ["Spline16", "Spline16"], ["Spline36", "Spline36"], ["Nnedi3", "Nnedi3"]]), 'algorithm')
            .appendField("width")
            .appendField(new Blockly.FieldNumber('1280', 0, 10000000, 0, (number) => {if (number < 0 || number > 10000000) return 0}), 'width')
            .appendField("height")
            .appendField(new Blockly.FieldNumber('720', 0, 10000000, 0, (number) => {if (number < 0 || number > 10000000) return 0}), 'height')
        this.setInputsInline(true);
        this.setPreviousStatement(true, null);
        this.setNextStatement(true, null);
        this.setColour(100);
        this.setTooltip("In VapourSynth the resizers have several functions, in addition, Nnedi3 resizer uses OpenCL.");
        this.setHelpUrl("http://www.vapoursynth.com/doc/functions/resize.html");
    },
};

Blockly.Python['resize'] = function(block) {
    let algorithm = block.getFieldValue('algorithm');
    let width = block.getFieldValue('width');
    let height = block.getFieldValue('height');
    var code = null;
    switch (algorithm) {
        case 'Bilinear':
        case 'Bicubic':
        case 'Point':
        case 'Lanczos':
        case 'Spline16':
        case 'Spline36':
        default:
            code = qvs.format("{0} = core.resize.{1}({0}, width={2}, height={3})\n", blocksParams.searchTargetClip(block), algorithm, width, height);
            break;
        case 'Nnedi3':
            code = qvs.format("{0} = qvs.Nnedi3Resize({0}, w={1}, h={2}, cl=True, device=2, list_device=False)\n", blocksParams.searchTargetClip(block), width, height);
            break;
    }
    return code;
};

/// BilinearResize
Blockly.Blocks['bilinear_resize'] = {
    init: function() {
    this.appendDummyInput()
        .appendField("BilinearResize")
        .appendField("width")
        .appendField(new Blockly.FieldNumber('1280', 0, 10000000, 0, (number) => {if (number < 0 || number > 10000000) return 0}), 'width')
        .appendField("height")
        .appendField(new Blockly.FieldNumber('720', 0, 10000000, 0, (number) => {if (number < 0 || number > 10000000) return 0}), 'height')
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(100);
    this.setTooltip("Bilinear resizer in VapourSynth functions.");
    this.setHelpUrl("http://www.vapoursynth.com/doc/functions/resize.html");
    },
};

Blockly.Python['bilinear_resize'] = function(block) {
    let width = block.getFieldValue('width');
    let height = block.getFieldValue('height');
    var code = qvs.format("{0} = core.resize.Bilinear({0}, width={1}, height={2})\n", blocksParams.searchTargetClip(block), width, height);
    return code;
};

/// BicubicResize
Blockly.Blocks['bicubic_resize'] = {
    init: function() {
    this.appendDummyInput()
        .appendField("BicubicResize")
        .appendField("width")
        .appendField(new Blockly.FieldNumber('1280', 0, 10000000, 0, (number) => {if (number < 0 || number > 10000000) return 0}), 'width')
        .appendField("height")
        .appendField(new Blockly.FieldNumber('720', 0, 10000000, 0, (number) => {if (number < 0 || number > 10000000) return 0}), 'height')
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(100);
    this.setTooltip("Bicubic resizer in VapourSynth functions.");
    this.setHelpUrl("http://www.vapoursynth.com/doc/functions/resize.html");
    },
};

Blockly.Python['bicubic_resize'] = function(block) {
    let width = block.getFieldValue('width');
    let height = block.getFieldValue('height');
    var code = qvs.format("{0} = core.resize.Bicubic({0}, width={1}, height={2})\n", blocksParams.searchTargetClip(block), width, height);
    return code;
};

/// PointResize
Blockly.Blocks['point_resize'] = {
    init: function() {
    this.appendDummyInput()
        .appendField("PointResize")
        .appendField("width")
        .appendField(new Blockly.FieldNumber('1280', 0, 10000000, 0, (number) => {if (number < 0 || number > 10000000) return 0}), 'width')
        .appendField("height")
        .appendField(new Blockly.FieldNumber('720', 0, 10000000, 0, (number) => {if (number < 0 || number > 10000000) return 0}), 'height')
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(100);
    this.setTooltip("Point resizer in VapourSynth functions.");
    this.setHelpUrl("http://www.vapoursynth.com/doc/functions/resize.html");
    },
};

Blockly.Python['point_resize'] = function(block) {
    let width = block.getFieldValue('width');
    let height = block.getFieldValue('height');
    var code = qvs.format("{0} = core.resize.Point({0}, width={1}, height={2})\n", blocksParams.searchTargetClip(block), width, height);
    return code;
};

/// LanczosResize
Blockly.Blocks['lanczos_resize'] = {
    init: function() {
    this.appendDummyInput()
        .appendField("LanczosResize")
        .appendField("width")
        .appendField(new Blockly.FieldNumber('1280', 0, 10000000, 0, (number) => {if (number < 0 || number > 10000000) return 0}), 'width')
        .appendField("height")
        .appendField(new Blockly.FieldNumber('720', 0, 10000000, 0, (number) => {if (number < 0 || number > 10000000) return 0}), 'height')
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(100);
    this.setTooltip("Lanczos resizer in VapourSynth functions.");
    this.setHelpUrl("http://www.vapoursynth.com/doc/functions/resize.html");
    },
};

Blockly.Python['lanczos_resize'] = function(block) {
    let width = block.getFieldValue('width');
    let height = block.getFieldValue('height');
    var code = qvs.format("{0} = core.resize.Lanczos({0}, width={1}, height={2})\n", blocksParams.searchTargetClip(block), width, height);
    return code;
};

/// Spline16Resize
Blockly.Blocks['spline16_resize'] = {
    init: function() {
    this.appendDummyInput()
        .appendField("Spline16Resize")
        .appendField("width")
        .appendField(new Blockly.FieldNumber('1280', 0, 10000000, 0, (number) => {if (number < 0 || number > 10000000) return 0}), 'width')
        .appendField("height")
        .appendField(new Blockly.FieldNumber('720', 0, 10000000, 0, (number) => {if (number < 0 || number > 10000000) return 0}), 'height')
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(100);
    this.setTooltip("Spline16 resizer in VapourSynth functions.");
    this.setHelpUrl("http://www.vapoursynth.com/doc/functions/resize.html");
    },
};

Blockly.Python['spline16_resize'] = function(block) {
    let width = block.getFieldValue('width');
    let height = block.getFieldValue('height');
    var code = qvs.format("{0} = core.resize.Spline16({0}, width={1}, height={2})\n", blocksParams.searchTargetClip(block), width, height);
    return code;
};

/// Spline36Resize
Blockly.Blocks['spline36_resize'] = {
    init: function() {
    this.appendDummyInput()
        .appendField("Spline36Resize")
        .appendField("width")
        .appendField(new Blockly.FieldNumber('1280', 0, 10000000, 0, (number) => {if (number < 0 || number > 10000000) return 0}), 'width')
        .appendField("height")
        .appendField(new Blockly.FieldNumber('720', 0, 10000000, 0, (number) => {if (number < 0 || number > 10000000) return 0}), 'height')
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(100);
    this.setTooltip("Spline36 resizer in VapourSynth functions.");
    this.setHelpUrl("http://www.vapoursynth.com/doc/functions/resize.html");
    },
};

Blockly.Python['spline36_resize'] = function(block) {
    let width = block.getFieldValue('width');
    let height = block.getFieldValue('height');
    var code = qvs.format("{0} = core.resize.Spline36({0}, width={1}, height={2})\n", blocksParams.searchTargetClip(block), width, height);
    return code;
};

/// Nnedi3Resize
Blockly.Blocks['nnedi3_resize'] = {
    init: function() {
    this.appendDummyInput()
        .appendField("Nnedi3Resize")
        .appendField("width")
        .appendField(new Blockly.FieldNumber('1280', 0, 10000000, 0, (number) => {if (number < 0 || number > 10000000) return 0}), 'width')
        .appendField("height")
        .appendField(new Blockly.FieldNumber('720', 0, 10000000, 0, (number) => {if (number < 0 || number > 10000000) return 0}), 'height')
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(100);
    this.setTooltip("Nnedi3 resizer uses OpenCL.\nIt can do scaling, color space conversion, etc.");
    this.setHelpUrl("https://github.com/mawen1250/VapourSynth-script/blob/master/nnedi3_resample-readme.txt");
    },
};

Blockly.Python['nnedi3_resize'] = function(block) {
    let width = block.getFieldValue('width');
    let height = block.getFieldValue('height');
    var code = qvs.format("{0} = qvs.Nnedi3Resize({0}, w={1}, h={2}, cl=True, device=2, list_device=False)\n", blocksParams.searchTargetClip(block), width, height);
    return code;
};

/// Anime4K
Blockly.Blocks['anime4k'] = {
    init: function() {
    this.appendDummyInput()
        .appendField("Anime4K")
        .appendField("GPUMode")
        .appendField(new Blockly.FieldNumber('1', 0, 10000, 0, (number) => {if (number < 0 || number > 10000) return 0}), 'gpu_mode')
        .appendField("ACNet")
        .appendField(new Blockly.FieldNumber('1', 0, 10000, 0, (number) => {if (number < 0 || number > 10000) return 0}), 'acnet')
        .appendField("zoomFactor")
        .appendField(new Blockly.FieldNumber('2', 0, 10000, 0, (number) => {if (number < 0 || number > 10000) return 0}), 'zoom_factor')
        .appendField("HDN")
        .appendField(new Blockly.FieldNumber('1', 0, 10000, 0, (number) => {if (number < 0 || number > 10000) return 0}), 'hdn')
        .appendField("HDNLevel")
        .appendField(new Blockly.FieldNumber('1', 1, 3, 0, (number) => {if (number < 1 || number > 3) return 1}), 'hdn_level')
    this.setInputsInline(false);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(100);
    this.setTooltip(`Anime4KCPP supports RGB24 and YUV 8bit(ACNet support YUV444,422,420, Anime4K09 support YUV444)
parameters: description (type [=default])
passes: Passes for processing (int [=2])
pushColorCount: Limit the number of color pushes, make sure the edge won't be too thin (int [=2])
strengthColor: Strength for pushing color,range 0 to 1,higher for thinner (double [=0.3])
strengthGradient: Strength for pushing gradient,range 0 to 1,higher for sharper (double [=1])
zoomFactor: upscaling ratio for resizing (double [=1])
ACNet: Enable ACNet (int [=0])
GPUMode: Enable GPU acceleration (int [=0])
HDN: Enable HDN for ACNet (int [=0])
HDNLevel: Set HDN level, higher for better denoising but may cause blur and lack of detail, range 1 to 3 (int [=1])
platformID, deviceID: For specifying the GPU (int [=0])
safeMode: usually faster, no extra pixels, but may use more memory, it must be enabled for YUV 8bit support, otherwise only RGB24 and YUV444 is supported (int [=1])`);
    this.setHelpUrl("https://github.com/TianZerL/Anime4KCPP/wiki/VapourSynth-plugin");
    },
};

Blockly.Python['anime4k'] = function(block) {
    let gpu_mode = block.getFieldValue('gpu_mode');
    let acnet = block.getFieldValue('acnet');
    let zoom_factor = block.getFieldValue('zoom_factor');
    let hdn = block.getFieldValue('hdn');
    let hdn_level = block.getFieldValue('hdn_level');

    var code = qvs.format("{0} = core.anime4kcpp.Anime4KCPP({0}, GPUMode={0}, ACNet={1}, zoomFactor={2}, HDN={3}, HDNLevel={4})\n", blocksParams.searchTargetClip(block), gpu_mode, acnet, zoom_factor, hdn, hdn_level);
    return code;
};

/// Crop
Blockly.Blocks['crop'] = {
    init: function() {
    this.appendDummyInput()
        .appendField("Crop")
        .appendField("left")
        .appendField(new Blockly.FieldNumber('0', 0, 2**10, 0, (number) => {if (number < 0 || number > 2**10) return 0}), 'left')
        .appendField("top")
        .appendField(new Blockly.FieldNumber('0', 0, 2**10, 0, (number) => {if (number < 0 || number > 2**10) return 0}), 'top')
        .appendField("right")
        .appendField(new Blockly.FieldNumber('0', 0, 2**10, 0, (number) => {if (number < 0 || number > 2**10) return 0}), 'right')
        .appendField("bottom")
        .appendField(new Blockly.FieldNumber('0', 0, 2**10, 0, (number) => {if (number < 0 || number > 2**10) return 0}), 'bottom')
    this.setInputsInline(false);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(100);
    this.setTooltip("Crops the frames in a clip.");
    this.setHelpUrl("http://www.vapoursynth.com/doc/functions/crop.html");
    },
};

Blockly.Python['crop'] = function(block) {
    let left = block.getFieldValue('left');
    let top = block.getFieldValue('top');
    let right = block.getFieldValue('right');
    let bottom = block.getFieldValue('bottom');
    var code = qvs.format("{0} = qvs.Crop({0}, l={1}, t={2}, r={3}, b={4})\n", blocksParams.searchTargetClip(block), left, top, right, bottom);
    return code;
};

/// FillMargins
Blockly.Blocks['fillmargins'] = {
    init: function() {
    this.appendDummyInput()
        .appendField("FillMargins")
        .appendField("left")
        .appendField(new Blockly.FieldNumber('0', 0, 2**10, 0, (number) => {if (number < 0 || number > 2**10) return 0}), 'left')
        .appendField("top")
        .appendField(new Blockly.FieldNumber('0', 0, 2**10, 0, (number) => {if (number < 0 || number > 2**10) return 0}), 'top')
        .appendField("right")
        .appendField(new Blockly.FieldNumber('0', 0, 2**10, 0, (number) => {if (number < 0 || number > 2**10) return 0}), 'right')
        .appendField("bottom")
        .appendField(new Blockly.FieldNumber('0', 0, 2**10, 0, (number) => {if (number < 0 || number > 2**10) return 0}), 'bottom')
    this.setInputsInline(false);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(100);
    this.setTooltip("This is a simple filter that fills the borders of a clip, without changing the clip's dimensions.");
    this.setHelpUrl("https://github.com/dubhater/vapoursynth-fillborders");
    },
};

Blockly.Python['fillmargins'] = function(block) {
    let left = block.getFieldValue('left');
    let top = block.getFieldValue('top');
    let right = block.getFieldValue('right');
    let bottom = block.getFieldValue('bottom');
    var code = qvs.format("{0} = qvs.FillMargins({0}, l={1}, t={2}, r={3}, b={4})\n", blocksParams.searchTargetClip(block), left, top, right, bottom);
    return code;
};

/// AddMargins
Blockly.Blocks['addmargins'] = {
    init: function() {
    this.appendDummyInput()
        .appendField("AddMargins")
        .appendField("left")
        .appendField(new Blockly.FieldNumber('0', 0, 2**10, 0, (number) => {if (number < 0 || number > 2**10) return 0}), 'left')
        .appendField("top")
        .appendField(new Blockly.FieldNumber('0', 0, 2**10, 0, (number) => {if (number < 0 || number > 2**10) return 0}), 'top')
        .appendField("right")
        .appendField(new Blockly.FieldNumber('0', 0, 2**10, 0, (number) => {if (number < 0 || number > 2**10) return 0}), 'right')
        .appendField("bottom")
        .appendField(new Blockly.FieldNumber('0', 0, 2**10, 0, (number) => {if (number < 0 || number > 2**10) return 0}), 'bottom')
        .appendField("fv")
        .appendField(new Blockly.FieldCheckbox("0"), "fv")
        .appendField("fh")
        .appendField(new Blockly.FieldCheckbox("0"), "fh")
        .appendField("blur")
        .appendField(new Blockly.FieldCheckbox("TRUE"), "blur")
        .appendField("radius")
        .appendField(new Blockly.FieldNumber("0", 0, 2**10, 0, (number) => {if (number < 0 || number > 2**10) return 0}), 'radius')
    this.setInputsInline(false);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(100);
    this.setTooltip("Add the margins instead of borders.");
    this.setHelpUrl("https://github.com/emako/qvs/tree/master/python/scripts");
    },
};

Blockly.Python['addmargins'] = function(block) {
    let left = block.getFieldValue('left');
    let top = block.getFieldValue('top');
    let right = block.getFieldValue('right');
    let bottom = block.getFieldValue('bottom');
    let fv = block.getFieldValue('fv') == "TRUE" ? "True" : "False";
    let fh = block.getFieldValue('fh') == "TRUE" ? "True" : "False";
    let blur = block.getFieldValue('blur') == "TRUE" ? "True" : "False";
    let radius = block.getFieldValue('radius');
    var code = qvs.format("{0} = qvs.AddMargins({0}, l={1}, t={2}, r={3}, b={4}, fv={5}, fh={6}, blur={7}, radius={8})\n", blocksParams.searchTargetClip(block), left, top, right, bottom, fv, fh, blur, radius);
    return code;
};

/// AddBorders
Blockly.Blocks['addborders'] = {
    init: function() {
    this.appendDummyInput()
        .appendField("AddBorders")
        .appendField("left")
        .appendField(new Blockly.FieldNumber('0', 0, 2**10, 0, (number) => {if (number < 0 || number > 2**10) return 0}), 'left')
        .appendField("top")
        .appendField(new Blockly.FieldNumber('0', 0, 2**10, 0, (number) => {if (number < 0 || number > 2**10) return 0}), 'top')
        .appendField("right")
        .appendField(new Blockly.FieldNumber('0', 0, 2**10, 0, (number) => {if (number < 0 || number > 2**10) return 0}), 'right')
        .appendField("bottom")
        .appendField(new Blockly.FieldNumber('0', 0, 2**10, 0, (number) => {if (number < 0 || number > 2**10) return 0}), 'bottom')
        .appendField("color")
        .appendField(new Blockly.FieldTextInput(""), "color")
    this.setInputsInline(false);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(100);
    this.setTooltip("This is a simple filter that fills the borders of a clip, without changing the clip's dimensions.");
    this.setHelpUrl("https://github.com/dubhater/vapoursynth-fillborders");
    },
};

Blockly.Python['addborders'] = function(block) {
    let left = block.getFieldValue('left');
    let top = block.getFieldValue('top');
    let right = block.getFieldValue('right');
    let bottom = block.getFieldValue('bottom');
    let color = block.getFieldValue('color');
	color = Blockly.Python.stringToColorArray(color);
    var code = qvs.format("{0} = core.std.AddBorders({0}, left={1}, top={2}, right={3}, bottom={4}, color={5})\n", blocksParams.searchTargetClip(block), left, top, right, bottom, color);
    return code;
};

// Descale
Blockly.Blocks['descale'] = {
    init: function() {
    this.appendDummyInput()
        .appendField("Descale")
        .appendField("algorithm")
        .appendField(new Blockly.FieldDropdown([["Debilinear", "Debilinear"], ["Debicubic", "Debicubic"], ["Delanczos", "Delanczos"], ["Despline16", "Despline16"], ["Despline36", "Despline36"], ["Despline64", "Despline64"]]), 'algorithm')
        .appendField("width")
        .appendField(new Blockly.FieldNumber('1280', 0, 10000000, 0, (number) => {if (number < 0 || number > 10000000) return 0}), 'width')
        .appendField("height")
        .appendField(new Blockly.FieldNumber('720', 0, 10000000, 0, (number) => {if (number < 0 || number > 10000000) return 0}), 'height')
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(100);
    this.setTooltip("VapourSynth plugin to undo upscaling. \nThe plugin itself only supports GrayS, RGBS, and YUV444PS input. \nThe included python wrapper supports YUV (every subsampling), Gray, and RGB of every bitdepth.");
    this.setHelpUrl("https://github.com/Irrational-Encoding-Wizardry/vapoursynth-descale");
    },
};

Blockly.Python['descale'] = function(block) {
    let algorithm = block.getFieldValue('algorithm');
    let width = block.getFieldValue('width');
    let height = block.getFieldValue('height');
    var code = qvs.format("{0} = qvs.{1}Resize({0}, width={2}, height={3}, yuv444=False, gray=False, chromaloc=None)\n", blocksParams.searchTargetClip(block), algorithm, width, height);
    return code;
};

/// ConvertToYV24
Blockly.Blocks['converttoyv24'] = {
	init: function() {
		this.appendDummyInput()
			.appendField("ConvertToYV24")
		this.setInputsInline(true);
		this.setPreviousStatement(true, null);
		this.setNextStatement(true, null);
		this.setColour(100);
		this.setTooltip("Format constants exactly describe a format. \n[YV24 <=> 444p] Color format of YV24 is equivalent to planar image, whom chroma is 4:4:4 (full chroma).");
		this.setHelpUrl("https://github.com/emako/qvs/tree/master/python/scripts");
	},
};

Blockly.Python['converttoyv24'] = function(block) {
	var code = qvs.format("{0} = qvs.ConvertToYV24({0})\n", blocksParams.searchTargetClip(block));
	return code;
};

/// ConvertToYV16
Blockly.Blocks['converttoyv16'] = {
	init: function() {
		this.appendDummyInput()
			.appendField("ConvertToYV16")
		this.setInputsInline(true);
		this.setPreviousStatement(true, null);
		this.setNextStatement(true, null);
		this.setColour(100);
		this.setTooltip("Format constants exactly describe a format. \n[YV16 <=> 422p] Color format of YV16 is equivalent to planar image, whom chroma is 4:2:2 (chroma shared between 2 horizontal pixels).");
		this.setHelpUrl("https://github.com/emako/qvs/tree/master/python/scripts");
	},
};

Blockly.Python['converttoyv16'] = function(block) {
	var code = qvs.format("{0} = qvs.ConvertToYV16({0})\n", blocksParams.searchTargetClip(block));
	return code;
};

/// ConvertToYUY2
Blockly.Blocks['converttoyuy2'] = {
	init: function() {
		this.appendDummyInput()
			.appendField("ConvertToYUY2")
		this.setInputsInline(true);
		this.setPreviousStatement(true, null);
		this.setNextStatement(true, null);
		this.setColour(100);
		this.setTooltip("Format constants exactly describe a format. \n[YUY2 <=> 422i] Color format of YUY2 is equivalent to interleaved image, whom chroma is 4:2:2 (chroma shared between 2 horizontal pixels).");
		this.setHelpUrl("https://github.com/emako/qvs/tree/master/python/scripts");
	},
};

Blockly.Python['converttoyuy2'] = function(block) {
	var code = qvs.format("{0} = qvs.ConvertToYUY2({0})\n", blocksParams.searchTargetClip(block));
	return code;
};

/// ConvertToYV12
Blockly.Blocks['converttoyv12'] = {
	init: function() {
		this.appendDummyInput()
			.appendField("ConvertToYV12")
		this.setInputsInline(true);
		this.setPreviousStatement(true, null);
		this.setNextStatement(true, null);
		this.setColour(100);
		this.setTooltip("Format constants exactly describe a format. \n[YV12 <=> 420p] Color format of YV12 is equivalent to planar image, whom chroma is 4:2:0 (chroma shared between 2 horizontal x 2 vertical pixels).");
		this.setHelpUrl("https://github.com/emako/qvs/tree/master/python/scripts");
	},
};

Blockly.Python['converttoyv12'] = function(block) {
	var code = qvs.format("{0} = qvs.ConvertToYV12({0})\n", blocksParams.searchTargetClip(block));
	return code;
};

/// ConvertToYV411
Blockly.Blocks['converttoyv411'] = {
	init: function() {
		this.appendDummyInput()
			.appendField("ConvertToYV411")
		this.setInputsInline(true);
		this.setPreviousStatement(true, null);
		this.setNextStatement(true, null);
		this.setColour(100);
		this.setTooltip("Format constants exactly describe a format. \n[YV411 <=> 411p] Color format of YV411 is equivalent to planar image, whom chroma is 4:1:1 (chroma shared between 4 vertical pixels).");
		this.setHelpUrl("https://github.com/emako/qvs/tree/master/python/scripts");
	},
};

Blockly.Python['converttoyv411'] = function(block) {
	var code = qvs.format("{0} = qvs.ConvertToYV411({0})\n", blocksParams.searchTargetClip(block));
	return code;
};

/// ConvertToY8
Blockly.Blocks['converttoy8'] = {
	init: function() {
		this.appendDummyInput()
			.appendField("ConvertToY8")
		this.setInputsInline(true);
		this.setPreviousStatement(true, null);
		this.setNextStatement(true, null);
		this.setColour(100);
		this.setTooltip("Format constants exactly describe a format. \n[Y8 <=> 400b] Color format of YV411 is equivalent to both planar and interleaved image, whom chroma is 4:0:0 (no chroma but IsYUV returns true).");
		this.setHelpUrl("https://github.com/emako/qvs/tree/master/python/scripts");
	},
};

Blockly.Python['converttoy8'] = function(block) {
	var code = qvs.format("{0} = qvs.ConvertToY8({0})\n", blocksParams.searchTargetClip(block));
	return code;
};

/// ConvertToRGB24
Blockly.Blocks['converttorgb24'] = {
	init: function() {
		this.appendDummyInput()
			.appendField("ConvertToRGB24")
		this.setInputsInline(true);
		this.setPreviousStatement(true, null);
		this.setNextStatement(true, null);
		this.setColour(100);
		this.setTooltip("Format constants exactly describe a format.");
		this.setHelpUrl("https://github.com/emako/qvs/tree/master/python/scripts");
	},
};

Blockly.Python['converttorgb24'] = function(block) {
	var code = qvs.format("{0} = qvs.ConvertToRGB24({0})\n", blocksParams.searchTargetClip(block));
	return code;
};

/// ConvertToRGB48
Blockly.Blocks['converttorgb48'] = {
	init: function() {
		this.appendDummyInput()
			.appendField("ConvertToRGB48")
		this.setInputsInline(true);
		this.setPreviousStatement(true, null);
		this.setNextStatement(true, null);
		this.setColour(100);
		this.setTooltip("Format constants exactly describe a format.");
		this.setHelpUrl("https://github.com/emako/qvs/tree/master/python/scripts");
	},
};

Blockly.Python['converttorgb48'] = function(block) {
	var code = qvs.format("{0} = qvs.ConvertToRGB48({0})\n", blocksParams.searchTargetClip(block));
	return code;
};

/// ConvertToRGBS
Blockly.Blocks['converttorgbs'] = {
	init: function() {
		this.appendDummyInput()
			.appendField("ConvertToRGBS")
		this.setInputsInline(true);
		this.setPreviousStatement(true, null);
		this.setNextStatement(true, null);
		this.setColour(100);
		this.setTooltip("Format constants exactly describe a format.");
		this.setHelpUrl("https://github.com/emako/qvs/tree/master/python/scripts");
	},
};

Blockly.Python['converttorgbs'] = function(block) {
	var code = qvs.format("{0} = qvs.ConvertToRGBS({0})\n", blocksParams.searchTargetClip(block));
	return code;
};

/// ConvertToGrey
Blockly.Blocks['converttogrey'] = {
	init: function() {
		this.appendDummyInput()
			.appendField("ConvertToGrey")
		this.setInputsInline(true);
		this.setPreviousStatement(true, null);
		this.setNextStatement(true, null);
		this.setColour(100);
		this.setTooltip("Format constants exactly describe a format.");
		this.setHelpUrl("https://github.com/emako/qvs/tree/master/python/scripts");
	},
};

Blockly.Python['converttogrey'] = function(block) {
	var code = qvs.format("{0} = qvs.ConvertToGrey({0})\n", blocksParams.searchTargetClip(block));
	return code;
};

/// Depth
Blockly.Blocks['depth'] = {
	init: function() {
		this.appendDummyInput()
			.appendField("Depth")
			.appendField("depth")
            .appendField(new Blockly.FieldNumber('16', 1, 16, 0, (number) => Math.floor(number)), 'depth')
		this.setInputsInline(true);
		this.setPreviousStatement(true, null);
		this.setNextStatement(true, null);
		this.setColour(100);
		this.setTooltip("Bit depth conversion with dithering (if needed). \nIt's a wrapper for fmtc.bitdepth and zDepth(core.resize/zimg). \nOnly constant format is supported, frame properties of the input clip is mostly ignored (only zDepth is able to use it).");
		this.setHelpUrl("https://github.com/HomeOfVapourSynthEvolution/mvsfunc");
	},
};

Blockly.Python['depth'] = function(block) {
    let depth = block.getFieldValue('depth');
	var code = qvs.format("{0} = mvf.Depth({0}, depth={1})\n", blocksParams.searchTargetClip(block), depth);
	return code;
};

/// GetPlane
Blockly.Blocks['getplane'] = {
	init: function() {
		this.appendDummyInput()
			.appendField("GetPlane")
			.appendField("index")
            .appendField(new Blockly.FieldNumber('0', 0, 2, 0, (number) => Math.floor(number)), 'index')
		this.setInputsInline(true);
		this.setPreviousStatement(true, null);
		this.setNextStatement(true, null);
		this.setColour(100);
		this.setTooltip("Get clip gray plane by index.");
		this.setHelpUrl("https://github.com/emako/qvs/tree/master/python/scripts");
	},
};

Blockly.Python['getplane'] = function(block) {
    let i = block.getFieldValue('i');
	var code = qvs.format("{0} = qvs.GetPlane({0}, i={1})\n", blocksParams.searchTargetClip(block), i);
	return code;
};

/// ToYUV
Blockly.Blocks['toyuv'] = {
	init: function() {
		this.appendDummyInput()
			.appendField("ToYUV")
			.appendField("css")
			.appendField(new Blockly.FieldDropdown(Blockly.Blocks.createDropdownArray(getChromaSubSamplings(true))), 'css')
		this.setInputsInline(true);
		this.setPreviousStatement(true, null);
		this.setNextStatement(true, null);
		this.setColour(100);
		this.setTooltip("Convert any color space to YUV/YCoCg with/without sub-sampling.");
		this.setHelpUrl("https://github.com/HomeOfVapourSynthEvolution/mvsfunc");
	},
};

Blockly.Python['toyuv'] = function(block) {
    let css = block.getFieldValue('css');
    if (css != "None") {
        css = qvs.format("'{0}'", css);
    }
	var code = qvs.format("{0} = mvf.ToYUV({0}, css={1})\n", blocksParams.searchTargetClip(block), css);
	return code;
};

/// ToRGB
Blockly.Blocks['torgb'] = {
	init: function() {
		this.appendDummyInput()
			.appendField("ToRGB")
			.appendField("matrix")
			.appendField(new Blockly.FieldDropdown(Blockly.Blocks.createDropdownArray(getMatrixs(true))), 'matrix')
		this.setInputsInline(true);
		this.setPreviousStatement(true, null);
		this.setNextStatement(true, null);
		this.setColour(100);
		this.setTooltip("Convert any color space to full range RGB.");
		this.setHelpUrl("https://github.com/HomeOfVapourSynthEvolution/mvsfunc");
	},
};

Blockly.Python['torgb'] = function(block) {
    let matrix = block.getFieldValue('matrix');
    if (matrix != "None" && matrix != "Unspecified" && matrix != "Not specified") {
        matrix = qvs.format("'{0}'", matrix);
    }
    else {
        matrix = "None";
    }
	var code = qvs.format("{0} = mvf.ToRGB({0}, matrix={1})\n", blocksParams.searchTargetClip(block), matrix);
	return code;
};

