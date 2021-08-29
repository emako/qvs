@rem https://sourceforge.net/projects/vdfiltermod/files/VirtualDub%20pack/
@rem copy VirtualDub2_44282.zip to here firstly.

rd /s /q .\vd64

rem extract VirtualDub2 x64 Zip pkg
mkdir vd64
copy VirtualDub2*.zip vd64
cd vd64
7z x VirtualDub2*.zip
del /s VirtualDub2*.zip

cd ..
mkdir qvs\tools\VirtualDub2
mkdir qvs\tools\VirtualDub2\plugins64

del vd64\plugins64\cch_input.ini
xcopy /y vd64\plugins64\* qvs\tools\VirtualDub2\plugins64
copy vd64\VirtualDub64.exe qvs\tools\VirtualDub2

rd /s /q .\vd64
pause
