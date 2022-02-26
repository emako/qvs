# qvs

![](https://img.shields.io/badge/qvs-r17.2-green)
![](https://img.shields.io/tokei/lines/github/emako/qvs)
![](https://img.shields.io/github/license/emako/qvs?color=blue)
![](https://img.shields.io/github/stars/emako/qvs?color=blue)
![](https://img.shields.io/github/forks/emako/qvs?color=blue)


<img src="res/images/qvs.png" width = "200" height = "200" alt="" align=center />
A simple program for using VapourSynth/Avisynth Script previewed and encoded.



## Download

[![GitHub downloads](https://img.shields.io/github/downloads/emako/qvs/total)](https://github.com/emako/qvs/releases)
[![GitHub downloads](https://img.shields.io/github/downloads/emako/qvs/latest/total)](https://github.com/emako/qvs/releases)

You can download from [releases](https://github.com/emako/qvs/releases) page.

See the [changelog.md](changelog.md) page.



## Main Features

- [x] New script(*.vpy), also using blockly, a visual programming tools.
- [x] Encode script(*.vpy) or video, also using x264/x265/NVEnc/QSVEnc/VCEEnc encoders.
- [x] Encode audio, also using AAC/MP3/ALAC/FLAC/OPUS/OGG Vorbis/AC3/WAV encoders.
- [x] Muxer video and audio, also using MP4Box/L-smash/MKVMerge/FFMpeg tools.
- [x] Demuxer video, also using FFMpeg/Eac3to/MKVExtract/TsDemux tools.
- [x] Create single image video.
- [x] Splite/Merge media file.
- [x] Show MediaInfo.
- [ ] Audio Cutter.



## Screen Shot

- ##### Main UI

![main-encode](res/images/screen-shot/main-encode.jpg)  

- ##### Mediainfo UI

![mediainfo](res/images/screen-shot/mediainfo.jpg)  

- ##### Create Script from Add New Job

![add-job](res/images/screen-shot/add-job.jpg)  

- ##### Create Script from blockly UI

![script_blockly](res/images/screen-shot/script-blockly.png)



- ##### Script Mount UI

![script-mount](res/images/screen-shot/script-mount.jpg)



- ##### Script Preview UI

![script-preview](res/images/screen-shot/script-preview.jpg)



## Building

qvs is developed based on Qt5.

See [build.md](build.md) for more details.



## Issuse

![GitHub issues](https://img.shields.io/github/issues/emako/qvs) ![GitHub closed issues](https://img.shields.io/github/issues-closed/emako/qvs)

VapourSynth is developing fastly, so API expiration problems are easy to occur.

Leave your [issuse](https://github.com/emako/qvs/issues) for any question.



## Future

1. May add `audio track support`, but depending on the update of `vsedit`.

2. About Blockly, Qt support for the web (blockly) is unfriendly, and Qt itself still has a large number of bugs. Consider adopting it in the future .NET technology substitution.

C++/Qt development is too time-consuming so may use .NET/WPF or .NET/MAUI in the future development.



## License

qvs is licensed under the [MIT](https://github.com/emako/qvs/blob/master/LICENSE) License.

