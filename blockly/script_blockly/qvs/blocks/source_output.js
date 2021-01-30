'use strict';

/** Category List:
Source/Output
*/

/// LibavSMASHSource
Blockly.Blocks['libavsmashsource'] = {
	init: function() {
		this.appendDummyInput()
			.appendField("LibavSMASHSource")
			.appendField(new Blockly.FieldTextInput(""), "path")
			.appendField("fpsnum")
			.appendField(new Blockly.FieldNumber('0', 0, 10000, 0, (number) => {if (number < 0 || number > 10000) return 0}), 'fpsnum')
			.appendField("fpsden")
			.appendField(new Blockly.FieldNumber('1', 1, 10000, 0, (number) => {if (+number < 1 || +number > 10000) return 1}), 'fpsden')
			.appendField("format")
			.appendField(new Blockly.FieldDropdown([["None", ""], ["YUV420P8", "YUV420P8"], ["YUV422P8", "YUV422P8"], ["YUV444P8", "YUV444P8"], ["YUV410P8", "YUV410P8"], ["YUV411P8", "YUV411P8"], ["YUV440P8", "YUV440P8"], ["YUV420P9", "YUV420P9"], ["YUV422P9", "YUV422P9"], ["YUV420P10", "YUV420P10"], ["YUV422P10", "YUV422P10"], ["YUV444P10", "YUV444P10"], ["YUV420P16", "YUV420P16"], ["YUV422P16", "YUV422P16"], ["YUV444P16", "YUV444P16"], ["RGB24", "RGB24"], ["RGB27", "RGB27"], ["RGB30", "RGB30"], ["RGB48", "RGB48"]]), 'format')
			.appendField("decoder")
			.appendField(new Blockly.FieldDropdown([["None", ""], ["h264_qsv", "h264_qsv"], ["h264_cuvid", "h264_cuvid"], ["hevc_qsv", "hevc_qsv"], ["hevc_cuvid", "hevc_cuvid"], ["mpeg2_qsv", "mpeg2_qsv"], ["mpeg2_cuvid", "mpeg2_cuvid"], ["mpeg4_cuvid", "mpeg4_cuvid"], ["vp9_cuvid", "vp9_cuvid"]]), 'decoder');
		this.appendValueInput("load");
		this.setInputsInline(true);
		this.setPreviousStatement(true, null);
		this.setNextStatement(true, null);
		this.setColour(330);
		this.setTooltip("LSMASHSource for VapourSynth.");
		this.setHelpUrl("https://github.com/VFR-maniac/L-SMASH-Works/tree/master/VapourSynth");
	},
	contextMenu: new BlockContextMenu(),
};

Blockly.Python['libavsmashsource'] = function(block) {
	let path = block.getFieldValue('path');
	let fpsnum = block.getFieldValue('fpsnum');
	let fpsden = block.getFieldValue('fpsden');
	let format = block.getFieldValue('format')
	let decoder = block.getFieldValue('decoder');
	var code = blocksParams.searchTargetClip(block) + qvs.format(" = core.lsmas.LibavSMASHSource(u'{0}', fpsnum={1}, fpsden={2}, format='{3}', decoder='{4}')\n", qvs.unifySeparator(path), fpsnum, fpsden, format, decoder);
	return code;
};

