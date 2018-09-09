#include "mediainfo_dialog.h"
#include "mediainfo_loader.h"
#include "mainwindow.h"
#include "com/common.h"
#include "../script/script_player.h"
#include "ui_mediainfo_dialog.h"

static const wchar_t *c_mediainfo_lang_list_en = __T(
"  Language_ISO639;en\n"
"  Author_Email;Info@MediaArea.net\n"
"  Author_Name;Zen\n"
"  Author_OldNames;Initial translator\n"
"  Language_Name;English\n"
"  Config_Text_ColumnSize;40\n"
"  Config_Text_Separator; : \n"
"  Config_Text_NumberTag; @\n"
"  Config_Text_FloatSeparator;.\n"
"  Config_Text_ThousandsSeparator; \n"
" audio stream1; audio stream\n"
" audio stream2; audio streams\n"
" audio stream3; audio streams\n"
" bit1; bit\n"
" bit2; bits\n"
" bit3; bits\n"
" bps; b/s\n"
" Bps; B/s\n"
" Byte1; Byte\n"
" Byte2; Bytes\n"
" Byte3; Bytes\n"
" channel1; channel\n"
" channel2; channels\n"
" channel3; channels\n"
" chapter1; chapter\n"
" chapter2; chapters\n"
" chapter3; chapters\n"
" chapters stream1; chapters stream\n"
" chapters stream2; chapters streams\n"
" chapters stream3; chapters streams\n"
" character1; character\n"
" character2; characters\n"
" character3; characters\n"
" day1; day\n"
" day2; days\n"
" day3; days\n"
" dB1; dB\n"
" dB2; dB\n"
" dB3; dB\n"
" file1; file\n"
" file2; files\n"
" file3; files\n"
" fps1; FPS\n"
" fps2; FPS\n"
" fps3; FPS\n"
" frame1; framesssssssssssssv\n"
" frame2; framesssssssssssssv\n"
" frame3; framesssssssssssssv\n"
" GB; GB\n"
" Gb; Gb\n"
" Gbps; Gb/s\n"
" GBps; GB/s\n"
" GHz; GHz\n"
" GiB; GiB\n"
" GibiByte1; GibiBytes\n"
" GibiByte2; GibiBytes\n"
" GibiByte3; GibiBytes\n"
" GiBps; GiB/s\n"
" GigaBit1; GigaBit\n"
" GigaBit2; GigaBits\n"
" GigaBit3; GigaBits\n"
" GigaByte1; GigaByte\n"
" GigaByte2; GigaBytes\n"
" GigaByte3; GigaBytes\n"
" hour1; hour\n"
" hour2; hours\n"
" hour3; hours\n"
" Hz; Hz\n"
" image stream1; image stream\n"
" image stream2; image streams\n"
" image stream3; image streams\n"
" KB; kB\n"
" Kb; kb\n"
" KBps; kB/s\n"
" Kbps; kb/s\n"
" KHz; kHz\n"
" KiB; KiB\n"
" KibiBit1; KibiBit\n"
" KibiBit2; KibiBits\n"
" KibiBit3; KibiBits\n"
" KibiByte1; KibiByte\n"
" KibiByte2; KibiBytes\n"
" KibiByte3; KibiBytes\n"
" KiBps; KiB/s\n"
" KiloBit1; KiloBit\n"
" KiloBit2; KiloBits\n"
" KiloBit3; KiloBits\n"
" KiloByte1; KiloByte\n"
" KiloByte2; KiloBytes\n"
" KiloByte3; KiloBytes\n"
" MB; MB\n"
" Mb; Mb\n"
" Mbps; Mb/s\n"
" MBps; MebiBytes\n"
" MebiBit1; MebiBit\n"
" MebiBit2; MebiBits\n"
" MebiBit3; MebiBits\n"
" MebiByte1; MebiByte\n"
" MebiByte2; MebiBytes\n"
" MebiByte3; MebiBytes\n"
" MegaBit1; MegaBit\n"
" MegaBit2; MegaBits\n"
" MegaBit3; MegaBits\n"
" MegaByte1; MegaByte\n"
" MegaByte2; MegaBytes\n"
" MegaByte3; MegaBytes\n"
" MHz; MHz\n"
" MiB; MiB\n"
" Mib; Mib\n"
" MiBps; MiB/s\n"
" millisecond1; millisecond\n"
" millisecond2; milliseconds\n"
" millisecond3; milliseconds\n"
" minute1; minute\n"
" minute2; minutes\n"
" minute3; minutes\n"
" month1; month\n"
" month2; months\n"
" month3; months\n"
" pixel1; pixel\n"
" pixel2; pixels\n"
" pixel3; pixels\n"
" second1; second\n"
" second2; seconds\n"
" second3; seconds\n"
" text stream1; text stream\n"
" text stream2; text streams\n"
" text stream3; text streams\n"
" video frames1; video frame\n"
" video frames2; video frames\n"
" video frames3; video frames\n"
" video stream1; video stream\n"
" video stream2; video streams\n"
" video stream3; video streams\n"
" warppoint0;No warppoints\n"
" warppoint1; warppoint\n"
" warppoint2; warppoints\n"
" warppoint3; warppoints\n"
" week1; week\n"
" week2; weeks\n"
" week3; weeks\n"
" year1; year\n"
" year2; years\n"
" year3; years\n"
", ;, \n"
": ;: \n"
"3D;3D\n"
"3DType;3D Type\n"
"About;About\n"
"About_Hint;How to contact me and find last version\n"
"Accompaniment;Accompaniment\n"
"ActiveFormatDescription;Active Format Description\n"
"ActiveFormatDescription_MuxingMode;Active Format Description, Muxing mode\n"
"Actor;Actor\n"
"Actor_Character;Character played\n"
"AdID;Ad-ID identifier\n"
"Added_Date;Added date\n"
"Address;Address\n"
"Advanced;Advanced\n"
"Advanced mode;Advanced mode\n"
"Album;Album\n"
"Album_ReplayGain_Gain;Album replay gain\n"
"Album_ReplayGain_Peak;Album replay gain peak\n"
"Alignment;Alignment\n"
"Alignment_Aligned;Aligned on interleaves\n"
"Alignment_Split;Split accross interleaves\n"
"All;All\n"
"All;All\n"
"AlternateGroup;Alternate group\n"
"Archival_Location;Archival location\n"
"Arranger;Arranger\n"
"ArtDirector;ArtDirector\n"
"AspectRatio;Aspect ratio\n"
"AssistantDirector;AssistantDirector\n"
"at;at\n"
"At least one file;(You must at least open one file)\n"
"Audio;Audio\n"
"Audio stream(s);Audio streams\n"
"Audio_Codec_List;Audio codecs\n"
"Audio_No;No audio\n"
"Audio1;First audio stream\n"
"Audio2;Second audio stream\n"
"AudioComments;Audio Comments\n"
"AudioCount;Count of audio streams\n"
"AudioDescriptionPresent;Audio Description Present\n"
"AudioDescriptionType;Audio Description Type\n"
"AudioLoudnessStandard;Audio Loudness Standard\n"
"AudioTrackLayout;Audio Track Layout\n"
"Author;Author\n"
"BarCode;BarCode\n"
"Basic;Basic\n"
"Basic_Note;Note : for more information about this file, you must select a different view (Sheet, Tree...)\n"
"BedChannelConfiguration;Bed channel configuration\n"
"BedChannelCount;Bed channel count\n"
"BitDepth;位深\n"
"BitDepth_Detected;Detected bit depth\n"
"BitDepth_Stored;Stored bit depth\n"
"BitRate;Bit rate\n"
"BitRate_Encoded;Encoded bit rate\n"
"BitRate_Maximum;Maximum bit rate\n"
"BitRate_Minimum;Minimum bit rate\n"
"BitRate_Mode;Bit rate mode\n"
"BitRate_Mode_CBR;Constant\n"
"BitRate_Mode_VBR;Variable\n"
"BitRate_Nominal;Nominal bit rate\n"
"Bits-(Pixel*Frame);Bits/(Pixel*Frame)\n"
"BufferSize;Buffer size\n"
"Cancel;Cancel\n"
"Channel(s);Channel(s)\n"
"ChannelLayout;Channel layout\n"
"ChannelPositions;Channel positions\n"
"Chapter(s);Chapter(s)\n"
"Chapters;Chapters\n"
"Chapters stream(s);Chapters stream(s)\n"
"Chapters_Codec_List;Chapters Codecs\n"
"Chapters_No;No chapters\n"
"ChaptersCount;Count of chapter streams\n"
"CheckNewVersion;Check for new version\n"
"Choose custom;Choose custom\n"
"Choose custom sheet;Choose your desired custom sheet\n"
"Choose custom text;Choose your desired custom text\n"
"Choose export format;Choose your desired export format\n"
"Choose file(s);Choose the files to open\n"
"Choose filename;Choose your desired filename\n"
"Choose language;Choose your desired language\n"
"Choregrapher;Choregrapher\n"
"Chroma;Chroma\n"
"ChromaSubsampling;Chroma subsampling\n"
"Close;Close\n"
"Close all before open;Close all before open\n"
"ClosedCaptionsLanguage;Closed Captions Language\n"
"ClosedCaptionsPresent;Closed Captions Present\n"
"ClosedCaptionsType;Closed Captions Type\n"
"Codec;Codec\n"
"Codec_Description;Codec description\n"
"Codec_Info;Details for codec\n"
"Codec_Profile;Codec profile\n"
"Codec_Settings;Codec settings\n"
"Codec_Settings_BVOP;Codec settings, BVOP\n"
"Codec_Settings_CABAC;Codec settings, CABAC\n"
"Codec_Settings_Endianness;Codec settings, Endianness\n"
"Codec_Settings_Firm;Codec settings, Firm\n"
"Codec_Settings_Floor;Codec settings, Floor\n"
"Codec_Settings_GMC;Codec settings, GMC\n"
"Codec_Settings_ITU;Codec settings, ITU\n"
"Codec_Settings_Law;Codec settings, Law\n"
"Codec_Settings_Matrix;Codec settings, Matrix\n"
"Codec_Settings_PacketBitStream;Codec settings, Packet bitstream\n"
"Codec_Settings_QPel;Codec settings, QPel\n"
"Codec_Settings_Sign;Codec settings, Sign\n"
"Codec_Url;Weblink for codec\n"
"CodecConfigurationBox;Codec configuration box\n"
"CodecID;Codec ID\n"
"CodecID_Description;Description of the codec\n"
"CoDirector;Codirector\n"
"Collection;Collection\n"
"Colorimetry;Colorimetry\n"
"ColorSpace;Color space\n"
"colour_primaries;Color primaries\n"
"colour_range;Color range\n"
"Comment;Comment\n"
"CommissionedBy;Commissioned by\n"
"Compilation;Compilation\n"
"CompleteName;Complete name\n"
"CompletionDate;Completion Date\n"
"ComplexityIndex;Complexity index\n"
"Composer;Composer\n"
"Compression_Mode;Compression mode\n"
"Compression_Mode_Lossless;Lossless\n"
"Compression_Mode_Lossy;Lossy\n"
"Compression_Ratio;Compression ratio\n"
"Conductor;Conductor\n"
"ContactEmail;Contact Email\n"
"ContactTelephoneNumber;Contact Telephone Number\n"
"Container and general information;Container and general information\n"
"ContentType;ContentType\n"
"CoProducer;Coproducer\n"
"Copyright;Copyright\n"
"CopyrightYear;Copyright Year\n"
"CostumeDesigner;Costume designer\n"
"Count;Count\n"
"Country;Country\n"
"Cover;Cover\n"
"Cover_Datas;Cover datas\n"
"Cover_Description;Cover description\n"
"Cover_Mime;Cover MIME\n"
"Cover_Type;Cover type\n"
"Cropped;Crop dimensions\n"
"Custom;Custom\n"
"Customize;Customize\n"
"Date;Date\n"
"Debug;Debug\n"
"Decimal point;Decimal point\n"
"Delay;Delay\n"
"Delay_Source;Delay, origin\n"
"Delay_Source_Container;Container\n"
"Delay_Source_Stream;Raw stream\n"
"Delete;Delete\n"
"Description;Description\n"
"Digitized_Date;Digitized date\n"
"Dimensions;Dimensions\n"
"Director;Director\n"
"DirectorOfPhotography;Director of photography\n"
"Disabled;Disabled\n"
"DisplayAspectRatio;Display aspect ratio\n"
"DisplayAspectRatio_CleanAperture;Clean aperture display aspect ratio\n"
"DisplayAspectRatio_Original;Original display aspect ratio\n"
"DistributedBy;Distributed by\n"
"Distributor;Distributor\n"
"DolbyVision;Dolby Vision\n"
"DolbyVision_Layers;Dolby Vision layers\n"
"DolbyVision_Level;Dolby Vision level\n"
"DolbyVision_Profile;Dolby Vision profile\n"
"DolbyVision_Version;Dolby Vision version\n"
"Donate;Donate\n"
"DotsPerInch;Dots per inch\n"
"Duration;Duration\n"
"Duration_End;End time\n"
"Duration_Start;Start time\n"
"Edit;Edit\n"
"EditedBy;Edited by\n"
"ElementCount;Count of elements\n"
"EMail;E-Mail\n"
"Encoded_Application;Writing application\n"
"Encoded_Date;Encoded date\n"
"Encoded_Library;Writing library\n"
"Encoded_Library_Settings;Encoding settings\n"
"Encoded_Original;Original support\n"
"EncodedBy;Encoded by\n"
"EPG_Positions;EPG positions (internal)\n"
"EpisodeTitleNumber;Episode Title Number\n"
"Error_File;Error while reading file\n"
"ExecutiveProducer;Executive producer\n"
"Exit;Exit\n"
"Exit_Hint;Quit the program\n"
"Export;Export\n"
"Export_Hint;Export in a customized format\n"
"Extensions;Extensions usually used\n"
"Family;Family\n"
"Fax;Fax\n"
"File;File\n"
"File size;File size\n"
"File_Append;Append to the existing file (Warning : be careful to have the same parameters)\n"
"File_Created_Date;File creation date\n"
"File_Created_Date_Local;File creation date (local)\n"
"File_Hint;Select a multimedia file to examine\n"
"File_Modified_Date;File last modification date\n"
"File_Modified_Date_Local;File last modification date (local)\n"
"FileExtension;File extension\n"
"FileName;File name\n"
"FileNameExtension;File name\n"
"FileSize;File size\n"
"Folder;Folder\n"
"Folder (R);Folder (R)\n"
"Folder (R)_Hint;Select a folder to examine (with all folders recursively)\n"
"Folder (Recursively);Folder (Recursively)\n"
"Folder_Hint;Select a folder to examine\n"
"FolderName;Folder name\n"
"Format;Format\n"
"Format_Commercial;Commercial name\n"
"Format_Commercial_IfAny;Commercial name\n"
"Format_Description;Format description\n"
"Format_Info;Details for format\n"
"Format_Profile;Format profile\n"
"Format_Level;Format level\n"
"Format_Tier;Format tier\n"
"Format_Settings;Format settings\n"
"Format_Settings_BVOP;Format settings, BVOP\n"
"Format_Settings_CABAC;Format settings, CABAC\n"
"Format_Settings_Emphasis;Emphasis\n"
"Format_Settings_Endianness;Format settings, Endianness\n"
"Format_Settings_Firm;Format settings, Firm\n"
"Format_Settings_Floor;Format settings, Floor\n"
"Format_Settings_FrameMode;Frame mode\n"
"Format_Settings_GMC;Format settings, GMC\n"
"Format_Settings_GOP;Format settings, GOP\n"
"Format_Settings_ITU;Format settings, ITU\n"
"Format_Settings_Law;Format settings, Law\n"
"Format_Settings_Matrix;Format settings, Matrix\n"
"Format_Settings_Matrix_Custom;Custom\n"
"Format_Settings_Matrix_Default;Default\n"
"Format_Settings_Mode;Mode\n"
"Format_Settings_ModeExtension;Mode extension\n"
"Format_Settings_PacketBitStream;Format settings, Packet bitstream\n"
"Format_Settings_PictureStructure;Format settings, picture structure\n"
"Format_Settings_PS;Format settings, PS\n"
"Format_Settings_Pulldown;Format settings, Pulldown\n"
"Format_Settings_QPel;Format settings, QPel\n"
"Format_Settings_RefFrames;Format settings, ReFrames\n"
"Format_Settings_SBR;Format settings, SBR\n"
"Format_Settings_Sign;Format settings, Sign\n"
"Format_Settings_Wrapping;Format settings, wrapping mode\n"
"Format_Url;Weblink for format\n"
"Format_Version;Format version\n"
"FpaManufacturer;FPA Manufacturer\n"
"FpaPass;FPA Pass\n"
"FpaVersion;FPA Version\n"
"FrameCount;Frame count\n"
"FrameRate;Frame rate\n"
"FrameRate_Maximum;Maximum frame rate\n"
"FrameRate_Minimum;Minimum frame rate\n"
"FrameRate_Mode;Frame rate mode\n"
"FrameRate_Mode_CFR;Constant\n"
"FrameRate_Mode_VFR;Variable\n"
"FrameRate_Nominal;Nominal frame rate\n"
"FrameRate_Original;Original frame rate\n"
"General;General\n"
"Genre;Genre\n"
"Genre_000;Blues\n"
"Genre_001;Classic Rock\n"
"Genre_002;Country\n"
"Genre_003;Dance\n"
"Genre_004;Disco\n"
"Genre_005;Funk\n"
"Genre_006;Grunge\n"
"Genre_007;Hip-Hop\n"
"Genre_008;Jazz\n"
"Genre_009;Metal\n"
"Genre_010;New Age\n"
"Genre_011;Oldies\n"
"Genre_012;Other\n"
"Genre_013;Pop\n"
"Genre_014;R&B\n"
"Genre_015;Rap\n"
"Genre_016;Reggae\n"
"Genre_017;Rock\n"
"Genre_018;Techno\n"
"Genre_019;Industrial\n"
"Genre_020;Alternative\n"
"Genre_021;Ska\n"
"Genre_022;Death Metal\n"
"Genre_023;Pranks\n"
"Genre_024;Soundtrack\n"
"Genre_025;Euro-Techno\n"
"Genre_026;Ambient\n"
"Genre_027;Trip-Hop\n"
"Genre_028;Vocal\n"
"Genre_029;Jazz+Funk\n"
"Genre_030;Fusion\n"
"Genre_031;Trance\n"
"Genre_032;Classical\n"
"Genre_033;Instrumental\n"
"Genre_034;Acid\n"
"Genre_035;House\n"
"Genre_036;Game\n"
"Genre_037;Sound Clip\n"
"Genre_038;Gospel\n"
"Genre_039;Noise\n"
"Genre_040;Alt. Rock\n"
"Genre_041;Bass\n"
"Genre_042;Soul\n"
"Genre_043;Punk\n"
"Genre_044;Space\n"
"Genre_045;Meditative\n"
"Genre_046;Instrumental Pop\n"
"Genre_047;Instrumental Rock\n"
"Genre_048;Ethnic\n"
"Genre_049;Gothic\n"
"Genre_050;Darkwave\n"
"Genre_051;Techno-Industrial\n"
"Genre_052;Electronic\n"
"Genre_053;Pop-Folk\n"
"Genre_054;Eurodance\n"
"Genre_055;Dream\n"
"Genre_056;Southern Rock\n"
"Genre_057;Comedy\n"
"Genre_058;Cult\n"
"Genre_059;Gangsta Rap\n"
"Genre_060;Top 40\n"
"Genre_061;Christian Rap\n"
"Genre_062;Pop/Funk\n"
"Genre_063;Jungle\n"
"Genre_064;Native American\n"
"Genre_065;Cabaret\n"
"Genre_066;New Wave\n"
"Genre_067;Psychedelic\n"
"Genre_068;Rave\n"
"Genre_069;Showtunes\n"
"Genre_070;Trailer\n"
"Genre_071;Lo-Fi\n"
"Genre_072;Tribal\n"
"Genre_073;Acid Punk\n"
"Genre_074;Acid Jazz\n"
"Genre_075;Polka\n"
"Genre_076;Retro\n"
"Genre_077;Musical\n"
"Genre_078;Rock & Roll\n"
"Genre_079;Hard Rock\n"
"Genre_080;Folk\n"
"Genre_081;Folk-Rock\n"
"Genre_082;National Folk\n"
"Genre_083;Swing\n"
"Genre_084;Fast-Fusion\n"
"Genre_085;Bebop\n"
"Genre_086;Latin\n"
"Genre_087;Revival\n"
"Genre_088;Celtic\n"
"Genre_089;Bluegrass\n"
"Genre_090;Avantgarde\n"
"Genre_091;Gothic Rock\n"
"Genre_092;Progressive Rock\n"
"Genre_093;Psychedelic Rock\n"
"Genre_094;Symphonic Rock\n"
"Genre_095;Slow Rock\n"
"Genre_096;Big Band\n"
"Genre_097;Chorus\n"
"Genre_098;Easy Listening\n"
"Genre_099;Acoustic\n"
"Genre_100;Humour\n"
"Genre_101;Speech\n"
"Genre_102;Chanson\n"
"Genre_103;Opera\n"
"Genre_104;Chamber Music\n"
"Genre_105;Sonata\n"
"Genre_106;Symphony\n"
"Genre_107;Booty Bass\n"
"Genre_108;Primus\n"
"Genre_109;Porn Groove\n"
"Genre_110;Satire\n"
"Genre_111;Slow Jam\n"
"Genre_112;Club\n"
"Genre_113;Tango\n"
"Genre_114;Samba\n"
"Genre_115;Folklore\n"
"Genre_116;Ballad\n"
"Genre_117;Power Ballad\n"
"Genre_118;Rhythmic Soul\n"
"Genre_119;Freestyle\n"
"Genre_120;Duet\n"
"Genre_121;Punk Rock\n"
"Genre_122;Drum Solo\n"
"Genre_123;A Cappella\n"
"Genre_124;Euro-House\n"
"Genre_125;Dance Hall\n"
"Genre_126;Goa\n"
"Genre_127;Drum & Bass\n"
"Genre_128;Club-House\n"
"Genre_129;Hardcore\n"
"Genre_130;Terror\n"
"Genre_131;Indie\n"
"Genre_132;BritPop\n"
"Genre_133;Afro-Punk\n"
"Genre_134;Polsk Punk\n"
"Genre_135;Beat\n"
"Genre_136;Christian Gangsta Rap\n"
"Genre_137;Heavy Metal\n"
"Genre_138;Black Metal\n"
"Genre_139;Crossover\n"
"Genre_140;Contemporary Christian\n"
"Genre_141;Christian Rock\n"
"Genre_142;Merengue\n"
"Genre_143;Salsa\n"
"Genre_144;Thrash Metal\n"
"Genre_145;Anime\n"
"Genre_146;JPop\n"
"Genre_147;Synthpop\n"
"Genre_148;Abstract\n"
"Genre_149;Art Rock\n"
"Genre_150;Baroque\n"
"Genre_151;Bhangra\n"
"Genre_152;Big Beat\n"
"Genre_153;Breakbeat\n"
"Genre_154;Chillout\n"
"Genre_155;Downtempo\n"
"Genre_156;Dub\n"
"Genre_157;EBM\n"
"Genre_158;Eclectic\n"
"Genre_159;Electro\n"
"Genre_160;Electroclash\n"
"Genre_161;Emo\n"
"Genre_162;Experimental\n"
"Genre_163;Garage\n"
"Genre_164;Global\n"
"Genre_165;IDM\n"
"Genre_166;Illbient\n"
"Genre_167;Industro-Goth\n"
"Genre_168;Jam Band\n"
"Genre_169;Krautrock\n"
"Genre_170;Leftfield\n"
"Genre_171;Lounge\n"
"Genre_172;Math Rock\n"
"Genre_173;New Romantic\n"
"Genre_174;Nu-Breakz\n"
"Genre_175;Post-Punk\n"
"Genre_176;Post-Rock\n"
"Genre_177;Psytrance\n"
"Genre_178;Shoegaze\n"
"Genre_179;Space Rock\n"
"Genre_180;Trop Rock\n"
"Genre_181;World Music\n"
"Genre_182;Neoclassical\n"
"Genre_183;Audiobook\n"
"Genre_184;Audio Theatre\n"
"Genre_185;Neue Deutsche Welle\n"
"Genre_186;Podcast\n"
"Genre_187;Indie Rock\n"
"Genre_188;G-Funk\n"
"Genre_189;Dubstep\n"
"Genre_190;Garage Rock\n"
"Genre_191;Psybient\n"
"Go to WebSite;Go to website\n"
"Gop_OpenClosed;GOP, Open/Closed\n"
"Gop_OpenClosed_Open;Open\n"
"Gop_OpenClosed_Closed;Closed\n"
"Gop_OpenClosed_FirstFrame;GOP, Open/Closed of first frame\n"
"Grouping;Grouping\n"
"h; h\n"
"Header file;Create a header file\n"
"Height;Height\n"
"Height_CleanAperture;Clean aperture height\n"
"Height_Original;Original height\n"
"Help;Help\n"
"Hint;Hint\n"
"How many audio streams?;How many audio streams?\n"
"How many chapters streams?;How many chapters streams?\n"
"How many text streams?;How many text streams?\n"
"How many video streams?;How many video streams?\n"
"HTML;HTML\n"
"ID;ID\n"
"IdentClockStart;Ident Clock Start\n"
"Image;Image\n"
"Image stream(s);Image streams\n"
"Image_Codec_List;Codecs Image\n"
"ImageCount;Count of image streams\n"
"Info;Info\n"
"Instruments;Instruments\n"
"Interlaced_BFF;Bottom Field First\n"
"Interlaced_Interlaced;Interlaced\n"
"Interlaced_PPF;Progressive--PPF\n"
"Interlaced_Progressive;Progressive--PPF\n"
"Interlaced_TFF;Top Field First\n"
"Interlacement;Interlacement\n"
"Interleave_Duration;Interleave, duration\n"
"Interleave_Preload;Interleave, preload duration\n"
"Interleave_VideoFrames;Interleave, duration\n"
"Interleaved;Interleaved\n"
"InternetMediaType;Internet media type\n"
"IRCA;IRCA\n"
"ISBN;ISBN\n"
"ISRC;ISRC\n"
"Keywords;Keywords\n"
"Known codecs;Known codecs\n"
"Known formats;Known formats\n"
"Known parameters;Known parameters\n"
"Label;Label\n"
"Language;Language\n"
"Language_aa;Afar\n"
"Language_ab;Abkhazian\n"
"Language_ae;Avestan\n"
"Language_af;Afrikaans\n"
"Language_ak;Akan\n"
"Language_am;Amharic\n"
"Language_an;Aragonese\n"
"Language_ar;Arabic\n"
"Language_as;Assamese\n"
"Language_av;Avaric\n"
"Language_ay;Aymara\n"
"Language_az;Azerbaijani\n"
"Language_ba;Bashkir\n"
"Language_be;Belarusian\n"
"Language_bg;Bulgarian\n"
"Language_bh;Bihari\n"
"Language_bi;Bislama\n"
"Language_bm;Bambara\n"
"Language_bn;Bengali\n"
"Language_bo;Tibetan\n"
"Language_br;Breton\n"
"Language_bs;Bosnian\n"
"Language_ca;Catalan\n"
"Language_ce;Chechen\n"
"Language_ch;Chamorro\n"
"Language_co;Corsican\n"
"Language_cr;Cree\n"
"Language_cs;Czech\n"
"Language_cu;Slave\n"
"Language_cv;Chuvash\n"
"Language_cy;Welsh\n"
"Language_da;Danish\n"
"Language_de;German\n"
"Language_dv;Divehi\n"
"Language_dz;Dzongkha\n"
"Language_ee;Ewe\n"
"Language_el;Greek\n"
"Language_en;English\n"
"Language_en-gb;English (Great Britain)\n"
"Language_en-us;English (United States)\n"
"Language_eo;Esperanto\n"
"Language_es;Spanish\n"
"Language_es-419;Spanish (Latin America)\n"
"Language_et;Estonian\n"
"Language_eu;Basque\n"
"Language_fa;Persian\n"
"Language_ff;Fulah\n"
"Language_fi;Finnish\n"
"Language_fj;Fijian\n"
"Language_fo;Faroese\n"
"Language_fr;French\n"
"Language_fy;Frisian\n"
"Language_ga;Irish\n"
"Language_gd;Gaelic\n"
"Language_gl;Galician\n"
"Language_gn;Guarani\n"
"Language_gu;Gujarati\n"
"Language_gv;Manx\n"
"Language_ha;Hausa\n"
"Language_he;Hebrew\n"
"Language_hi;Hindi\n"
"Language_ho;Hiri Motu\n"
"Language_hr;Croatian\n"
"Language_ht;Haitian\n"
"Language_hu;Hungarian\n"
"Language_hy;Armenian\n"
"Language_hz;Herero\n"
"Language_ia;Auxiliary Language Association\n"
"Language_id;Indonesian\n"
"Language_ie;Interlingue\n"
"Language_ig;Igbo\n"
"Language_ii;Sichuan Yi\n"
"Language_ik;Inupiaq\n"
"Language_Info;Language info\n"
"Language_io;Ido\n"
"Language_is;Icelandic\n"
"Language_it;Italian\n"
"Language_iu;Inuktitut\n"
"Language_ja;Japanese\n"
"Language_jv;Javanese\n"
"Language_ka;Georgian\n"
"Language_kg;Kongo\n"
"Language_ki;Kikuyu\n"
"Language_kj;Kuanyama\n"
"Language_kk;Kazakh\n"
"Language_kl;Kalaallisut\n"
"Language_km;Khmer\n"
"Language_kn;Kannada\n"
"Language_ko;Korean\n"
"Language_kr;Kanuri\n"
"Language_ks;Kashmiri\n"
"Language_ku;Kurdish\n"
"Language_kv;Komi\n"
"Language_kw;Cornish\n"
"Language_ky;Kirghiz\n"
"Language_la;Latin\n"
"Language_lb;Luxembourgish\n"
"Language_lg;Ganda\n"
"Language_li;Limburgish\n"
"Language_ln;Lingala\n"
"Language_lo;Lao\n"
"Language_lt;Lithuanian\n"
"Language_lu;Luba-Katanga\n"
"Language_lv;Latvian\n"
"Language_mg;Malagasy\n"
"Language_mh;Marshallese\n"
"Language_mi;Maori\n"
"Language_mk;Macedonian\n"
"Language_ml;Malayalam\n"
"Language_mn;Mongolian\n"
"Language_mo;Moldavian\n"
"Language_More;Language, more info\n"
"Language_mr;Marathi\n"
"Language_ms;Malay\n"
"Language_mt;Maltese\n"
"Language_mul;Multiple languages\n"
"Language_my;Burmese\n"
"Language_na;Nauru\n"
"Language_nb;Norwegian Bokmal\n"
"Language_nd;Ndebele\n"
"Language_ne;Nepali\n"
"Language_ng;Ndonga\n"
"Language_nl;Dutch\n"
"Language_nn;Norwegian Nynorsk\n"
"Language_no;Norwegian\n"
"Language_nr;Ndebele\n"
"Language_nv;Navaho\n"
"Language_ny;Nyanja\n"
"Language_oc;Occitan\n"
"Language_oj;Ojibwa\n"
"Language_om;Oromo\n"
"Language_or;Oriya\n"
"Language_os;Ossetic\n"
"Language_pa;Panjabi\n"
"Language_pi;Pali\n"
"Language_pl;Polish\n"
"Language_ps;Pushto\n"
"Language_pt;Portuguese\n"
"Language_pt-br;Portuguese (Brazil)\n"
"Language_qu;Quechua\n"
"Language_rm;Raeto-Romance\n"
"Language_rn;Rundi\n"
"Language_ro;Romanian\n"
"Language_ru;Russian\n"
"Language_rw;Kinyarwanda\n"
"Language_sa;Sanskrit\n"
"Language_sc;Sardinian\n"
"Language_sd;Sindhi\n"
"Language_se;Northern Sami\n"
"Language_sg;Sango\n"
"Language_si;Sinhala\n"
"Language_sk;Slovak\n"
"Language_sl;Slovenian\n"
"Language_sm;Samoan\n"
"Language_sn;Shona\n"
"Language_so;Somali\n"
"Language_sq;Albanian\n"
"Language_sr;Serbian\n"
"Language_ss;Swati\n"
"Language_st;Sotho\n"
"Language_su;Sundanese\n"
"Language_sv;Swedish\n"
"Language_sw;Swahili\n"
"Language_ta;Tamil\n"
"Language_te;Telugu\n"
"Language_tg;Tajik\n"
"Language_th;Thai\n"
"Language_ti;Tigrinya\n"
"Language_tk;Turkmen\n"
"Language_tl;Tagalog\n"
"Language_tn;Tswana\n"
"Language_to;Tonga\n"
"Language_tr;Turkish\n"
"Language_ts;Tsonga\n"
"Language_tt;Tatar\n"
"Language_tw;Twi\n"
"Language_ty;Tahitian\n"
"Language_ug;Uighur\n"
"Language_uk;Ukrainian\n"
"Language_ur;Urdu\n"
"Language_uz;Uzbek\n"
"Language_ve;Venda\n"
"Language_vi;Vietnamese\n"
"Language_vo;Volapuk\n"
"Language_wa;Walloon\n"
"Language_wo;Wolof\n"
"Language_xh;Xhosa\n"
"Language_yi;Yiddish\n"
"Language_yo;Yoruba\n"
"Language_za;Zhuang\n"
"Language_zh;Chinese\n"
"Language_zh-cn;Chinese (China)\n"
"Language_zh-tw;Chinese (Taiwan)\n"
"Language_zu;Zulu\n"
"LawRating;Law rating\n"
"LCCN;LCCN\n"
"Library;Muxing library\n"
"Lightness;Lightness\n"
"LineUpStart;Line Up Start\n"
"List;List\n"
"Lyricist;Lyricist\n"
"Lyrics;Lyrics\n"
"Mastered_Date;Mastered date\n"
"MasteredBy;Mastered by\n"
"MasteringDisplay_ColorPrimaries;Mastering display color primaries\n"
"MasteringDisplay_Luminance;Mastering display luminance\n"
"Matrix_Channel(s);Matrix encoding, Channel(s)\n"
"Matrix_ChannelPositions;Matrix encoding, channel positions\n"
"matrix_coefficients;Matrix coefficients\n"
"Matrix_Format;Matrix encoding, format\n"
"MaxCLL;Maximum Content Light Level\n"
"MaxFALL;Maximum Frame-Average Light Level\n"
"MediaInfo_About;MediaInfo provides easy access to technical and tag information about video and audio files.\r\nExcept the Mac App Store graphical user interface, it is open-source software, which means that it is free of charge to the end user and developers have freedom to study, to improve and to redistribute the program (BSD license)\n"
"Menu;Menu\n"
"Menu stream(s);Menu streams\n"
"Menu_Codec_List;Menu codecs\n"
"Menu_Hint;More possibilities\n"
"Menu_No;No menu\n"
"MenuCount;Count of menu streams\n"
"MenuID;Menu ID\n"
"NumberOfDynamicObjects;Number of dynamic objects\n"
"mn; min\n"
"Mood;Mood\n"
"More;More\n"
"Movie;Movie name\n"
"ms; ms\n"
"MSDI;MSDI\n"
"MusicBy;Music by\n"
"MuxingMode;Muxing mode\n"
"MuxingMode_MoreInfo;Muxing mode, more info\n"
"MuxingMode_PackedBitstream;Packed bitstream\n"
"Name;Name\n"
"Nationality;Nationality\n"
"NetworkName;Network name\n"
"New;New\n"
"Newest version;Check for new versions (requires Internet connection)\n"
"NewVersion_Menu;A new version is available\n"
"NewVersion_Question_Content;A new version (v%Version%) is available, would you like to download it?\n"
"NewVersion_Question_Title;A new version was released!\n"
"No;No\n"
"Not yet;Not yet\n"
"NumColors;Number of colors\n"
"OK;OK\n"
"One output file per input file;One output file per input file\n"
"Open;Open\n"
"OpenCandy_01;Downloading ________\n"
"OpenCandy_02;__% Complete\n"
"OpenCandy_03;Internet connection interrupted\n"
"OpenCandy_04;________ download complete\n"
"OpenCandy_05;Click to install ________\n"
"OpenCandy_06;Are you sure you wish to cancel the install?\r\nIf you wish to postpone the install until later, select 'No'.\r\nNote: You may select Exit from the menu to defer installation until after the next time you reboot.\n"
"OpenCandy_07;Download of ________ has been paused.\r\nClick on the tray icon to resume downloading.\n"
"OpenCandy_08;A critical error has occurred. Installation of _________ will be aborted.\n"
"OpenCandy_09;Pause download\n"
"OpenCandy_10;Cancel install\n"
"OpenCandy_11;Resume download\n"
"OpenCandy_12;Exit Installer\n"
"OpenCandy_13;___________ - Recommended by ____________\n"
"OpenCandy_14;Downloading _________\n"
"OpenCandy_15;___________, the software recommended to you by ___________, is now downloading at your requestWe will let you know when it is ready to be installed.\n"
"OpenCandy_16;___________ is ready for installation\n"
"OpenCandy_17;___________ is now fully downloaded. Please click on 'Install' to proceed.\n"
"OpenCandy_18;___________ of ___________ downloaded\n"
"OpenCandy_19;Powered by OpenCandy\n"
"OpenCandy_20;Learn more at OpenCandy.com\n"
"OpenCandy_21;Install\n"
"OpenCandy_22;Installation of ___________\n"
"OpenCandy_23;This will cancel the installation of ___________\r\nAre you sure you wish to exit?\n"
"OpenCandy_24;Pause\n"
"OpenCandy_25;Your download has been paused. Click 'Resume' when you are ready to continue.\n"
"OpenCandy_26;Resume\n"
"OpenCandy_27;Install Now\n"
"OpenCandy_28;Pause Download\n"
"OpenCandy_29;Resume Download\n"
"OpenCandy_30;Cancel Install\n"
"OpenCandy_31;Please choose an installation option\n"
"OpenCandy_32;Install ___________\n"
"OpenCandy_33;Don't Install\n"
"OpenCandy_34;Please select an install option\n"
"OpenCandy_35;______ recommends this software\n"
"OpenCandy_36;Your current installation will not be interrupted\n"
"OpenCaptionsLanguage;Open Captions Language\n"
"OpenCaptionsPresent;Open Captions Present\n"
"OpenCaptionsType;Open Captions Type\n"
"Options;Options\n"
"Options_Hint;Preferences\n"
"Original;Original\n"
"OriginalNetworkName;Original network name\n"
"OriginalSourceForm;Original source form\n"
"OriginalSourceMedium;Original source medium\n"
"OriginalSourceMedium_ID;ID in the original source medium\n"
"Originator;Originator\n"
"Other;Other\n"
"OtherIdentifier;Other Identifier\n"
"OtherIdentifierType;Other Identifier Type\n"
"Output;Output\n"
"Output format;Output format\n"
"OverallBitRate;Overall bit rate\n"
"OverallBitRate_Maximum;Maximum Overall bit rate\n"
"OverallBitRate_Minimum;Minimum Overall bit rate\n"
"OverallBitRate_Mode;Overall bit rate mode\n"
"OverallBitRate_Nominal;Nominal Overall bit rate\n"
"PackageName;Package name\n"
"Part;Part\n"
"Part_Count;Total count\n"
"PartNumber;Part Number\n"
"PartTotal;Part Total\n"
"Performer;Performer\n"
"Period;Period\n"
"PodcastCategory;Podcast category\n"
"Phone;Phone\n"
"PictureRatio;Picture Ratio\n"
"PixelAspectRatio;Pixel aspect ratio\n"
"PixelAspectRatio_CleanAperture;Clean aperture pixel aspect ratio\n"
"PixelAspectRatio_Original;Original pixel aspect ratio\n"
"PlayCounter;PlayCounter\n"
"Played_Count;Times played\n"
"Played_First_Date;First played\n"
"Played_Last_Date;Last played\n"
"PlayTime;PlayTime\n"
"Position;Position\n"
"Position_Total;Total\n"
"Preferences;Preferences\n"
"PrimaryAudioLanguage;Primary Audio Language\n"
"Producer;Producer\n"
"ProductionDesigner;Production designer\n"
"ProductionNumber;Production Number\n"
"ProductionStudio;Production studio\n"
"ProductPlacement;Product Placement\n"
"ProgrammeHasText;Programme Has Text\n"
"ProgrammeTextLanguage;Programme Text Language\n"
"ProgrammeTitle;Programme Title\n"
"Publisher;Publisher\n"
"Purchased_Date;purchased date\n"
"Quote character;Quote character\n"
"RadioStation;Radio station\n"
"Rating;Rating\n"
"Recorded_Date;Recorded date\n"
"Recorded_Location;Recorded location\n"
"Released_Date;Released date\n"
"RemixedBy;Remixed by\n"
"ReplayGain_Gain;Replay gain\n"
"ReplayGain_Peak;Replay gain peak\n"
"Resolution;Resolution\n"
"s; s\n"
"SamplesPerFrame;Samples per frame\n"
"SamplingCount;Samples count\n"
"SamplingRate;Sampling rate\n"
"Save;Save\n"
"ScanOrder;Scan order\n"
"ScanOrder_Original;Original scan order\n"
"ScanOrder_Stored;Stored scan order\n"
"ScanOrder_StoredDisplayedInverted;Scan order, stored/displayed order inverted\n"
"ScanOrder_StoreMethod;Scan order, store method\n"
"ScanType;Scan type\n"
"ScanType_Original;Original scan type\n"
"ScanType_StoreMethod;Scan type, store method\n"
"ScreenplayBy;Screenplay by\n"
"Season;Season\n"
"SecondaryAudioLanguage;Secondary Audio Language\n"
"see below;see below\n"
"Send HeaderFile;Please send me the Header file here : http://sourceforge.net/projects/mediainfo/ (Bug section)\n"
"Separator_Columns;columns separator\n"
"Separator_Lines;lines separator\n"
"SeriesTitle;Series Title\n"
"ServiceChannel;Service channel number\n"
"ServiceKind;Service kind\n"
"ServiceName;Service name\n"
"ServiceProvider;Service provider\n"
"ServiceType;Service type\n"
"Set;Set\n"
"Set_Count;Set count\n"
"Setup;Setup\n"
"Sharpness;Sharpness\n"
"Sheet;Sheet\n"
"Sheet (Complete);Sheet (Complete)\n"
"Shell extension;Explorer extension (in Windows Explorer, right click on a file, there will be a MediaInfo option)\n"
"Shell extension, folder;For folders too\n"
"Shell InfoTip;Explorer Tooltip (in Windows Explorer, move the mouse over the file, info will be displayed)\n"
"ShimName;Shim Name\n"
"ShimVersion;Shim Version\n"
"Show menu;Show menu\n"
"Show toolbar;Show toolbar\n"
"SigningPresent;Signing Present\n"
"SignLanguage;Sign Language\n"
"Sort;Sorted by\n"
"SoundEngineer;Sound engineer\n"
"Source;Source\n"
"Source_Duration;Source duration\n"
"Source_FrameCount;Source frame count\n"
"Source_SamplingCount;Source sample count\n"
"Source_StreamSize;Source stream size\n"
"Source_StreamSize_Encoded;Source encoded stream size\n"
"Standard;Standard\n"
"StoreMethod_InterleavedFields;Interleaved fields\n"
"StoreMethod_SeparatedFields;Separated fields\n"
"StoreMethod_SeparatedFields_1;Separated fields (1 field per block)\n"
"StoreMethod_SeparatedFields_2;Separated fields (2 fields per block)\n"
"Stream;Stream\n"
"Stream_MoreInfo;More information about the stream\n"
"StreamCount;Count of stream of this kind\n"
"StreamID;Stream ID\n"
"StreamKind;Kind of stream\n"
"StreamKindID;Stream identifier\n"
"StreamKindPos;Stream identifier\n"
"StreamSize;Stream size\n"
"StreamSize_Demuxed;Stream size when demuxed\n"
"StreamSize_Encoded;Encoded stream size\n"
"StreamSize_Proportion;Proportion of this stream\n"
"Subject;Subject\n"
"SubTrack;SubTrack\n"
"Summary;Summary\n"
"Supported formats;Supported formats\n"
"Supported?;Supported?\n"
"Synopsis;Synopsis\n"
"SystemId;Id\n"
"Tagged_Application;Tagging application\n"
"Tagged_Date;Tagged date\n"
"Technician;Technician\n"
"TermsOfUse;Terms of use\n"
"TertiaryAudioLanguage;Tertiary Audio Language\n"
"Text;Text\n"
"Text - Custom;Text - Custom\n"
"Text (HTML);Text (HTML)\n"
"Text stream(s);Text streams\n"
"Text streams;Text streams\n"
"Text_Codec_List;Text codecs\n"
"Text_No;No text\n"
"Text1;First text stream\n"
"Text2;Second text stream\n"
"Text3;Third text stream\n"
"TextCount;Count of text streams\n"
"TextlessElementsExist;Textless Elements Exist\n"
"ThanksTo;Thanks to\n"
"Thousands separator;Thousands separator\n"
"TimeCode;Time code\n"
"TimeCode_FirstFrame;Time code of first frame\n"
"TimeCode_Settings;Time code settings\n"
"TimeCode_Source;Time code source\n"
"TimeCode_Striped;Time code, striped\n"
"TimeStamp;Time stamp\n"
"TimeZone;Timezone\n"
"Title;Title\n"
"Title_More;Title, more info\n"
"Total;Total\n"
"TotalNumberOfParts;Total Number Of Parts\n"
"TotalProgrammeDuration;Total Programme Duration\n"
"Track;Track name\n"
"Track_Count;Track count\n"
"transfer_characteristics;Transfer characteristics\n"
"Translator;Translator\n"
"Tree;Tree\n"
"Tree & Text;Tree & Text\n"
"Type;Type\n"
"UniqueID;Unique ID\n"
"UniversalAdID;Universal Ad ID\n"
"UniversalAdID_Registry;Universal Ad ID registry\n"
"UniversalAdID_Value;Universal Ad ID value\n"
"Unknown;Unknown\n"
"Url;Url\n"
"Video;Video\n"
"Video stream(s);Video stream(s)\n"
"Video_Codec_List;Codecs Video\n"
"Video_Delay;Delay relative to video\n"
"Video_No;No video\n"
"Video0_Delay;Video0 delay\n"
"Video1;First video stream\n"
"VideoComments;Video Comments\n"
"VideoCount;Count of video streams\n"
"View;View\n"
"View_Hint;Change the means of viewing information\n"
"Warning : more streams in the files;Warning : there are more streams in the files\n"
"Web;Web\n"
"WebSite_Audio;Go to the web site of this audio codec\n"
"WebSite_Audio_More;Go to the web site (%Url%) to find this audio codec\n"
"WebSite_General;Go to the web site of a player for this file\n"
"WebSite_General_More;Go to the web site of a player for this file\n"
"WebSite_Text;Go to the web site of this text codec\n"
"WebSite_Text_More;Go to the web site (%Url%) to find this text codec\n"
"WebSite_Url;http://MediaArea.net/MediaInfo\n"
"WebSite_Video;Go to the web site of this video codec\n"
"WebSite_Video_More;Go to the web site (%Url%) to find this video codec\n"
"Width;Width\n"
"Width_CleanAperture;Clean aperture width\n"
"Width_Original;Original width\n"
"WriteMe;Write mail to author\n"
"WriteToTranslator;Write to translator\n"
"Written_Date;Written date\n"
"Written_Location;Written location\n"
"WrittenBy;Written by\n"
"Yes;Yes\n"
"Your system;Your system\n"
"ZZ_Automatic_Percent;100\n"
"ZZ_AutomaticLanguage_Percent;100\n");

