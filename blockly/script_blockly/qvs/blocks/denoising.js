'use strict';

/** Category List:
Denoising
*/

/// DGDenoise
Blockly.Blocks['dgdenoise'] = {
    init: function() {
        this.appendDummyInput()
            .appendField("DGDenoise")
            .appendField("strength")
            .appendField(new Blockly.FieldNumber('0.15', 0.1, 1, 0, (number) => {if (number < 0 || number > 100000000) return 0}), 'strength')
            .appendField("blend")
            .appendField(new Blockly.FieldNumber('0.1', 0, 1, 0, (number) => {if (number < 0 || number > 1) return 0}), 'blend')
            .appendField("chroma")
            .appendField(new Blockly.FieldDropdown([["True", "True"], ["False", "False"]]), 'chroma')
            .appendField("searchw")
            .appendField(new Blockly.FieldDropdown([["Quality 5", "5"], ["Quality 7", "7"], ["Quality 9", "9"]]), 'searchw');
        this.setInputsInline(true);
        this.setPreviousStatement(true, null);
        this.setNextStatement(true, null);
        this.setColour(220);
        this.setTooltip("DGDenoise is a fast stand-alone CUDA filter that implements NLM denoising. \nThe input clip must be in the YV12 format.");
        this.setHelpUrl("file:///../../DGIndexNV/DGDecodeNVManual.html");
    },
};

Blockly.Python['dgdenoise'] = function(block) {
    let strength = block.getFieldValue('strength');
    let blend = block.getFieldValue('blend');
    let chroma = block.getFieldValue('chroma');
    let searchw = block.getFieldValue('searchw');
    var code = qvs.format("{0} = qvs.DGDenoise({0}, strength={1}, blend={2}, chroma={3}, searchw={4}, device=255)\n", blocksParams.searchTargetClip(block), strength, blend, chroma, searchw);
    return code;
};

