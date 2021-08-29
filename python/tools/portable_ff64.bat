@rem https://www.gyan.dev/ffmpeg/builds/
@rem copy ffmpeg-4.4-full_build-shared.7z to here firstly.

rd /s /q .\ff64

rem extract ffmpeg 7zip pkg
mkdir ff64
copy ffmpeg*shared*.7z ff64
cd ff64
7z x ffmpeg*shared*.7z
del /s ffmpeg*shared*.7z

rem TODO

pause
