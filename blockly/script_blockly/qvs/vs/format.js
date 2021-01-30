/**
 * Get the list of format constants in vapoursynth.
 * See more: http://www.vapoursynth.com/doc/pythonreference.html
 * @return {string} List of format constants.
 */
var getFormatConstants = function(noneable=false) {
    // Format constants exactly describe a format. 
    // All common and even more uncommon formats have handy constants predefined 
    // so in practice no one should really need to register one of their own. 
    // These values are mostly used by the resizers to specify which format to convert to. 
    // The naming system is quite simple. First the color family, then the subsampling (only YUV has it) 
    // and after that how many bits per sample in one plane. 
    // The exception to this rule is RGB, which has the bits for all 3 planes added together. 
    // The long list of values:
    var formatConstants = [];
    if (noneable) {
        formatConstants.push("None");
    }
    formatConstants.push(
        "RGB24",
        "RGB27",
        "RGB30",
        "RGB48",
        
        "RGBH",
        "RGBS",
        
        "COMPATBGR32",
        "COMPATYUY2",

        "YUV420P8",
        "YUV422P8",
        "YUV444P8",
        "YUV410P8",
        "YUV411P8",
        "YUV440P8",
        
        "YUV420P9",
        "YUV422P9",
        "YUV444P9",
        
        "YUV420P10",
        "YUV422P10",
        "YUV444P10",
        
        "YUV420P12",
        "YUV422P12",
        "YUV444P12",
        
        "YUV420P14",
        "YUV422P14",
        "YUV444P14",
        
        "YUV420P16",
        "YUV422P16",
        "YUV444P16",
        
        "YUV444PH",
        "YUV444PS",
        
        "GRAY8",
        "GRAY16",
        "GRAYH",
        "GRAYS",
    );

    return formatConstants;
};

/**
 * Get the list of css(chroma sub-sampling) in vapoursynth.
 * See more: https://github.com/HomeOfVapourSynthEvolution/mvsfunc
 * @return {string} List of css.
 */
var getChromaSubSamplings = function(noneable=false, nametype=null) {
    var formatConstants = [];
    if (noneable) {
        formatConstants.push("None");
    }
    nametype = nametype | 0;
    switch (nametype) {
        case 0:
        default:
            formatConstants.push(
                "444",
                "440",
                "422",
                "420",
                "411",
                "410",
            );
            break;
        case 1:
            formatConstants.push(
                "4:4:4",
                "4:4:0",
                "4:2:2",
                "4:2:0",
                "4:1:1",
                "4:1:0",
            );
            break;
        case 2:
            formatConstants.push(
                "11",
                "12",
                "21",
                "22",
                "41",
                "42",
            );
            break;
    }
    return formatConstants;
};

/**
 * Get the list of matrix in vapoursynth.
 * See more: https://github.com/HomeOfVapourSynthEvolution/mvsfunc
 * @return {string} List of matrix.
 */
var getMatrixs = function(noneable=false, nametype=null) {
    var formatConstants = [];
    if (noneable) {
        formatConstants.push("None");
    }
    `
    ##     matrix {int|str}: explicitly specify matrix in int or str format, not case-sensitive
    ##         - 0 | "RGB"
    ##         - 1 | "709" | "bt709"
    ##         - 2 | "Unspecified": same as not specified (None)
    ##         - 4 | "FCC"
    ##         - 5 | "bt470bg": same as "601"
    ##         - 6 | "601" | "smpte170m"
    ##         - 7 | "240" | "smpte240m"
    ##         - 8 | "YCgCo" | "YCoCg"
    ##         - 9 | "2020" | "bt2020nc"
    ##         - 10 | "2020cl" | "bt2020c"
    ##         - 100 | "OPP" | "opponent": same as the opponent color space used in BM3D denoising filter
    `
    nametype = nametype | 0;
    switch (nametype) {
        case 0:
            formatConstants.push(
                "RGB",
                "709",
                "FCC",
                "bt470bg",
                "601",
                "240",
                "YCgCo",
                "2020",
                "2020cl",
                "OPP",
            );
            break;
        case 1:
            formatConstants.push(
                "RGB",
                "bt709",
                "FCC",
                "bt470bg",
                "smpte170m",
                "smpte240m",
                "YCoCg",
                "bt2020nc",
                "bt2020c",
                "opponent",
            );
            break;
    }
    return formatConstants;
};