/// SMDegrain
Blockly.Blocks['smdegrain'] = {
    init: function() {
        this.appendDummyInput()
            .appendField("SMDegrain")
        this.appendDummyInput()
            .appendField("  ")
            .appendField("tr")
            .appendField(new Blockly.FieldNumber('2', 1, 128, 0, number => number), 'tr')
            .appendField("thSAD")
            .appendField(new Blockly.FieldNumber('300', -(2**52), (2**52), 0, number => number), 'thSAD')
            .appendField("RefineMotion")
            .appendField(new Blockly.FieldCheckbox("FALSE"), 'refineMotion')
            .appendField("contrasharp")
            .appendField(new Blockly.FieldDropdown([["None", "None"], ["Integer", "Integer"], ["True", "True"], ["False", "False"]]), 'contrasharp')
            .appendField(new Blockly.FieldNumber('50', 0, 100, 0, (number) => number), 'contrasharp_integer')
            .appendField("interlaced")
            .appendField(new Blockly.FieldDropdown([["False", "False"], ["TFF", "TFF"], ["BFF", "BFF"]]), 'interlaced')
            .appendField("plane")
            .appendField(new Blockly.FieldDropdown([["All", "4"], ["Luma only", "0"], ["Chroma U", "1"], ["Chroma V", "2"], ["Both chromas", "3"]]), 'plane')
        this.appendDummyInput()
            .appendField("  ")
            .appendField("Globals")
            .appendField(new Blockly.FieldDropdown([["Ignore globals", "0"], ["Read globals and Process", "1"], ["Process and output globals", "2"], ["Output globals only", "3"]]), 'globals')
            .appendField("pel")
            .appendField(new Blockly.FieldDropdown([["None", "None"], ["Full-pixel", "1"], ["Half-pixel", "2"], ["Quarter-pixel", "4"]]), 'pel')
            .appendField("subpixel")
            .appendField(new Blockly.FieldDropdown([["Sharper Wiener", "2"], ["Nnedi3", "3"], ["Bilinear ", "1"], ["Bicubic", "1"]]), 'subpixel')
        this.appendDummyInput()
            .appendField("    ")
            .appendField("prefilter")
            .appendField(new Blockly.FieldDropdown([["Off", "-1"], ["Light controlled gauss blur", "0"], ["Mild median/gauss blur ", "1"], ["Strong median/gauss blur", "2"], ["Dfttest (spatial)", "3"], ["Clip", "Clip"]]), 'prefilter')
			.appendField(new Blockly.FieldVariable('preclip'), 'preclip')
            .appendField("mfilter")
            .appendField(new Blockly.FieldDropdown([["Off", "None"], ["On", "On"]]), 'mfilter')
            .appendField(new Blockly.FieldVariable('mclip'), 'mclip')
        this.appendDummyInput()
            .appendField("  ")
            .appendField("blksize")
            .appendField(new Blockly.FieldDropdown([["None", "None"], ["4", "4"], ["8 (SD)", "8"], ["16 (HD)", "16"]]), 'blksize')
            .appendField("overlap")
            .appendField(new Blockly.FieldDropdown([["None", "None"], ["blksize / 4", "blksize / 4"], ["blksize / 2", "blksize / 2"]]), 'overlap')
            .appendField("search")
            .appendField(new Blockly.FieldNumber('4', 0, 7, 0, number => number), 'search')
            .appendField("truemotion")
            .appendField(new Blockly.FieldDropdown([["None", "None"], ["True", "True"], ["False", "False"]]), 'truemotion')
            .appendField("MVglobal")
            .appendField(new Blockly.FieldDropdown([["None", "None"], ["True", "True"], ["False", "False"]]), 'mvglobal')
        this.appendDummyInput()
            .appendField("  ")
            .appendField("dct")
            .appendField(new Blockly.FieldNumber('0', 0, 2**10, 0, number => number), 'dct')
            .appendField("limit")
            .appendField(new Blockly.FieldNumber('255', 0, 255, 0, number => number), 'limit')
            .appendField("limitc")
            .appendField(new Blockly.FieldNumber('255', 0, 255, 0, number => number), 'limitc')
            .appendField("thSCD1")
            .appendField(new Blockly.FieldNumber('400', 0, 2**52, 0, number => number), 'thSCD1')
            .appendField("thSCD2")
            .appendField(new Blockly.FieldNumber('130', 0, 2**52, 0, number => number), 'thSCD2')
            .appendField("chroma")
            .appendField(new Blockly.FieldCheckbox('TRUE'), 'chroma')
        this.appendDummyInput()
            .appendField("  ")
            .appendField("hpad")
            .appendField(new Blockly.FieldDropdown([["None", "None"], ["SD", "SD"], ["HD", "0"]]), 'hpad')
            .appendField("vpad")
            .appendField(new Blockly.FieldDropdown([["None", "None"], ["SD", "SD"], ["HD", "0"]]), 'vpad')
            .appendField("Str")
            .appendField(new Blockly.FieldNumber('1.0', 0.0, 8.0, 0, number => number), 'str')
            .appendField("Amp")
            .appendField(new Blockly.FieldNumber('0.0625', 0.0, 1.0, 0, number => number), 'amp')
        this.setInputsInline(false);
        this.setPreviousStatement(true, null);
        this.setNextStatement(true, null);
        this.setColour(220);
        this.setTooltip(`SMDegrain, the Simple MDegrain Mod, is mainly a convenience function for using MVTools. It is not a magic function (the magic comes from mvtools), it just takes the repetitive code blocks needed for mvtools+mdegrain denoising and wraps them into this function.
It has internal switches for interlaced or YUY2 content, saving you from writing long lines of code and preventing from possible mistakes. YUY2 is even automatically detected. Apart of that it adds some small and simple enhancements listed below, like easy prefilters, slightly better motion vectors (thanks to an internal TV->PC luma expansion and the possibility of dark enhancement), easy nnedi3 subpixel accuracy, globals import/export, show panel, and contra-sharpening option.`);
        this.setHelpUrl("http://avisynth.nl/index.php/SMDegrain");
    },
};