/// LWLibavSource
Blockly.Blocks['lwlibavsource'] = {
	init: function() {
		this.appendDummyInput()
			.appendField("LWLibavSource")
			.appendField(new Blockly.FieldTextInput(""), "path")
			.appendField("fpsnum")
			.appendField(new Blockly.FieldNumber('0', 0, 10000, 0, (number) => {if (number < 0 || number > 10000) return 0}), 'fpsnum')
			.appendField("fpsden")
			.appendField(new Blockly.FieldNumber('1', 1, 10000, 0, (number) => {if (number < 1 || number > 10000) return 1}), 'fpsden')
			.appendField("format")
			.appendField(new Blockly.FieldDropdown([["None", ""], ["YUV420P8", "YUV420P8"], ["YUV422P8", "YUV422P8"], ["YUV444P8", "YUV444P8"], ["YUV410P8", "YUV410P8"], ["YUV411P8", "YUV411P8"], ["YUV440P8", "YUV440P8"], ["YUV420P9", "YUV420P9"], ["YUV422P9", "YUV422P9"], ["YUV420P10", "YUV420P10"], ["YUV422P10", "YUV422P10"], ["YUV444P10", "YUV444P10"], ["YUV420P16", "YUV420P16"], ["YUV422P16", "YUV422P16"], ["YUV444P16", "YUV444P16"], ["RGB24", "RGB24"], ["RGB27", "RGB27"], ["RGB30", "RGB30"], ["RGB48", "RGB48"]]), 'format')
			.appendField("decoder")
			.appendField(new Blockly.FieldDropdown([["None", ""], ["h264_qsv", "h264_qsv"], ["h264_cuvid", "h264_cuvid"], ["hevc_qsv", "hevc_qsv"], ["hevc_cuvid", "hevc_cuvid"], ["mpeg2_qsv", "mpeg2_qsv"], ["mpeg2_cuvid", "mpeg2_cuvid"], ["mpeg4_cuvid", "mpeg4_cuvid"], ["vp9_cuvid", "vp9_cuvid"]]), 'decoder');
		this.appendValueInput("load");
		this.setInputsInline(true);
		this.setPreviousStatement(true, null);
		this.setNextStatement(true, null);
		this.setColour(330);
		this.setTooltip("LSMASHSource for VapourSynth.");
		this.setHelpUrl("https://github.com/VFR-maniac/L-SMASH-Works/tree/master/VapourSynth");
	},
	contextMenu: new BlockContextMenu(),
};

Blockly.Python['lwlibavsource'] = function(block) {
	let path = block.getFieldValue('path');
	let fpsnum = block.getFieldValue('fpsnum');
	let fpsden = block.getFieldValue('fpsden');
	let format = block.getFieldValue('format');
	let decoder = block.getFieldValue('decoder');
	var code = blocksParams.searchTargetClip(block) + qvs.format(" = core.lsmas.LWLibavSource(u'{0}', fpsnum={1}, fpsden={2}, format='{3}', decoder='{4}')\n", qvs.unifySeparator(path), fpsnum, fpsden, format, decoder);
	return code;
};

/// FFmpegSource
Blockly.Blocks['ffmpegsource'] = {
	init: function() {
		this.appendDummyInput()
			.appendField("FFmpegSource")
			.appendField(new Blockly.FieldTextInput(""), "path")
			.appendField("track")
			.appendField(new Blockly.FieldNumber('-1', -1, 255, 0, (number) => {if (number < -1 || number > 10000) return -1}), 'track')
			.appendField("fpsnum")
			.appendField(new Blockly.FieldNumber('-1', -1, 10000, 0, (number) => {if (number < -1 || number > 10000) return -1}), 'fpsnum')
			.appendField("fpsden")
			.appendField(new Blockly.FieldNumber('1', -1, 10000, 0, (number) => {if (number < 1 || number > 10000) return 1}), 'fpsden');
		this.appendValueInput("load");
		this.setInputsInline(true);
		this.setPreviousStatement(true, null);
		this.setNextStatement(true, null);
		this.setColour(330);
		this.setTooltip("FFmpegSource 2 for VapourSynth.");
		this.setHelpUrl("https://github.com/FFMS/ffms2/blob/master/doc/ffms2-vapoursynth.md");
	},
	contextMenu: new BlockContextMenu(),
};

Blockly.Python['ffmpegsource'] = function(block) {
	let path = block.getFieldValue('path');
	let track = block.getFieldValue('track');
	let fpsnum = block.getFieldValue('fpsnum');
	let fpsden = block.getFieldValue('fpsden');
	var code = blocksParams.searchTargetClip(block) + qvs.format(" = core.ffms2.Source(u'{0}', track={1}, fpsnum={2}, fpsden={3}, timecodes='')\n", qvs.unifySeparator(path), track, fpsnum, fpsden);
	return code;
};

