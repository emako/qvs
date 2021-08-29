@rem https://www.fosshub.com/MKVToolNix.html
@rem copy mkvtoolnix-64-bit-60.0.0.7z to here firstly.

rd /s /q .\mkv64

rem extract mkv64 7zip pkg
mkdir mkv64
copy mkvtoolnix*.7z mkv64
cd mkv64
7z x mkvtoolnix*.7z
del /s mkvtoolnix*.7z

cd ..
mkdir qvs
mkdir qvs\tools

copy mkv64\mkvtoolnix\mkvextract.exe qvs\tools
copy mkv64\mkvtoolnix\mkvmerge.exe qvs\tools
rd /s /q .\mkv64

pause
