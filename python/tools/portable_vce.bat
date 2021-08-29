@rem https://github.com/rigaya/VCEEnc/releases
@rem copy VCEEncC_6.14_Win32.7z and VCEEncC_6.14_x64.7z to here firstly.

rd /s /q .\vce32

rem extract VCEEncC 32bit 7zip pkg
mkdir vce32
copy VCEEncC*32*.7z vce32
cd vce32
7z x VCEEncC*32*.7z
del /s VCEEncC*32*.7z

cd ..
mkdir qvs\tools\VCEEncC\x86
xcopy /y vce32\* qvs\tools\VCEEncC\x86
rd /s /q .\vce32

rem extract VCEEncC 64bit 7zip pkg
mkdir vce64
copy VCEEncC*64*.7z vce64
cd vce64
7z x VCEEncC*64*.7z
del /s VCEEncC*64*.7z

cd ..
mkdir qvs\tools\VCEEncC\x64
xcopy /y vce64\* qvs\tools\VCEEncC\x64
rd /s /q .\vce64

pause