/// DGSourceNV
Blockly.Blocks['dgsourcenv'] = {
	init: function() {
		this.appendDummyInput()
			.appendField("DGSourceNV")
			.appendField(new Blockly.FieldTextInput(""), "path")
			.appendField("deinterlace")
			.appendField(new Blockly.FieldDropdown([["None", "0"], ["Single Rate", "1"], ["Double Rate", "2"]]), 'deinterlace')
			.appendField("resize_w")
			.appendField(new Blockly.FieldNumber('0', 0, 10000000, 0, (number) => {if (number < 0 || number > 100000000) return 0}), 'resize_w')
			.appendField("resize_h")
			.appendField(new Blockly.FieldNumber('0', 0, 10000000, 0, (number) => {if (number < 0 || number > 100000000) return 0}), 'resize_h')
			.appendField("fieldop")
				.appendField(new Blockly.FieldDropdown([["Honor Pulldown Falgs", "0"], ["Force Film", "1"], ["Ignore Pulldown", "2"]]), 'fieldop');
		this.appendValueInput("load");
		this.setInputsInline(true);
		this.setPreviousStatement(true, null);
		this.setNextStatement(true, null);
		this.setColour(330);
		this.setTooltip("DGSourceNV is a source plugin suite for AVC/HEVC/MPG/VC1 video.");
		this.setHelpUrl("http://rationalqm.us/dgdecnv/QuickStart.html");
	},
	contextMenu: new BlockContextMenu(),
};

Blockly.Python['dgsourcenv'] = function(block) {
	let path = block.getFieldValue('path');
	let deinterlace = block.getFieldValue('deinterlace');
	let resize_w = block.getFieldValue('resize_w');
	let resize_h = block.getFieldValue('resize_h');
	let fieldop = block.getFieldValue('fieldop');
	var code = blocksParams.searchTargetClip(block) + qvs.format(" = qvs.DGSourceNV(u'{0}', audio=True, force_index=False, deinterlace={1}, resize_w={2}, resize_h={3}, use_top_field=True, fieldop={4}, fulldepth=False)\n", qvs.unifySeparator(path), deinterlace, resize_w, resize_h, fieldop);
	return code;
};

/// DGSource
Blockly.Blocks['dgsource'] = {
	init: function() {
		this.appendDummyInput()
			.appendField("DGSource")
			.appendField(new Blockly.FieldTextInput(""), "path")
			.appendField("fieldop")
			.appendField(new Blockly.FieldDropdown([["Honor Pulldown Falgs", "0"], ["Force Film", "1"], ["Ignore Pulldown", "2"]]), 'fieldop');
		this.appendValueInput("load");
		this.setInputsInline(true);
		this.setPreviousStatement(true, null);
		this.setNextStatement(true, null);
		this.setColour(330);
		this.setTooltip("Create an index of an MPEG video stream using DGIndex, \nand use D2V Source to load the indexed file.");
		this.setHelpUrl("http://rationalqm.us/dgmpgdec/DGIndexManual.html");
	},
	contextMenu: new BlockContextMenu(),
};

Blockly.Python['dgsource'] = function(block) {
	let path = block.getFieldValue('path');
	let fieldop = block.getFieldValue('fieldop');
	var code = blocksParams.searchTargetClip(block) + qvs.format(" = qvs.DGSource(u'{0}', audio=True, force_index=False, field_operation={1}, threads=0, nocrop=True, rff=True)\n", qvs.unifySeparator(path), fieldop);
	return code;
};

/// D2VSource
Blockly.Blocks['d2vsource'] = {
	init: function() {
		this.appendDummyInput()
			.appendField("D2VSource")
			.appendField(new Blockly.FieldTextInput(""), "path");
		this.appendValueInput("load");
		this.setInputsInline(true);
		this.setPreviousStatement(true, null);
		this.setNextStatement(true, null);
		this.setColour(330);
		this.setTooltip("D2V Source for VapourSynth.");
		this.setHelpUrl("https://github.com/dwbuiten/d2vsource");
	},
	contextMenu: new BlockContextMenu(),
};

