# qvs

![](https://img.shields.io/badge/qvs-r16-green)
![](https://img.shields.io/github/license/emako/qvs?color=blue)
![](https://img.shields.io/github/stars/emako/qvs?color=blue)
![](https://img.shields.io/github/forks/emako/qvs?color=blue)

<img src="res/images/qvs.png" width = "200" height = "200" alt="" align=center />
A simple program for using VapourSynth/Avisynth Script previewed and encoded.



## Download

[![GitHub downloads](https://img.shields.io/github/downloads/emako/qvs/total?style=flat-square)](https://github.com/emako/qvs/releases)

[![GitHub downloads](https://img.shields.io/github/downloads/emako/qvs/latest/total?style=flat-square)](https://github.com/emako/qvs/releases)

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



## Building Equipments

- Qt5
- FFmpeg (Header code included)

- OpenCV (Header code included)

- [QtAV](https://github.com/emako/QtAV)  (Header code included)
- [Log4Qt](https://github.com/emako/Log4Qt) (Source code included)

- Blockly (Source code included)



## Running Equipments

- Qt5 (x64)

- x264/x265 (x86/x64)
- VapourSynth (x64)
- avfs (x86/x64)
- avs2yuv (x86/x64)
- [AVSMeter](https://github.com/emako/AVSMeter) (x86/x64)
- BonTsDemuxC (x86/x64)
- ffmpeg (x86/x64)
- mkvmerge/mkvextract (x64)
- pfm-192-vapoursynth-win (x86)
- yamdi (x86/x64)
- AviSynth (x86) (Optional)
- Aviutl (x86) (Optional)
- AvsPmod (x86) (Optional)
- Python3 (x64)

- VapourSynth Editor (x64)

- [Wobbly](https://github.com/emako/Wobbly) (x64) (Optional)

- [d2vwitch](https://github.com/emako/D2VWitch) (x64) (Optional)

- mp4box (x86)

- eac3to (x86)

- LAVFilters (x86/x64) (Optional)

- Lsmash (x64)

- NVEncC/QSVEncC/VCEEncC (x86/x64)

- VirtualDub2 (x64) (Optional)

- DGIndex (x86)

- DGIndexNV (x64)

  Tips: Not included but you can copy your `DGIndexNV.exe` to `qvs\tools\DGIndexNV\` for default using.

- Caption2Ass (x64)

- fdkaac (x86)

- flac (x86)

- lame (x86)

- neroAacEnc (x86)

- oggenc2 (x86)

- opusenc (x86)

- qaac (x86)

- refalac (x86)

- wavpack (x86)

See the [releases](https://github.com/emako/qvs/releases) binary package for more details.



## Building

qvs is developed based on Qt5.

See Building Equipments for more details.



## License

qvs is licensed under the [MIT](https://github.com/emako/qvs/blob/master/LICENSE) License.