MediaInfoDialog::MediaInfoDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MediaInfoDialog),
    m_isFFprobe(false),
    m_child(false),
    m_fromCLI(false)
{
    ui->setupUi(this);
    this->setupUi();
}

MediaInfoDialog::~MediaInfoDialog()
{
    delete m_pContextMenu;
    delete ui;
}

void MediaInfoDialog::setupUi(void)
{
    this->setAcceptDrops(true);
    ui->editMediaInfo->setAcceptDrops(false);
    ui->editMediaInfo->setContextMenuPolicy(Qt::CustomContextMenu);

    /* MediaInfoMenu */
    m_pContextMenu = new QMenu(ui->editMediaInfo);
    QAction *at_action_load = new QAction(QIcon(":/buttons/folder_add.png"), tr("Open..."), ui->editMediaInfo);
    QAction *at_action_preview = new QAction(QIcon(":/buttons/film.png"), tr("Preview"), ui->editMediaInfo);
    QAction *at_action_copy = new QAction(QIcon(":/buttons/page_paste.png"), tr("Copy to Clipboard"), ui->editMediaInfo);
    QAction *at_action_save = new QAction(QIcon(":/buttons/disk.png"), tr("Save to the Same Here"), ui->editMediaInfo);
    QAction *at_action_add_media_form = new QAction(QIcon(":/buttons/application_add.png"), tr("Add a Form"), ui->editMediaInfo);
    QAction *at_action_calc_md5 = new QAction(QIcon(":/buttons/tag_blue.png"), tr("Calculate MD5"), ui->editMediaInfo);
    QAction *at_action_using_ffprobe = new QAction(QIcon(":/buttons/ffmpeg.png"), tr("From FFprobe"), ui->editMediaInfo);
    QAction *at_action_show_full_info = new QAction(QIcon(":/buttons/text_wrapping.png"), tr("Show Full Info"), ui->editMediaInfo);
    QAction *at_action_enable_line_wrapping = new QAction(QIcon(":/buttons/text_wrapping.png"), tr("Enable Line Wrap"), ui->editMediaInfo);
    at_action_using_ffprobe->setCheckable(true);
    at_action_show_full_info->setCheckable(true);
    at_action_enable_line_wrapping->setCheckable(true);
    at_action_enable_line_wrapping->setChecked(true);
    m_pContextMenu->addActions(QList<QAction*>() << at_action_load << at_action_add_media_form);
    m_pContextMenu->addSeparator();
    m_pContextMenu->addActions(QList<QAction*>() << at_action_preview << at_action_copy << at_action_save);
    m_pContextMenu->addSeparator();
    m_pContextMenu->addActions(QList<QAction*>() << at_action_calc_md5 << at_action_using_ffprobe << at_action_show_full_info << at_action_enable_line_wrapping);
    connect(at_action_load, SIGNAL(triggered()), this, SLOT(selectMediafile()));
    connect(at_action_add_media_form, SIGNAL(triggered()), this, SLOT(addMediainfoForm()));
    connect(at_action_preview, SIGNAL(triggered()), this, SLOT(slotPreview()));
    connect(at_action_copy, SIGNAL(triggered()), this, SLOT(on_buttonMediaInfoCopy_clicked()));
    connect(at_action_save, SIGNAL(triggered()), this, SLOT(on_buttonMediaInfoSave_clicked()));
    connect(at_action_using_ffprobe, SIGNAL(triggered(bool)), this, SLOT(setFFprobe(bool)));
    connect(at_action_show_full_info, SIGNAL(triggered(bool)), this, SLOT(setFull(bool)));
    connect(at_action_enable_line_wrapping, SIGNAL(triggered(bool)), this, SLOT(setWrapped(bool)));
    connect(at_action_calc_md5, SIGNAL(triggered()), this, SLOT(calcMd5()));

    /*Signal*/
    connect(&m_process_sub, SIGNAL(readyReadStandardError()), this, SLOT(slotSubProcessReadyReadStandardError()));
    connect(&m_process_sub, SIGNAL(readyReadStandardOutput()), this, SLOT(slotSubProcessReadyReadStandardOutput()));
}