Blockly.Python['d2vsource'] = function(block) {
	let path = block.getFieldValue('path');
	var code = blocksParams.searchTargetClip(block) + qvs.format(" = qvs.D2VSource(u'{0}', audio=True, force_index=False, threads=0, nocrop=True, rff=True)\n", qvs.unifySeparator(path));
	return code;
};

/// DirectShowSource
Blockly.Blocks['directshowsource'] = {
	init: function() {
		this.appendDummyInput()
			.appendField("DirectShowSource")
			.appendField(new Blockly.FieldTextInput(""), "path")
			.appendField("fps")
			.appendField(new Blockly.FieldNumber('0', 0, 10000, 0, (number) => {if (number < 0 || number > 10000) return 0}), 'fps')
			.appendField("convertfps")
			.appendField(new Blockly.FieldDropdown([["True", "True"], ["False", "False"]]), 'convertfps');
		this.appendValueInput("load");
		this.setInputsInline(true);
		this.setPreviousStatement(true, null);
		this.setNextStatement(true, null);
		this.setColour(330);
		this.setTooltip("DirectShowSource reads media files using Microsoft DirectShow.");
		this.setHelpUrl("http://avisynth.nl/index.php/DirectShowSource");
	},
	contextMenu: new BlockContextMenu(),
};

Blockly.Python['directshowsource'] = function(block) {
	let path = block.getFieldValue('path');
	let fps = block.getFieldValue('fps');
	let convertfps = block.getFieldValue('convertfps');
	if (fps == 0) {
	fps = 'None';
	}
	var code = blocksParams.searchTargetClip(block) + qvs.format(" = qvs.DirectShowSource(u'{0}', , fps={1}, convertfps={2})\n", qvs.unifySeparator(path), fps, convertfps);
	return code;
};

/// QRCodeSource
Blockly.Blocks['qrcodesource'] = {
	init: function() {
		this.appendDummyInput()
			.appendField("QRCodeSource")
			.appendField("message")
			.appendField(new Blockly.FieldTextInput("enter your message"), "message")
			.appendField("width")
			.appendField(new Blockly.FieldNumber('150', 24, 2**10, 0, (number) => {if (number < 24 || number > 2**10) return 24}), 'width')
			.appendField("height")
			.appendField(new Blockly.FieldNumber('150', 24, 2**10, 0, (number) => {if (number < 24 || number > 2**10) return 24}), 'height')
		this.setInputsInline(true);
		this.setPreviousStatement(true, null);
		this.setNextStatement(true, null);
		this.setColour(330);
		this.setTooltip("Vapoursynth plugin to provide a means to embed QR codes in video.");
		this.setHelpUrl("https://github.com/jeremypoulter/QRCodeSource");
	},
};

Blockly.Python['qrcodesource'] = function(block) {
	let message = block.getFieldValue('message');
	let width = block.getFieldValue('width');
	let height = block.getFieldValue('height');
	var code = qvs.format(`{0} = core.qr.Code(message=u'{1}', version=0, error_correction='H')\n{0} = core.resize.Point({0}, width={2}, height={3})\n`, blocksParams.searchTargetClip(block), message, width, height);
	return code;
};

