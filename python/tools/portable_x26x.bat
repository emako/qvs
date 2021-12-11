@rem https://github.com/lordmulder/Simple-x264-Launcher/releases
@rem copy x264_launcher.2021-05-29.zip to here firstly.

rd /s /q .\x26x

rem extract x264/x265 Zip pkg
mkdir x26x
copy x264_launcher*.zip x26x
cd x26x
7z x x264_launcher*.zip
del /s x264_launcher*.zip

cd ..
mkdir qvs
mkdir qvs/tools

copy x26x\toolset\x64\x264_x64.exe .\qvs\tools
copy x26x\toolset\x64\x265_x64.exe .\qvs\tools
copy x26x\toolset\x64\avs2yuv_x64.exe .\qvs\tools

copy x26x\toolset\x86\x264_x86.exe .\qvs\tools
copy x26x\toolset\x86\x265_x86.exe .\qvs\tools
copy x26x\toolset\x86\avs2yuv_x86.exe .\qvs\tools

rd /s /q .\x26x

pause