void MediaInfoDialog::setChild(bool a_child)
{
    m_child = a_child;
    ui->editMediaInfo->setAcceptDrops(true);
    this->setAcceptDrops(true);
}

bool MediaInfoDialog::isChild(void)
{
    return m_child;
}

void MediaInfoDialog::setPath(const QString &a_filename)
{
    m_mediainfo_path = a_filename;
}

QString MediaInfoDialog::getPath(void)
{
    return m_mediainfo_path;
}

void MediaInfoDialog::append(QString a_text)
{
    ui->editMediaInfo->append(a_text);
}

void MediaInfoDialog::clear(void)
{
    ui->editMediaInfo->clear();
}

void MediaInfoDialog::reload(QString a_filename)
{
    if(!a_filename.isEmpty())
    {
        showMediaInfo(a_filename, ui->checkBoxMediaInfoFull->isChecked());
        m_mediainfo_path = a_filename;
    }
}

void MediaInfoDialog::reload(void)
{
    if(!m_mediainfo_path.isEmpty())
    {
        showMediaInfo(m_mediainfo_path, ui->checkBoxMediaInfoFull->isChecked());
    }
}

void MediaInfoDialog::showMediaInfo(void)
{
    showMediaInfo(m_mediainfo_path, ui->checkBoxMediaInfoFull->isChecked());
}

