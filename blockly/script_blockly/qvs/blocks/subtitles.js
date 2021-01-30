'use strict';

/** Category List:
Subtitles
*/

/// TextSub from VSFilter
Blockly.Blocks['textsub'] = {
    init: function() {
    this.appendDummyInput()
        .appendField("VSFilter")
        .appendField(new Blockly.FieldTextInput(""), "file")
        .appendField("charset")
        .appendField(new Blockly.FieldNumber('1', 1, 10000000, 0, (number) => {if (number < 1 || number > 10000000) return 1}), 'charset')
        .appendField("fps")
        .appendField(new Blockly.FieldNumber('-1', -1, 10000000, 0, (number) => {if (number < -1 || number > 10000000) return -1}), 'fps')
        .appendField("vfr")
        .appendField(new Blockly.FieldTextInput(""), 'vfr')
    this.appendValueInput("load");
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(40);
    this.setTooltip("Only YUV420P8, YUV420P16, and RGB24 are supported. \nSupported Subtitle Formats: VOBsub (.sub/.idx), SubStation Alpha/Advanced SubStation Alpha (.ssa/.ass), SubRip (.srt), MicroDVD (.sub), SAMI (.smi), PowerDivX (.psb), Universal Subtitle Format (.usf), Structured Subtitle Format (.ssf).");
    this.setHelpUrl("https://github.com/HomeOfVapourSynthEvolution/VSFilter");
    this.setHelpUrl("http://avisynth.nl/index.php/VSFilterMod");
    },
	contextMenu: new BlockContextMenu("Open Suttitle file", "Suttitle (*.ass *.ssa *.sub *.idx *.sup *.tcas)", null),
};

Blockly.Python['textsub'] = function(block) {
    let file = block.getFieldValue('file');
    let charset = block.getFieldValue('charset');
    let fps = block.getFieldValue('fps');
    let vfr = block.getFieldValue('vfr');

    let fileExt = qvs.getFileExtension(file);
    var code = null;

    if (fileExt == 'sub' || fileExt == 'idx') {
        code = qvs.format("{0} = core.vsf.VobSub({0}, file=u'{1}')\n", qvs.unifySeparator(file));
    }
    else {
        code = qvs.format("{0} = core.vsf.TextSub({0}, file=u'{1}', charset={2}, fps={3}, vfr=u'{4}')\n", blocksParams.searchTargetClip(block), qvs.unifySeparator(file), charset, fps, qvs.unifySeparator(vfr));
    }

    return code;
};

/// TextSubMod from VSFilterMod
Blockly.Blocks['textsubmod'] = {
    init: function() {
    this.appendDummyInput()
        .appendField("VSFilterMod")
        .appendField(new Blockly.FieldTextInput(""), "file")
        .appendField("charset")
        .appendField(new Blockly.FieldNumber('1', 1, 10000000, 0, (number) => {if (number < 1 || number > 10000000) return 1}), 'charset')
        .appendField("fps")
        .appendField(new Blockly.FieldNumber('-1', -1, 10000000, 0, (number) => {if (number < -1 || number > 10000000) return -1}), 'fps')
        .appendField("vfr")
        .appendField(new Blockly.FieldTextInput(""), 'vfr')
        .appendField("accurate")
        .appendField(new Blockly.FieldDropdown([["Off", "0"], ["On", "1"]]), 'accurate')
    this.appendValueInput("load");
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(40);
    this.setTooltip("VSFilterMod is modification of original VSFilter subtitle renderer by Gabest. \nOnly YUV420P8, YUV420P10, YUV420P16 and RGB24 are supported.");
    this.setHelpUrl("https://github.com/HomeOfVapourSynthEvolution/VSFilterMod");
    this.setHelpUrl("http://avisynth.nl/index.php/VSFilterMod");
    },
	contextMenu: new BlockContextMenu("Open Suttitle file", "Suttitle (*.ass *.ssa *.sub *.idx *.sup *.tcas)", null),
};

Blockly.Python['textsubmod'] = function(block) {
    let file = block.getFieldValue('file');
    let charset = block.getFieldValue('charset');
    let fps = block.getFieldValue('fps');
    let vfr = block.getFieldValue('vfr');
    let accurate = block.getFieldValue('accurate');

    let fileExt = qvs.getFileExtension(file);
    var code = null;

    if (fileExt == 'sub' || fileExt == 'idx') {
        code = qvs.format("{0} = core.vsfm.VobSub({0}, file=u'{1}')\n", blocksParams.searchTargetClip(block), qvs.unifySeparator(file));
    }
    else {
        code = qvs.format("{0} = core.vsfm.TextSubMod({0}, file=u'{1}', charset={2}, fps={3}, vfr=u'{4}', accurate={5})\n", blocksParams.searchTargetClip(block), qvs.unifySeparator(file), charset, fps, qvs.unifySeparator(vfr), accurate);
    }
    return code;
};

