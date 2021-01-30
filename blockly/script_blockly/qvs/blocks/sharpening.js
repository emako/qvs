'use strict';

/** Category List:
Sharpening
*/

/// DGSharpen
Blockly.Blocks['dgsharpen'] = {
    init: function() {
        this.appendDummyInput()
            .appendField("DGSharpen")
            .appendField("strength")
            .appendField(new Blockly.FieldNumber('1.0', 0.1, 1, 0, (number) => {if (number < 0 || number > 100000000) return 0}), 'strength')
        this.setInputsInline(true);
        this.setPreviousStatement(true, null);
        this.setNextStatement(true, null);
        this.setColour(210);
        this.setTooltip("DGSharpen is a fast stand-alone CUDA filter that implements limited sharpening like the well-known filter LimitedSharpenFaster(). The input clip must be in the YV12 format.");
        this.setHelpUrl("file:///../../DGIndexNV/DGDecodeNVManual.html");
    },
};

Blockly.Python['dgsharpen'] = function(block) {
    let strength = block.getFieldValue('strength');
    var code = qvs.format("{0} = qvs.DGSharpen({0}, strength={1}, device=255)\n", blocksParams.searchTargetClip(block), strength);
    return code;
};