void MediaInfoDialog::showMediaInfo(const QString &a_filename)
{
    showMediaInfo(a_filename, ui->checkBoxMediaInfoFull->isChecked());
}

void MediaInfoDialog::showMediaInfo(const QString &a_filename, bool a_is_full_info)
{
    if(a_filename.isEmpty())
    {
        return;
    }

    if(m_fromCLI)
    {
        QString cmd;

        if(m_isFFprobe)
        {
            cmd = QString("%1 -show_streams -show_chapters -of json %3 \"%2\"").arg(mainUi->m_com->findFirstFilePath("ffprobe.exe")).arg(a_filename).arg("-show_format " + (a_is_full_info) ? "-show_data" : "");
        }
        else
        {
            cmd = QString("%1 \"%2\"").arg(mainUi->m_com->findFirstFilePath("MediaInfo.exe")).arg(a_filename) + ((a_is_full_info) ? " -f" : "");
        }

        ui->editMediaInfo->clear();
        if(m_process_sub.state() != QProcess::NotRunning)
        {
            m_process_sub.kill();
            m_process_sub.waitForFinished();
        }
        m_process_sub.start(cmd);
    }
    else
    {
        MediaInfoLoader mediainfoLoder(a_filename);

        ui->editMediaInfo->setText(mediainfoLoder.inform(a_is_full_info));
        mediainfoLoder.close();
    }
}