/// Subtext from core
Blockly.Blocks['subtext'] = {
    init: function() {
    this.appendDummyInput()
        .appendField("Subtext")
        .appendField(new Blockly.FieldTextInput(""), "file")
        .appendField("charset")
        .appendField(new Blockly.FieldTextInput('UTF-8'), 'charset')
        .appendField("sar")
        .appendField(new Blockly.FieldNumber('0', 0, 255, 0, (number) => {if (number < 0 || number > 255) return 0}), 'sar')
    this.appendValueInput("load");
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(40);
    this.setTooltip("Subtext is a subtitle renderer that uses libass and ffmpeg. \nTextFile renders text subtitles. Supported formats include ASS, JACOsub, MicroDVD, SAMI, SRT, WebVTT, and some other obscure ones. \nImageFile renders image-based subtitles such as VOBSUB and PGS.");
    this.setHelpUrl("http://www.vapoursynth.com/doc/plugins/subtext.html");
    },
	contextMenu: new BlockContextMenu("Open Suttitle file", "Suttitle (*.ass *.ssa *.sub *.idx *.sup *.tcas)", null),
};

Blockly.Python['subtext'] = function(block) {
    let file = block.getFieldValue('file');
    let charset = block.getFieldValue('charset');
    let sar = block.getFieldValue('sar');

    let fileExt = qvs.getFileExtension(file);
    var code = null;

    if (fileExt == 'sub' || fileExt == 'idx' || fileExt == 'pgs') {
        code = qvs.format("{0} = core.sub.ImageFile({0}, file=u'{1}')\n", blocksParams.searchTargetClip(block), qvs.unifySeparator(file));
    }
    else {
        code = qvs.format("{0} = core.sub.TextFile({0}, file=u'{1}', charset='{2}', sar={3})\n", blocksParams.searchTargetClip(block), qvs.unifySeparator(file), charset, sar);
    }
    return code;
};

/// TcasSub from tcasFilter
Blockly.Blocks['tcassub'] = {
    init: function() {
    this.appendDummyInput()
        .appendField("TcasFilter")
        .appendField(new Blockly.FieldTextInput(""), "file")
        .appendField("fps")
        .appendField(new Blockly.FieldNumber('0', 0, 255, 0, (number) => {if (number < 0 || number > 255) return 0}), 'fps')
        .appendField("max_frame")
        .appendField(new Blockly.FieldNumber('0', 0, 2**52, 0, (number) => {if (number < 0 || number > 2**52) return 0}), 'max_frame')
        .appendField("memory_max")
        .appendField(new Blockly.FieldNumber('0', 0, 1024, 0, (number) => {if (number < 0 || number > 1024) return 0; else if (number > 0 && number < 32) {return 32}}), 'memory_max')
    this.appendValueInput("load");
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(40);
    this.setTooltip("Parse Tcas subtilte for tcax project.");
    this.setHelpUrl("http://www.tcax.org");
    this.setHelpUrl("http://www.tcax.org/docs/tcas-spec.htm");
    this.setHelpUrl("https://github.com/emako/qvs/blob/master/python/scripts/qvs.py");
    },
	contextMenu: new BlockContextMenu("Open Suttitle file", "Suttitle (*.tcas)", null),
};

Blockly.Python['tcassub'] = function(block) {
    let file = block.getFieldValue('file');
    let fps = block.getFieldValue('fps');
    let max_frame = block.getFieldValue('max_frame');
    let memory_max = block.getFieldValue('memory_max');

    var code = qvs.format("{0} = core.tcax.TcasSub({0}, file=u'{1}', fps={2}, max_frame={3}, memory_max={4})\n", blocksParams.searchTargetClip(block), qvs.unifySeparator(file), fps, max_frame, memory_max);
    return code;
};
/// Subtitle from core @Deprecated
Blockly.Blocks['subtitle_stext'] = {
    init: function() {
    this.appendDummyInput()
        .appendField("Subtitle")
        .appendField(new Blockly.FieldTextInput(""), "text")
        .appendField("start")
        .appendField(new Blockly.FieldNumber('0', 0, 2**52, 0, (number) => {if (number < 0 || number > 2**52) return 0}), 'start')
        .appendField("end")
        .appendField(new Blockly.FieldNumber('0', 0, 2**52, 0, (number) => {if (number < 0 || number > 2**52) return 0}), 'end')
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(40);
    this.setTooltip("Instead of rendering a subtitle file, Subtitle renders the string text. \nOtherwise it works the same as TextFile.");
    this.setHelpUrl("http://www.vapoursynth.com/doc/plugins/subtext.html");
    },
};

Blockly.Python['subtitle_stext'] = function(block) {
    let text = block.getFieldValue('text');
    let start = block.getFieldValue('start');
    let end = block.getFieldValue('end');

    if (end <= 0) {
        end = 'src.numFrames';
    }
    var code = qvs.format("{0} = core.sub.Subtitle({0}, text=u'{1}', start={2}, end={3})\n", blocksParams.searchTargetClip(block), text, start, end);
    return code;
};

