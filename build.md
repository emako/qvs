# Building Equipments

- Qt5
- FFmpeg (Header code included)

- OpenCV (Header code included)

- [QtAV](https://github.com/emako/QtAV)  (Header code included)
- [Log4Qt](https://github.com/emako/Log4Qt) (Source code included)

- Blockly (Source code included)

# Running Equipments

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

# Building Manual

**Prepare your Qt5 environments.**

If something goes wrong, the  `MSVC2017x64` and `Qt5.12.0` is recommended.

> VS2017: https://my.visualstudio.com/Downloads?q=visual%20studio%202017&wt.mc_id=o~msft~vscom~older-downloads

> Qt5.12.0: https://download.qt.io/archive/qt/5.12/5.12.0/

- ## *Building QtAV*

> QtAV forked src url: https://github.com/emako/QtAV

Copy the ffmpeg `*.lib` and `*.h` to your Qt installation path like following.

```bash
# Copy to include folder
D:\Qt\5.12.12\msvc2017_64\include>tree
├─libavcodec
├─libavdevice
├─libavfilter
├─libavformat
├─libavutil
├─libpostproc
├─libswresample
└─libswscale
# Copy to lib folder
D:\Qt\5.12.12\msvc2017_64\lib>tree
├─avcodec.lib
├─avdevice.lib
├─avfilter.lib
├─avformat.lib
├─avutil.lib
├─postproc.lib
├─swresample.lib
└─swscale.lib
# Tips: Different ffmpeg versions may have different file names.
```

Run QtCreator and `Ctrl+R` for building.

Copy your builded file to `qvs/qtav/dll` and `qvs/qtav/lib`.

Tips: Debug building output like `QtAVd1.dll`, `d` is included.

- ## ~~*Building Wobbly*  `Optional`~~ `Deprecated`

> ~~Forked url: https://github.com/emako/Wobbly~~
>
> ~~Original url: https://github.com/dubhater/Wobbly~~

~~Requires [FieldHint](https://github.com/dubhater/vapoursynth-fieldhint/releases) v3 or newer.~~

~~Copy the latest vapoutsynth sdk files like following.~~

>~~\# Got from https://github.com/vapoursynth/vapoursynth/releases~~
>
>~~\# Portable package like VapourSynth32-Portable-R57.7z~~
>~~1. include~~
>~~2. msvc_project -> x64 -> Release~~

~~Copy the python sdk files.~~

- ## *Building D2VWitch*

Some error record following.

1. RegCloseKey referenced

> GUIWindow.obj:-1: error: LNK2019: unresolved external symbol __imp_RegCloseKey referenced in function "private: void __cdecl GUIWindow::initialiseVapourSynth(void)" (?initialiseVapourSynth@GUIWindow@@AEAAXXZ)

```
#pragma comment(lib, "Advapi32.lib")
```

2.  'out_of_range': is not a member of 'std'

> D:\D2VWitch\src\D2V.cpp:950: error: C2039: 'out_of_range': is not a member of 'std'
> C:\Program Files\Microsoft Visual Studio\2022\Professional\VC\Tools\MSVC\14.30.30705\include\unordered_map(24): note: see declaration of 'std'

```c++
#include <stdexcept>
```

3. windeployqt

> windeployqt --no-translations D:\D2VWitch\src\build\debug-64bit-msvc\d2vwitch-debug-64bit-msvc.exe
> 'windeployqt' is not an internal or external command, nor is it a runnable program or batch file.

```bash
# Add environment variable and Restart qtcreator
D:\Qt\5.12.12\msvc2017\bin
```

 - ##  **Building qvs**

 - Install Qt5

- Install `binarycreator`

Use `binarycreator` for building exe installer.

> Qt Installer Framework Manual
>
> https://doc.qt.io/qtinstallerframework/ifw-tools.html

> Qt Installer Framework Download
>
> http://download.qt.io/official_releases/qt-installer-framework/

Install `QtInstallerFramework-windows-x86-4.2.0.exe` and set the env var to installed path.

Such as `D:\Qt\QtIFW-4.2.0\bin`.

Confirm the command `binarycreator` is vaild.

- Prepare bin files

The `python/tools/*.bat` are good way for preparing those bin files.

Refer to [python/tools/README.md](python/tools/README.md).

- Build exe installer

`binarycreator.exe`, `7z.exe` are requested.

Copy `.\qvs\*` to `.\packages\noumenon\data\` firstly, and then run following.

```bash
setup\app_package.bat
setup\app_installer.bat
```

Refer to [setup/README.md](setup/README.md), [setup/app_installer.bat](setup/app_installer.bat), [setup/app_package.bat](setup/app_package.bat).