void MediaInfoDialog::on_editMediaInfo_customContextMenuRequested(const QPoint &)
{
    m_pContextMenu->exec(QCursor::pos());
}

void MediaInfoDialog::on_buttonMediaInfoSave_clicked()
{
    QString text = ui->editMediaInfo->toPlainText();

    if( text.isEmpty() || m_mediainfo_path.isEmpty() )
    {
        return;
    }

    QFile file(QString("%1.txt").arg(m_mediainfo_path));
    QTextStream out(&file);

    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qDebug() << "Open MediaInfo log file failed.";
        return;
    }
    out << text;
    file.close();
}

void MediaInfoDialog::on_buttonMediaInfoCopy_clicked()
{
    QClipboard *clipboard = QApplication::clipboard();
    clipboard->setText(ui->editMediaInfo->toPlainText());
}

void MediaInfoDialog::setWrapped(bool a_enable)
{
    if(a_enable)
    {
        ui->editMediaInfo->setLineWrapMode(QTextEdit::WidgetWidth);
    }
    else
    {
        ui->editMediaInfo->setLineWrapMode(QTextEdit::NoWrap);
    }
}

void MediaInfoDialog::calcMd5(void)
{
    if(!m_mediainfo_path.isEmpty())
    {
        if(!isChild())
        {
            mainUi->m_timer->start(Timer::ETIMER_TYPE_ONE_SHOT, Timer::ETIMER_SLOT_CALC_MD5);
        }
        else
        {
            QString md5 = mainUi->m_com->getHashMd5(getPath());

            clear();
            append(tr("Filename: ") + QFileInfo(getPath()).fileName());
            append(tr("MD5: ") + md5);
        }
    }
}