/// BlankClip
Blockly.Blocks['blankclip'] = {
	init: function() {
		this.appendDummyInput()
			.appendField("BlankClip")
			.appendField("width")
			.appendField(new Blockly.FieldNumber("0", 0, 2**10, 0, (number) => {if (number < -1 || number > 2**10) return 0}), "width")
			.appendField("height")
			.appendField(new Blockly.FieldNumber('0', 0, 2**10, 0, (number) => {if (number < -1 || number > 2**10) return 0}), 'height')
			.appendField("format")
			.appendField(new Blockly.FieldDropdown(Blockly.Blocks.createDropdownArray(getFormatConstants(true))), 'format')
			.appendField("length")
			.appendField(new Blockly.FieldNumber('1', 1, 2**52, 0, (number) => {if (number < 1 || number > 2**52) return 1}), 'length')
			.appendField("fpsnum")
			.appendField(new Blockly.FieldNumber('0', 0, 2**52, 0, (number) => {if (number < 0 || number > 2**52) return 0}), 'fpsnum')
			.appendField("fpsden")
			.appendField(new Blockly.FieldNumber('0', 0, 2**52, 0, (number) => {if (number < 0 || number > 2**52) return 0}), 'fpsden')
			.appendField("color")
			.appendField(new Blockly.FieldTextInput(""), "color")
		this.setInputsInline(true);
		this.setPreviousStatement(true, null);
		this.setNextStatement(true, null);
		this.setColour(330);
		this.setTooltip("Generates a new empty clip.");
		this.setHelpUrl("http://www.vapoursynth.com/doc/functions/blankclip.html");
	},
};

Blockly.Python['blankclip'] = function(block) {
	var setNoneWhenZero = (p) => { return p == 0 ? "None" : p };
	let target = blocksParams.searchTargetClip(block, false);
	let clip = blocksParams.searchTargetClip(block, true) || "None";
	let width = setNoneWhenZero(block.getFieldValue('width'));
	let height = setNoneWhenZero(block.getFieldValue('height'));
	let format = block.getFieldValue('format');
    let length = block.getFieldValue('length');
    let fpsnum = setNoneWhenZero(block.getFieldValue('fpsnum'));
    let fpsden = setNoneWhenZero(block.getFieldValue('fpsden'));
	let color = block.getFieldValue('color');
	color = Blockly.Python.stringToColorArray(color);
	if (format != "None") {
		format = qvs.format("vs.{0}", format);
	}
	var code = qvs.format("{0} = core.std.BlankClip({1}, width={2}, height={3}, format={4}, length={5}, fpsnum={6}, fpsden={7}, color={8}, keep=1)\n", target, clip, width, height, format, length, fpsnum, fpsden, color);
	return code;
};

/// Colorbars
Blockly.Blocks['colorbars'] = {
	init: function() {
		this.appendDummyInput()
			.appendField("Colorbars")
			.appendField("width")
			.appendField(new Blockly.FieldNumber("640", 1, 2**10, 0, (number) => {if (number < 1 || number > 2**10) return 1}), "width")
			.appendField("height")
			.appendField(new Blockly.FieldNumber('480', 1, 2**10, 0, (number) => {if (number < 1 || number > 2**10) return 1}), 'height')
			.appendField("format")
			.appendField(new Blockly.FieldDropdown(Blockly.Blocks.createDropdownArray(getFormatConstants(true))), 'format')
			.appendField("length")
			.appendField(new Blockly.FieldNumber('1', 1, 2**52, 0, (number) => {if (number < 1 || number > 2**52) return 1}), 'length')
			.appendField("fpsnum")
			.appendField(new Blockly.FieldNumber('0', 0, 2**52, 0, (number) => {if (number < 0 || number > 2**52) return 0}), 'fpsnum')
			.appendField("fpsden")
			.appendField(new Blockly.FieldNumber('0', 0, 2**52, 0, (number) => {if (number < 0 || number > 2**52) return 0}), 'fpsden')
			.appendField("duration")
			.appendField(new Blockly.FieldNumber('600', 1, 2**52, 0, (number) => {if (number < 1) return 1}), 'duration')
		this.setInputsInline(true);
		this.setPreviousStatement(true, null);
		this.setNextStatement(true, null);
		this.setColour(330);
		this.setTooltip("Vapoursynth plugin to provide a means to embed QR codes in video.");
		this.setHelpUrl("https://github.com/emako/qvs/tree/master/python/scripts");
	},
};