Blockly.Python['smdegrain'] = function(block) {
    let tr = block.getFieldValue('tr');
    let thSAD = block.getFieldValue('thSAD');
    let refineMotion = block.getFieldValue('refineMotion') == "TRUE" ? "True" : "False";
    let contrasharp = block.getFieldValue('contrasharp');
    let interlaced = block.getFieldValue('interlaced');
    let tff = "None";
    let plane = block.getFieldValue('plane');
    let globals = block.getFieldValue('globals');
    let pel = block.getFieldValue('pel');
    let subpixel = block.getFieldValue('subpixel');
    let prefilter = block.getFieldValue('prefilter');
    let mfilter = block.getFieldValue('mfilter');
    let blksize = block.getFieldValue('blksize');
    let overlap = block.getFieldValue('overlap');
    let search = block.getFieldValue('search');
    let truemotion = block.getFieldValue('truemotion');
    let mvglobal = block.getFieldValue('mvglobal');
    let dct = block.getFieldValue('dct');
    let limit = block.getFieldValue('limit');
    let limitc = block.getFieldValue('limitc');
    let thSCD1 = block.getFieldValue('thSCD1');
    let thSCD2 = block.getFieldValue('thSCD2');
    let chroma = block.getFieldValue('chroma') == "TRUE" ? "True" : "False";
    let hpad = block.getFieldValue('hpad');
    let vpad = block.getFieldValue('vpad');
    let str = block.getFieldValue('str');
    let amp = block.getFieldValue('amp');
    if (contrasharp == "Integer") {
        contrasharp = block.getFieldValue('contrasharp_integer');
    }
    switch (interlaced) {
        case "False":
            break;
        case "TFF":
            tff = "True";
            break;
        case "BFF":
           tff = "False";
            break;
    }
    if (prefilter == "Clip") {
        prefilter = block.getFieldVariableValue('preclip');
    }
    if (mfilter == "On") {
        mfilter = block.getFieldVariableValue('mclip');
    }
    if (overlap != "None") {
        if (blksize != "None") {
            overlap = Math.floor(eval(qvs.format("var blksize={0};{1};", blksize, overlap)));
        }
        else {
            overlap = "None";
        }
    }
    if (hpad == "SD") {
        hpad = blksize;
    }
    if (vpad == "SD") {
        vpad = blksize;
    }
    var code = qvs.format("{0} = haf.SMDegrain({0}, tr={1}, thSAD={2}, thSADC=None, RefineMotion={3}, contrasharp={4}, CClip=None, interlaced={5}, tff={6}, plane={7}, Globals={8}, pel={9}, subpixel={10}, prefilter={11}, mfilter={12}, blksize={13}, overlap={14}, search={15}, truemotion={16}, MVglobal={17}, dct={18}, limit={19}, limitc={20}, thSCD1={21}, thSCD2={22}, chroma={23}, hpad={24}, vpad={25}, Str={26}, Amp={27})\n", 
    blocksParams.searchTargetClip(block), tr, thSAD, refineMotion, contrasharp, interlaced, tff, plane, globals, pel, subpixel, prefilter, mfilter, blksize, overlap, search, truemotion, mvglobal, dct, limit, limitc, thSCD1, thSCD2, chroma, hpad, vpad, str, amp);
    return code;
};

/// KNLMeansCL
Blockly.Blocks['knlmeanscl'] = {
    init: function() {
        this.appendDummyInput()
            .appendField("KNLMeansCL")
            .appendField("d")
            .appendField(new Blockly.FieldNumber('1', -(2**52), 2**52, 0, number => Math.floor(number)), 'd')
            .appendField("a")
            .appendField(new Blockly.FieldNumber('2', -(2**52), 2**52, 0, number => Math.floor(number)), 'a')
            .appendField("s")
            .appendField(new Blockly.FieldNumber('4', -(2**52), 2**52, 0, number => Math.floor(number)), 's')
            .appendField("h")
            .appendField(new Blockly.FieldNumber('1.2', -(2**52), 2**52, 0, number => number), 'h')
            .appendField("channels")
            .appendField(new Blockly.FieldDropdown([["Auto", "auto"], ["YUV", "YUV"], ["Y", "Y"], ["UV", "UV"], ["RGB", "RGB"]]), 'channels')
            .appendField("wmode")
            .appendField(new Blockly.FieldDropdown([["0", "0"], ["1", "1"], ["2", "2"], ["3", "3"]]), 'wmode')
            .appendField("wref")
            .appendField(new Blockly.FieldNumber('1.0', -(2**52), 2**52, 0, number => number), 'wref')
            .appendField("rclip")
            .appendField(new Blockly.FieldDropdown([["Disable", "None"], ["Enable", "Enable"]]), 'rclip')
            .appendField(new Blockly.FieldVariable('rclip'), 'rclip_var')
        this.appendDummyInput()
            .appendField("  ")
            .appendField("device_type")
            .appendField(new Blockly.FieldDropdown([["Accelerator", "accelerator"], ["CPU", "cpu"], ["GPU", "gpu"], ["Auto", "auto"]]), 'device_type')
            .appendField("device_id")
            .appendField(new Blockly.FieldNumber('0', 0, 255, 0, number => Math.floor(number)), 'device_id')
            .appendField("info")
            .appendField(new Blockly.FieldCheckbox('FALSE'), 'info')
        this.setInputsInline(false);
        this.setPreviousStatement(true, null);
        this.setNextStatement(true, null);
        this.setColour(220);
        this.setTooltip("KNLMeansCL is an optimized OpenCL implementation of the Non-local means de-noising algorithm.");
        this.setHelpUrl("https://github.com/Khanattila/KNLMeansCL/wiki/Filter-description");
    },
};
  