void MediaInfoDialog::setFull(bool a_state)
{
    ui->checkBoxMediaInfoFull->setChecked(a_state);
}

void MediaInfoDialog::on_checkBoxMediaInfoFull_stateChanged(int a_state)
{
    showMediaInfo(m_mediainfo_path, (bool)a_state);
    m_pContextMenu->actions().at(eCONTEXT_MENU_SHOW_FULL_INFO)->setChecked((bool)a_state);
}

void MediaInfoDialog::setFFprobe(bool a_state)
{
    m_isFFprobe = a_state;
    m_fromCLI = a_state;
    reload();
}

void MediaInfoDialog::slotSubProcessReadyReadStandardError()
{
    QByteArray standardError = m_process_sub.readAllStandardError();
    QString standardErrorText = QString::fromUtf8(standardError);
    standardErrorText = standardErrorText.trimmed();
    if(!standardErrorText.isEmpty())
    {
       ui->editMediaInfo->append(standardErrorText);
       ui->editMediaInfo->moveCursor(QTextCursor::Start);
    }
}

void MediaInfoDialog::slotSubProcessReadyReadStandardOutput()
{
    QByteArray standardOutput = m_process_sub.readAllStandardOutput();
    QString standardOutputText = QString::fromUtf8(standardOutput);
    standardOutputText = standardOutputText.trimmed();
    if(!standardOutputText.isEmpty())
    {
        ui->editMediaInfo->append(standardOutputText);
        ui->editMediaInfo->moveCursor(QTextCursor::Start);
    }
}