Blockly.Python['colorbars'] = function(block) {
	let target = blocksParams.searchTargetClip(block, false);
	let width = setNoneWhenZero(block.getFieldValue('width'));
	let height = setNoneWhenZero(block.getFieldValue('height'));
	let format = block.getFieldValue('format');
    let fpsnum = setNoneWhenZero(block.getFieldValue('fpsnum'));
    let fpsden = setNoneWhenZero(block.getFieldValue('fpsden'));
	let duration = block.getFieldValue('duration');
	if (format != "None") {
		format = qvs.format("vs.{0}", format);
	}
	// Colorbars(width=640, height=480, fpsnum=25, fpsden=1, format=vs.RGB24, duration=600)
	var code = qvs.format("{0} = qvs.Colorbars(width={1}, height={2}, format={3}, fpsnum={4}, fpsden={5}, duration={6})\n", target, width, height, format, fpsnum, fpsden, duration);
	return code;
};

/// ImageSource
Blockly.Blocks['imagesource'] = {
	init: function() {
		this.appendDummyInput()
			.appendField("ImageSource")
			.appendField(new Blockly.FieldTextInput(""), "filename")
			.appendField("firstnum")
			.appendField(new Blockly.FieldNumber('0', 0, 2**52, 0, (number) => {if (number < 0) return 0}), 'firstnum')
			.appendField("mismatch")
			.appendField(new Blockly.FieldCheckbox('0'), 'mismatch')
			.appendField("alpha")
			.appendField(new Blockly.FieldCheckbox('0'), 'alpha')
			.appendField("float_output")
			.appendField(new Blockly.FieldCheckbox('0'), 'float_output')
		this.appendValueInput("load");
		this.setInputsInline(true);
		this.setPreviousStatement(true, null);
		this.setNextStatement(true, null);
		this.setColour(330);
		this.setTooltip(`The filename argument has two main modes. For example "image%06d.png" or "/images/%d.jpg" is common usage. 
Possible output formats when reading: 8-16 bit integer and 32 bit float. 
Note that by default 8-16 bit images are returned as integer and 32 bit images as float. 
When reading half precision float images you have to manually set *float_output* to have the unmodified floating point range returned. 
Read is a simple function for reading single or series of images and returning them as a clip.`);
		this.setHelpUrl("https://github.com/vapoursynth/vapoursynth/blob/master/doc/plugins/imwri.rst");
	},
	contextMenu: new BlockContextMenu(),
};

Blockly.Python['imagesource'] = function(block) {
	let filename = block.getFieldValue('filename');
	let firstnum = block.getFieldValue('firstnum');
	let mismatch = block.getFieldValue('mismatch') == "TRUE" ? "True" : "False";
	let alpha = block.getFieldValue('alpha') == "TRUE" ? "True" : "False";
	let float_output = block.getFieldValue('float_output') == "TRUE" ? "True" : "False";
	let target_clip = blocksParams.searchTargetClip(block);

	if (alpha == "True") {
		let image = Blockly.getMainWorkspace().getVariable("image", "");
		if (image == null || image == undefined) {
			Blockly.getMainWorkspace().createVariable("image", "", Blockly.utils.genUid());
		}
		target_clip = qvs.format("{0}, image", target_clip);
	}
	var code = qvs.format("{0} = core.imwri.Read(u'{1}', firstnum={2}, mismatch={2}, alpha={3}, float_output={4})\n", target_clip, qvs.unifySeparator(filename), firstnum, mismatch, alpha, float_output);
	return code;
};

