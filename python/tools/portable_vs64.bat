@rem https://hub.fastgit.org/vapoursynth/vapoursynth/releases
@rem copy VapourSynth64-Portable-R54.7z and VapourSynth32-Portable-R54.7z to here firstly.

rem extract vs64 7zip pkg
mkdir vs64
copy VapourSynth64-Portable-R*.7z vs64
cd vs64
7z x VapourSynth64-Portable-R*.7z
del /s VapourSynth64-Portable-R*.7z

rem make vs portable for qvs
mkdir tools
rename AVFS.exe avfs_x64.exe
move avfs_x64.exe tools
move pfm-*-vapoursynth-win.exe tools

mkdir Lib
mkdir Lib\site-packages
move vapoursynth.cp*-win_*.pyd Lib\site-packages

rd /s /q .\doc\
rd /s /q .\sdk\
del /s 7z.dll
del /s 7z.exe
del /s MANIFEST.in
del /s setup.py

cd ..

rem extract vs32 7zip pkg (for AVFSx86)
mkdir vs32
copy VapourSynth32-Portable-R*.7z vs32
cd vs32
7z x VapourSynth32-Portable-R*.7z
del /s VapourSynth32-Portable-R*.7z

rem make vs portable for qvs
mkdir tools
rename AVFS.exe avfs_x86.exe
move avfs_x86.exe ..\vs64\tools

cd ..

rd /s /q vs32
mkdir qvs
xcopy /s /e /y .\vs64\* .\qvs\
rd /s /q .\vs64

pause
