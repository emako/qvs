@rem https://github.com/rigaya/NVEnc/releases
@rem copy NVEncC_5.37_Win32.7z and NVEncC_5.37_x64.7z to here firstly.

rd /s /q .\nv32

rem extract NVEncC 32bit 7zip pkg
mkdir nv32
copy NVEncC*32*.7z nv32
cd nv32
7z x NVEncC*32*.7z
del /s NVEncC*32*.7z

cd ..
mkdir qvs\tools\NVEncC\x86
xcopy /y nv32\* qvs\tools\NVEncC\x86
rd /s /q .\nv32

rem extract NVEncC 64bit 7zip pkg
mkdir nv64
copy NVEncC*64*.7z nv64
cd nv64
7z x NVEncC*64*.7z
del /s NVEncC*64*.7z

cd ..
mkdir qvs\tools\NVEncC\x64
xcopy /y nv64\* qvs\tools\NVEncC\x64
rd /s /q .\nv64

pause
