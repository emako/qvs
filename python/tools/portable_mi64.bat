@rem copy MediaInfo_DLL_21.03_Windows_x64_WithoutInstaller.7z to here firstly.

rd /s /q .\List_Of_Parameters
rd /s /q .\mi64

rem extract mi64 7zip pkg
mkdir mi64
copy MediaInfo_DLL_*_Windows_x64_WithoutInstaller.7z mi64
cd mi64
7z x MediaInfo*.7z
del /s MediaInfo*.7z

cd ..
mkdir qvs
copy .\mi64\MediaInfo.dll qvs
mkdir List_Of_Parameters
copy .\mi64\Developers\List_Of_Parameters\* .\List_Of_Parameters\

rem may use python xxx.py when not work
mediainfo_define.py
mediainfo_enum.py
mediainfo_list.py

rd /s /q .\List_Of_Parameters

move mediainfo_define.h mi64
move mediainfo_enum.h mi64
move mediainfo_list.cpp mi64
move mediainfo_list.h mi64

copy /y .\mi64\* ..\..\mediainfo
rd /s /q .\mi64

pause
