'use strict';

/** Category List:
Deinterlacing
*/

/// Yadifmod
Blockly.Blocks['yadifmod'] = {
    init: function() {
    this.appendDummyInput()
        .appendField("Yadifmod")
        .appendField("order")
        .appendField(new Blockly.FieldDropdown([["Top Field First", "tff"], ["Bottom Field First", "bff"]]), 'order')
        .appendField("mode")
        .appendField(new Blockly.FieldDropdown([["Single Rate", "0"], ["Double Rate", "1"]]), 'mode')
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(240);
    this.setTooltip("Port of YADIF (Yet Another DeInterlacing Filter) from MPlayer. \nIt check pixels of previous, current and next frames to re-create the missed field by some local adaptive method (edge-directed interpolation) \nand uses spatial check to prevent most artifacts.");
    this.setHelpUrl("https://github.com/HomeOfVapourSynthEvolution/VapourSynth-Yadifmod");
    },
};

Blockly.Python['yadifmod'] = function(block) {
    let order = block.getFieldValue('order');
    let mode = block.getFieldValue('mode');
    var code = qvs.format("{0} = qvs.Yadifmod({0}, order='{1}', mode={2})\n", blocksParams.searchTargetClip(block), order, mode);
    return code;
};

/// QTGMC
Blockly.Blocks['qtgmc'] = {
    init: function() {
    this.appendDummyInput()
        .appendField("QTGMC")
        .appendField("preset")
        .appendField(new Blockly.FieldDropdown([["Placebo", "Placebo"], ["Very Slow", "Very Slow"], ["Slower", "Slower"], ["Slow", "Slow"], ["Medium", "Medium"], ["Fast", "Fast"], ["Faster", "Faster"], ["Very Fast", "Very Fast"], ["Super Fast", "Super Fast"], ["Ultra Fast", "Ultra Fast"]]), 'preset')
        .appendField("order")
        .appendField(new Blockly.FieldDropdown([["Top Field First", "True"], ["Other Field First", "False"]]), 'order')
        .appendField("mode")
        .appendField(new Blockly.FieldDropdown([["Single Rate", "2"], ["Double Rate", "1"]]), 'mode')
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(240);
    this.setTooltip("Port of YADIF (Yet Another DeInterlacing Filter) from MPlayer. \nIt check pixels of previous, current and next frames to re-create the missed field by some local adaptive method (edge-directed interpolation) \nand uses spatial check to prevent most artifacts.");
    this.setHelpUrl("https://github.com/HomeOfVapourSynthEvolution/havsfunc");
    },
};

Blockly.Python['qtgmc'] = function(block) {
    let preset = block.getFieldValue('preset');
    let order = block.getFieldValue('order');
    let mode = block.getFieldValue('mode');
    var code = qvs.format("{0} = qvs.QTGMC({0}, Preset='{1}', TFF={2}, FPSDivisor={3}, opencl=True)\n", blocksParams.searchTargetClip(block), preset, order, mode);
    return code;
};

/// DGBob
Blockly.Blocks['dgbob'] = {
    init: function() {
    this.appendDummyInput()
        .appendField("DGBob")
        .appendField("order")
        .appendField(new Blockly.FieldDropdown([["Top Field First", "1"], ["Bottom Field First", "0"]]), 'order')
        .appendField("mode")
        .appendField(new Blockly.FieldDropdown([["Single Rate", "0"], ["Double Rate", "1"]]), 'mode')
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(240);
    this.setTooltip(`This filter splits each field of the source into its own frame and then adaptively creates the missing lines either by interpolating the current field or by using the previous field's data. The filter attempts with some success to mitigate the flutter that bobbing produces. Note that this process of converting fields to frames will double the frame rate of the input clip.
    The filter can also be used as a simple deinterlacer that retains the input frame rate by setting the 'single' parameter to true.
    This filter supports RGB, YV12, and YUY2 input color spaces.`);
    this.setHelpUrl("http://rationalqm.us/dgbob/dgbob.html");
    },
};

Blockly.Python['dgbob'] = function(block) {
    let order = block.getFieldValue('order');
    let mode = block.getFieldValue('mode');
    var code = qvs.format("{0} = qvs.DGBob({0}, order='{1}', mode={2}, device=255, pv=False)\n", blocksParams.searchTargetClip(block), order, mode);
    return code;
};

/// Interlacing
Blockly.Blocks['interlacing'] = {
    init: function() {
    this.appendDummyInput()
        .appendField("Interlacing")
        .appendField("order")
        .appendField(new Blockly.FieldDropdown([["Top Field First", "True"], ["Bottom Field First", "False"]]), 'order')
        .appendField("mode")
        .appendField(new Blockly.FieldDropdown([["Single Rate", "0"], ["Double Rate", "1"]]), 'mode')
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(240);
    this.setTooltip("Convert clip to interlaced clip.");
    this.setHelpUrl("http://www.vapoursynth.com/doc/functions/doubleweave.html");
    },
};

Blockly.Python['interlacing'] = function(block) {
    let order = block.getFieldValue('order');
    let mode = block.getFieldValue('mode');
    var code = qvs.format("{0} = qvs.Interlacing({0}, tff={1}, mode={2})\n", blocksParams.searchTargetClip(block), order, mode);
    return code;
};
