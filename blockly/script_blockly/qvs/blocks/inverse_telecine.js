'use strict';

/** Category List:
Inverse Telecine
*/

/// VIVTC
Blockly.Blocks['vivtc'] = {
    init: function() {
    this.appendDummyInput()
        .appendField("VIVTC")
        .appendField("order")
        .appendField(new Blockly.FieldDropdown([["Top Field First", "1"], ["Bottom Field First", "0"]]), 'order')
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(230);
    this.setTooltip("VIVTC is a set of filters that can be used for inverse telecine. It is a rewrite of some of tritical’s TIVTC filters.");
    this.setHelpUrl("http://www.vapoursynth.com/doc/plugins/vivtc.html");
    },
};

Blockly.Python['vivtc'] = function(block) {
    let order = block.getFieldValue('order');
    var code = qvs.format("{0} = qvs.VIVTC({0}, order='{1}')\n", blocksParams.searchTargetClip(block), order);
    return code;
};

/// DGIVTC
Blockly.Blocks['dgivtc'] = {
    init: function() {
    this.appendDummyInput()
        .appendField("DGIVTC")
        .appendField("order")
        .appendField(new Blockly.FieldDropdown([["Top Field First", "1"], ["Bottom Field First", "0"]]), 'order')
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(230);
    this.setTooltip("DGTelecideis a fast stand-alone CUDA filter that implements field matching and adaptive deinterlacing.");
    this.setHelpUrl("file:///../../DGIndexNV/DGDecodeNVManual.html");
    },
};

Blockly.Python['dgivtc'] = function(block) {
    let order = block.getFieldValue('order');
    var code = qvs.format("{0} = qvs.DGIVTC({0}, order='{1}')\n", blocksParams.searchTargetClip(block), order);
    return code;
};

/// SelectEven
Blockly.Blocks['selecteven'] = {
    init: function() {
    this.appendDummyInput()
        .appendField("SelectEven")
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(230);
    this.setTooltip("Return even numbered frames, starting with 0(clip[1::2]).");
    this.setHelpUrl("https://github.com/emako/qvs/tree/master/python/scripts");
    },
};

Blockly.Python['selecteven'] = function(block) {
    var code = qvs.format("{0} = qvs.SelectEven({0})\n", blocksParams.searchTargetClip(block));
    return code;
};

/// SelectOdd
Blockly.Blocks['selectodd'] = {
    init: function() {
    this.appendDummyInput()
        .appendField("SelectOdd")
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(230);
    this.setTooltip("Return odd numbered frames, starting with 1(clip[0::2]).");
    this.setHelpUrl("https://github.com/emako/qvs/tree/master/python/scripts");
    },
};

Blockly.Python['selectodd'] = function(block) {
    var code = qvs.format("{0} = qvs.SelectOdd({0})\n", blocksParams.searchTargetClip(block));
    return code;
};
