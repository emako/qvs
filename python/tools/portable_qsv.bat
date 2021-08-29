@rem https://github.com/rigaya/QSVEnc/releases
@rem copy QSVEncC_5.06_Win32.7z and QSVEncC_5.06_x64.7z to here firstly.

rd /s /q .\qsv32

rem extract QSVEncC 32bit 7zip pkg
mkdir qsv32
copy QSVEncC*32*.7z qsv32
cd qsv32
7z x QSVEncC*32*.7z
del /s QSVEncC*32*.7z

cd ..
mkdir qvs\tools\QSVEncC\x86
xcopy /y qsv32\* qvs\tools\QSVEncC\x86
rd /s /q .\qsv32

rem extract QSVEncC 64bit 7zip pkg
mkdir qsv64
copy QSVEncC*64*.7z qsv64
cd qsv64
7z x QSVEncC*64*.7z
del /s QSVEncC*64*.7z

cd ..
mkdir qvs\tools\QSVEncC\x64
xcopy /y qsv64\* qvs\tools\QSVEncC\x64
rd /s /q .\qsv64

pause