/// ImageWriter
Blockly.Blocks['imagewriter'] = {
	init: function() {
		this.appendDummyInput()
			.appendField("ImageWriter")
			.appendField("imgformat")
			.appendField(new Blockly.FieldDropdown([["JPEG", "JPEG"], ["PNG", "PNG"], ["DPX", "DPX"]]), 'imgformat')
			.appendField("filename")
			.appendField(new Blockly.FieldTextInput(""), "filename")
			.appendField("firstnum")
			.appendField(new Blockly.FieldNumber('75', 0, 2**52, 0, (number) => {if (number < 0) return 0}), 'firstnum')
			.appendField("quality")
			.appendField(new Blockly.FieldNumber('0', 0, 100, 0, (number) => {if (number < 0) return 0; else if (number > 100) return 100;}), 'quality')
			.appendField("dither")
			.appendField(new Blockly.FieldCheckbox('1'), 'dither')
			.appendField("overwrite")
			.appendField(new Blockly.FieldCheckbox('0'), 'overwrite')
			.appendField("alpha")
			.appendField(new Blockly.FieldCheckbox('FALSE'), 'alpha_enable')
			.appendField(new Blockly.FieldVariable('image'), 'alpha')
		this.setInputsInline(true);
		this.setPreviousStatement(true, null);
		this.setNextStatement(true, null);
		this.setColour(330);
		this.setTooltip(`Write will write each frame to disk as it's requested. If a frame is never requested it's also never written to disk. \nRGB and Gray supported. \nThe filename string must have one or more frame number substitutions. The syntax is printf style. For example "image%06d.png" or "/images/%d.jpg" is common usage.`);
		this.setHelpUrl("https://github.com/vapoursynth/vapoursynth/blob/master/doc/plugins/imwri.rst");
	},
};

Blockly.Python['imagewriter'] = function(block) {
	let clip = blocksParams.searchTargetClip(block);
	let imgformat = block.getFieldValue('imgformat');
	let filename = block.getFieldValue('filename');
	let firstnum = block.getFieldValue('firstnum');
	let quality = block.getFieldValue('quality');
	let dither = block.getFieldValue('dither') == "TRUE" ? "True" : "False";
	let overwrite = block.getFieldValue('overwrite') == "TRUE" ? "True" : "False";
	let alpha_enable = block.getFieldValue('alpha_enable');
	let alpha = "None";
	if (alpha_enable == "TRUE") {
		alpha = block.getFieldVariableValue('alpha');
	}
	var code = qvs.format("core.imwri.Write({0}, imgformat='{1}', filename=u'{2}', firstnum={3}, quality={4}, dither={5}, overwrite={6}, alpha={7})\n", clip, imgformat, qvs.unifySeparator(filename), firstnum, quality, dither, overwrite, alpha);
	return code;
};

/// Import
Blockly.Blocks['import'] = {
	init: function() {
		this.appendDummyInput()
			.appendField("Import")
			.appendField(new Blockly.FieldTextInput(""), "file");
		this.appendValueInput("load");
		this.setInputsInline(true);
		this.setPreviousStatement(true, null);
		this.setNextStatement(true, null);
		this.setColour(330);
		this.setTooltip("Allows for easy import of your *.vpy");
		this.setHelpUrl("https://git.concertos.live/AHD/awsmfunc");
	},
	contextMenu: new BlockContextMenu("Open Vapoursynth Script file", "Vapoursynth Script (*.vpy)"),
};

Blockly.Python['import'] = function(block) {
	let file = block.getFieldValue('file');
	var code = blocksParams.searchTargetClip(block) + qvs.format(" = qvs.Import(u'{0}', dont_write_bytecode=True)\n", qvs.unifySeparator(file));
	return code;
};

/// Trim
Blockly.Blocks['trim'] = {
	init: function() {
		this.appendDummyInput()
			.appendField("Trim")
			.appendField("first")
            .appendField(new Blockly.FieldNumber('0', 0, 2**52, 0, (number) => {if (number < 0) return 0}), 'first')
			.appendField("last")
            .appendField(new Blockly.FieldNumber('0', 0, 2**52, 0, (number) => {if (number < 0) return 0}), 'last')
			.appendField("using_operator")
            .appendField(new Blockly.FieldCheckbox('FALSE'), 'using_operator')
		this.setInputsInline(true);
		this.setPreviousStatement(true, null);
		this.setNextStatement(true, null);
		this.setColour(330);
		this.setTooltip("Trim returns a clip with only the frames between the arguments first and last,\n or a clip of length frames, starting at first.");
		this.setHelpUrl("http://www.vapoursynth.com/doc/functions/trim.html");
	},
};