Blockly.Python['knlmeanscl'] = function(block) {
    let d = block.getFieldValue('d');
    let a = block.getFieldValue('a');
    let s = block.getFieldValue('s');
    let h = block.getFieldValue('h');
    let channels = block.getFieldValue('channels');
    let wmode = block.getFieldValue('wmode');
    let wref = block.getFieldValue('wref');
    let rclip = block.getFieldValue('rclip');
    let device_type = block.getFieldValue('device_type');
    let device_id = block.getFieldValue('device_id');
    let info = block.getFieldValue('info') == "TRUE" ? "True" : "False";
    if (rclip == "Enable") {
        rclip = block.getFieldVariableValue('rclip_var');
    }
    var code = qvs.format("{0} = core.knlm.KNLMeansCL({0}, d={1}, a={2}, s={3}, h={4}, channels='{5}', wmode={6}, wref={7}, rclip={8}, device_type='{9}', device_id={10}, info={11})\n", 
    blocksParams.searchTargetClip(block), d, a, s, h, channels, wmode, wref, rclip, device_type, device_id, info);
    return code;
};

/// VagueDenoiser
Blockly.Blocks['vaguedenoiser'] = {
    init: function() {
        this.appendDummyInput()
            .appendField("VagueDenoiser")
            .appendField("threshold")
            .appendField(new Blockly.FieldNumber('0', 0, 2**52, 0, (number) => number), 'threshold')
            .appendField("method")
            .appendField(new Blockly.FieldDropdown([["Hard thresholding", "0"], ["Soft thresholding", "1"], ["Qian's (garrote) thresholding", "2"]]), 'method')
            .appendField("nsteps")
            .appendField(new Blockly.FieldNumber('4', -(2**52), 2**52, 0, (number) => Math.floor(number)), 'nsteps')
            .appendField("percent")
            .appendField(new Blockly.FieldNumber('85', 0, 100, 0, (number) => Math.floor(number)), 'nsteps')
            .appendField("planes")
            .appendField(new Blockly.FieldTextInput('0, 1, 2'), 'planes')
        this.setInputsInline(true);
        this.setPreviousStatement(true, null);
        this.setNextStatement(true, null);
        this.setColour(220);
        this.setTooltip("This is a wavelet based denoiser.");
        this.setHelpUrl("http://avisynth.org.ru/vague/vaguedenoiser.html");
        this.setHelpUrl("https://github.com/HomeOfVapourSynthEvolution/VapourSynth-VagueDenoiser");
    },
};

Blockly.Python['vaguedenoiser'] = function(block) {
	let threshold = block.getFieldValue('threshold');
	let method = block.getFieldValue('method');
	let nsteps = block.getFieldValue('nsteps');
	let percent = block.getFieldValue('percent');
	let planes = block.getFieldValue('planes');
	planes = Blockly.Python.arrayToCode(Blockly.Python.stringToArray(planes));
    var code = qvs.format("{0} = core.vd.VagueDenoiser({0}, threshold={1}, method={2}, nsteps={3}, percent={4}, planes={5})\n", 
    blocksParams.searchTargetClip(block), threshold, method, nsteps, percent, planes);
    return code;
};
