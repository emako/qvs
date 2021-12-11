# Python Tools Script

Usage of `portable_*.bat`
---

To make qvs portable pacakge.
Copy the pacakges to here and auto extract it for portable qvs.

| Batch file          | Portable for              | Comment something                                            |
| ------------------- | ------------------------- | ------------------------------------------------------------ |
| portable_ff64.bat   | FFmpeg `64bit`            | ffmpeg-4.4-full_build-shared.7z<br />https://www.gyan.dev/ffmpeg/builds/ |
| portable_gpac64.bat | GPAC `64bit`              | gpac-1.1.0-DEV-latest-master-x64.exe<br />https://gpac.wp.imt.fr/downloads/gpac-nightly-builds/ |
| portable_mi64.bat   | MediaInfo `64bit`         | MediaInfo_DLL_21.03_Windows_x64_WithoutInstaller.7z<br />https://mediaarea.net/en/MediaInfo/Download/Windows |
| portable_mkv64.bat  | mkvtoolnix `64bit`        | mkvtoolnix-64-bit-60.0.0.7z<br />https://mkvtoolnix.download/downloads.html<br />https://www.fosshub.com/MKVToolNix.html |
| portable_nv.bat     | NVEncC `32bit` `64bit`    | NVEncC_5.37_Win32.7z<br />NVEncC_5.37_x64.7z<br />https://github.com/rigaya/NVEnc/releases |
| portable_py64.bat   | Python `64bit`            | python-3.9.6-embed-amd64.zip<br />https://www.python.org/downloads/ |
| portable_qacc32.bat | qaac `32bit`              | qaac_2.72.zip<br />https://github.com/nu774/qaac/releases    |
| portable_qsv.bat    | QSVEncC `32bit` `64bit`   | QSVEncC_5.06_Win32.7z<br />QSVEncC_5.06_x64.7z<br />https://github.com/rigaya/QSVEnc/releases |
| portable_vce.bat    | VCEEncC `32bit` `64bit`   | VCEEncC_6.14_Win32.7z<br />VCEEncC_6.14_x64.7z<br />https://github.com/rigaya/VCEEnc/releases |
| portable_vd64.bat   | VirtualDub2 `64bit`       | VirtualDub2_44282.zip<br />https://sourceforge.net/projects/vdfiltermod/files/ |
| portable_vs64.bat   | VapourSynth `64bit`       | And something file from 32bit.<br />VapourSynth32-Portable-R57.7z<br />VapourSynth64-Portable-R57.7z<br />https://github.com/vapoursynth/vapoursynth/releases |
| portable_x26x.bat   | x264/x265 `32bit` `64bit` | x264_launcher.2021-05-29.zip<br />https://github.com/lordmulder/Simple-x264-Launcher/releases |

### Other portable components

> LAVFilters from https://github.com/Nevcairiel/LAVFilters/releases
>
> Qt from https://download.qt.io/archive/qt/



Usage of `mediainfo_list.py`
---
Copy the MediaInfo_DLL_21.03_Windows_x64_WithoutInstaller\Developers\List_Of_Parameters to here and run script, and then 'mediainfo_list.cpp' and 'mediainfo_list.h' will be created.
Mediainfo can downloaded from https://mediaarea.net/en/MediaInfo/Download/Windows.
At last, replace them to 'qvs\mediainfo\'.



Usage of `mediainfo_enum.py`
---
Download the `File__Analyse_Automatic.h` from 'https://raw.githubusercontent.com/MediaArea/MediaInfoLib/master/Source/MediaInfo/File__Analyse_Automatic.h' and rename it to `mediainfo_enum.h.tmp`, and run this script. Then `mediainfo_enum.h.tmp`  will be repleaced to `mediainfo_enum.h`.
If raw DNS can't be read, check it out from 'https://github.com/MediaArea/MediaInfoLib/blob/master/Source/MediaInfo/File__Analyse_Automatic.h'.
At last, replace them to 'qvs\mediainfo\'.