/// Subtitle from core
Blockly.Blocks['subtitle'] = {
    init: function() {
    this.appendDummyInput()
        .appendField("Subtitle")
        .appendField(new Blockly.FieldTextInput(""), "text")
        .appendField("alignment")
        .appendField(new Blockly.FieldNumber('7', 1, 9, 0, (number) => {if (number < 1 || number > 9) return 7}), 'alignment')
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(40);
    this.setTooltip("Text is a simple text printing filter. \nIt doesn’t use any external libraries for drawing the text.");
    this.setHelpUrl("http://www.vapoursynth.com/doc/functions/text.html");
    },
};

Blockly.Python['subtitle'] = function(block) {
    let text = block.getFieldValue('text');
    let alignment = block.getFieldValue('alignment');

    var code = null;
    if (blocksParams.preferQvs) {
        code = qvs.format("{0} = qvs.Subtitle({0}, text=u'{1}', an={2})\n", blocksParams.searchTargetClip(block), text, alignment);
    }
    else {
        code = qvs.format("{0} = core.text.Text({0}, text=u'{1}', alignment={2})\n", blocksParams.searchTargetClip(block), text, alignment);
    }
    return code;
};

/// Subtitle from core
Blockly.Blocks['subtitle_auto'] = {
    init: function() {
    this.appendDummyInput()
        .appendField("Subtitle")
        .appendField(new Blockly.FieldTextInput(""), "file")
        .appendField("prefer")
        .appendField(new Blockly.FieldDropdown([["VSFilter", "vsf"], ["VSFilterMod", "vsfm"], ["VSCore", "sub"]]), 'prefer');
    this.appendValueInput("load");
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(40);
    this.setTooltip("");
    this.setHelpUrl("");
    },
	contextMenu: new BlockContextMenu("Open Suttitle file", "Suttitle (*.*)", null),
};

Blockly.Python['subtitle_auto'] = function(block) {
    let file = block.getFieldValue('file');
    let prefer = block.getFieldValue('prefer');

    let fileExt = qvs.getFileExtension(file);
    if (file == '') {
        fileExt = 'ass';
    }

    var code = null;
    switch (fileExt) {
        case 'ass':
        case 'ssa':
        case 'srt':
        case 'smi':
        case 'psb':
        case 'usf':
        case 'ssf':
        default:
            if (prefer == 'vsf') {
                code = qvs.format("{0} = core.vsf.TextSub({0}, file=u'{1}', charset=1, fps=0, vfr=u'')\n", blocksParams.searchTargetClip(block), qvs.unifySeparator(file));
            }
            else if (prefer == 'vsfm') {
                code = qvs.format("{0} = core.vsfm.TextSubMod({0}, file=u'{1}', charset=1, fps=0, vfr=u'', accurate=0)\n", blocksParams.searchTargetClip(block), qvs.unifySeparator(file));
            }
            else if (prefer == 'sub') {
                code = qvs.format("{0} = core.sub.TextFile({0}, file=u'{0}', charset='UTF-8', sar=0)\n", blocksParams.searchTargetClip(block), qvs.unifySeparator(file));
            }
            break;
        case 'sub':
        case 'idx':
            if (prefer == 'vsf') {
                code = qvs.format("{0} = core.vsf.VobSub({0}, file=u'{1}')\n", blocksParams.searchTargetClip(block), qvs.unifySeparator(file));
            }
            else if (prefer == 'vsfm') {
                code = qvs.format("{0} = core.vsfm.VobSub({0}, file=u'{1}')\n", blocksParams.searchTargetClip(block), qvs.unifySeparator(file));
            }
            else if (prefer == 'sub') {
                code = qvs.format("{0} = core.sub.ImageFile({0}, file=u'{1}')\n", blocksParams.searchTargetClip(block), qvs.unifySeparator(file));
            }
            break;
        case 'pgs':
        case 'sup':
            code = qvs.format("{0} = core.sub.ImageFile({0}, file=u'{1}')\n", blocksParams.searchTargetClip(block), qvs.unifySeparator(file));
            break;
        case 'tcas':
            code = qvs.format("{0} = core.tcax.TcasSub({0}, file=u'{1}', fps=0, max_frame=0, memory_max=0)\n", blocksParams.searchTargetClip(block), qvs.unifySeparator(file));
            break;
        case '':
            let text = file;
            if (blocksParams.preferQvs) {
                code = qvs.format("{0} = qvs.Subtitle({0}, text=u'{1}', an=7)\n", blocksParams.searchTargetClip(block), text);
            }
            else {
                code = qvs.format("{0} = core.text.Text({0}, text=u'{1}', alignment=7)\n", blocksParams.searchTargetClip(block), text);
            }
            break;
    }
    return code;
};