void MediaInfoDialog::selectMediafile(void)
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Open Mediafile"), NULL, tr("Media (*.*)"));

    if(!filename.isEmpty())
    {
        reload(filename);
    }
}

void MediaInfoDialog::addMediainfoForm(void)
{
    MediaInfoDialog *new_form = new MediaInfoDialog();
    new_form->mainUi = mainUi;
    new_form->setChild(true);
    new_form->m_uid_own = QUuid::createUuid();
    new_form->resize(this->width(), this->height());
    new_form->show();
    mainUi->m_pMediaInfoDialogs.insert(new_form->m_uid_own, new_form);
}

void MediaInfoDialog::slotPreview(void)
{
    if(m_mediainfo_path.isEmpty())
    {
        return;
    }

    ScriptPlayer *at_pScriptPlayer = new ScriptPlayer();

    at_pScriptPlayer->mainUi = mainUi;
    at_pScriptPlayer->m_uid_own = QUuid::createUuid();

    if(at_pScriptPlayer->reloadTypeDetect(m_mediainfo_path) == ScriptPlayer::eSCRIPT_TYPE_NOT_SCRIPT)
    {
        at_pScriptPlayer->hide();
        QProcess::startDetached(QString("cmd /c %1").arg(m_mediainfo_path));
        delete at_pScriptPlayer;
        at_pScriptPlayer = nullptr;
    }
    else
    {
        at_pScriptPlayer->show();
        at_pScriptPlayer->slotPlayOnMounted(true);
        at_pScriptPlayer->reload(m_mediainfo_path);
        mainUi->m_pScriptPlayers.insert(at_pScriptPlayer->m_uid_own, at_pScriptPlayer);
    }
}

void MediaInfoDialog::on_buttonMediaInfoPreview_clicked()
{
    slotPreview();
}

void MediaInfoDialog::dragEnterEvent(QDragEnterEvent* e)
{
    if(e->mimeData()->hasText())
    {
        e->acceptProposedAction();
    }
}

void MediaInfoDialog::dropEvent(QDropEvent* e)
{
    const QMimeData* mime = e->mimeData();

    if(mime->hasUrls())
    {
        foreach(QUrl url, e->mimeData()->urls())
        {
            QFileInfo file(url.toLocalFile());
            QString filename = file.canonicalFilePath();
            filename = QDir::toNativeSeparators(filename);
            if(!QFileInfo(filename).isFile())
            {
                continue;
            }
            showMediaInfo(filename, ui->checkBoxMediaInfoFull->isChecked());
            m_mediainfo_path = filename;
        }
    }
    e->acceptProposedAction();
}

void MediaInfoDialog::closeEvent(QCloseEvent *e)
{
    StdManager::releaseStdWatch(m_uid);
    e->accept();
}