Blockly.Python['trim'] = function(block) {
	let first = block.getFieldValue('first');
	let last = block.getFieldValue('last');
	var using_operator = block.getFieldValue("using_operator") == "TRUE" ? true : false;
	var code = "";
	if (using_operator) {
		var code = qvs.format("{0} = {0}[{1}:{2}]\n", blocksParams.searchTargetClip(block), first, last);
	}
	else {
		var code = qvs.format("{0} = core.std.Trim({0}, first={1}, last={2})\n", blocksParams.searchTargetClip(block), first, last);
	}
	return code;
};

/// Trim
Blockly.Blocks['splice'] = {
	init: function() {
		this.appendDummyInput()
			.appendField("Splice")
			.appendField("clipa")
			.appendField(new Blockly.FieldVariable('src'), 'clipa')
			.appendField("clipb")
			.appendField(new Blockly.FieldVariable('src'), 'clipb')
			.appendField("using_operator")
            .appendField(new Blockly.FieldCheckbox('TRUE'), 'using_operator')
		this.setInputsInline(true);
		this.setPreviousStatement(true, null);
		this.setNextStatement(true, null);
		this.setColour(330);
		this.setTooltip("Returns a clip with all clips appended in the given order.");
		this.setHelpUrl("http://www.vapoursynth.com/doc/functions/splice.html");
	},
};

Blockly.Python['splice'] = function(block) {
    var clipa = block.getFieldVariableValue("clipa");
    var clipb = block.getFieldVariableValue("clipb");
	var using_operator = block.getFieldValue("using_operator") == "TRUE" ? true : false;
	var code = "";
	if (using_operator) {
		code = qvs.format("{0} = {1} + {2}\n", blocksParams.searchTargetClip(block), clipa, clipb);
	}
	else {
		code = qvs.format("{0} = core.std.Splice([{1}, {2}])\n", blocksParams.searchTargetClip(block), clipa, clipb);
	}
	return code;
};

/// Loop
Blockly.Blocks['loop'] = {
	init: function() {
		this.appendDummyInput()
			.appendField("Loop")
			.appendField("times")
            .appendField(new Blockly.FieldNumber('0', 0, 2**52, 0, (number) => {if (number < 0) return 0}), 'times')
			.appendField("using_operator")
            .appendField(new Blockly.FieldCheckbox('TRUE'), 'using_operator')
		this.setInputsInline(true);
		this.setPreviousStatement(true, null);
		this.setNextStatement(true, null);
		this.setColour(330);
		this.setTooltip("Returns a clip with the frames repeated over and over again.");
		this.setHelpUrl("http://www.vapoursynth.com/doc/functions/loop.html");
	},
};

Blockly.Python['loop'] = function(block) {
	let times = block.getFieldValue('times');
	var using_operator = block.getFieldValue("using_operator") == "TRUE" ? true : false;
	var code = "";
	if (using_operator) {
		code = qvs.format("{0} = {0} * {1}\n", blocksParams.searchTargetClip(block), times);
	}
	else {
		code = qvs.format("{0} = core.std.Trim({0}, times={1})\n", blocksParams.searchTargetClip(block), times);
	}
	return code;
};

/// DeleteFrames
Blockly.Blocks['deleteframes'] = {
	init: function() {
		this.appendDummyInput()
			.appendField("DeleteFrames")
			.appendField("frame_num")
            .appendField(new Blockly.FieldNumber('0', 0, 2**52, 0, (number) => {if (number < 0) return 0}), 'frames')
		this.setInputsInline(true);
		this.setPreviousStatement(true, null);
		this.setNextStatement(true, null);
		this.setColour(330);
		this.setTooltip("Returns a clip with the frames repeated over and over again.");
		this.setHelpUrl("http://www.vapoursynth.com/doc/functions/loop.html");
	},
};

Blockly.Python['deleteframes'] = function(block) {
	let frames = block.getFieldValue('frames');
	var code = qvs.format("{0} = core.std.DeleteFrames({0}, frames=[{1}])\n", blocksParams.searchTargetClip(block), frames);
	return code;
};
