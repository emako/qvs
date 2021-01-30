'use strict';

/** Category List:
Frame Rate Conversion
*/

/// ChangeFPS
Blockly.Blocks['changefps'] = {
    init: function() {
    this.appendDummyInput()
        .appendField("ChangeFPS")
        .appendField("fpsnum")
        .appendField(new Blockly.FieldNumber('0', 0, 10000000, 0, (number) => {if (number < 0 || number > 10000000) return 0}), 'fpsnum')
        .appendField("fpsden")
        .appendField(new Blockly.FieldNumber('0', 0, 10000000, 0, (number) => {if (number < 0 || number > 10000000) return 0}), 'fpsden')
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(270);
    this.setTooltip("Changes the frame rate by deleting or duplicating frames.");
    this.setHelpUrl("https://github.com/HomeOfVapourSynthEvolution/havsfunc");
    },
};

Blockly.Python['changefps'] = function(block) {
    let fpsnum = block.getFieldValue('fpsnum');
    let fpsden = block.getFieldValue('fpsden');
    var code = qvs.format("{0} = haf.ChangeFPS({0}, fpsnum={1}, fpsden={2})\n", blocksParams.searchTargetClip(block), fpsnum, fpsden);
    return code;
};

/// AssumeFPS
Blockly.Blocks['assumefps'] = {
    init: function() {
    this.appendDummyInput()
        .appendField("AssumeFPS")
        .appendField("fpsnum")
        .appendField(new Blockly.FieldNumber('0', 0, 10000000, 0, (number) => {if (number < 0 || number > 10000000) return 0}), 'fpsnum')
        .appendField("fpsden")
        .appendField(new Blockly.FieldNumber('0', 0, 10000000, 0, (number) => {if (number < 0 || number > 10000000) return 0}), 'fpsden')
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(270);
    this.setTooltip("Changes the frame rate without changing the frame count, causing the video to play faster or slower.");
    this.setHelpUrl("http://www.vapoursynth.com/doc/functions/assumefps.html");
    },
};

Blockly.Python['assumefps'] = function(block) {
    let fpsnum = block.getFieldValue('fpsnum');
    let fpsden = block.getFieldValue('fpsden');
    var code = qvs.format("{0} = core.std.AssumeFPS({0}, fpsnum={1}, fpsden={2})\n", blocksParams.searchTargetClip(block), fpsnum, fpsden);
    return code;
};

/// VFRToCFR
Blockly.Blocks['vfrtocfr'] = {
    init: function() {
    this.appendDummyInput()
        .appendField("VFRToCFR")
        .appendField(new Blockly.FieldTextInput(""), "path")
        .appendField("fpsnum")
        .appendField(new Blockly.FieldNumber('0', 0, 10000000, 0, (number) => {if (number < 0 || number > 10000000) return 0}), 'fpsnum')
        .appendField("fpsden")
        .appendField(new Blockly.FieldNumber('0', 0, 10000000, 0, (number) => {if (number < 0 || number > 10000000) return 0}), 'fpsden')
    this.appendValueInput("load");
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(270);
    this.setTooltip("Converts Variable Frame Rate (VFR) video to a Constant Frame Rate (CFR) video through the use of Matroska Version 2 Timecodes.");
    this.setHelpUrl("https://github.com/Irrational-Encoding-Wizardry/Vapoursynth-VFRToCFR");
    },
	contextMenu: new BlockContextMenu("Open Timecode file", "Timecode (*.txt *.tc)", null),
};

Blockly.Python['vfrtocfr'] = function(block) {
    let path = block.getFieldValue('path');
    let fpsnum = block.getFieldValue('fpsnum');
    let fpsden = block.getFieldValue('fpsden');
    var code = qvs.format("{0} = core.vfrtocfr.VFRToCFR({0}, timecodes=u'{1}', fpsnum={2}, fpsden={3})\n", blocksParams.searchTargetClip(block), qvs.unifySeparator(path), fpsnum, fpsden);
    return code;
};
