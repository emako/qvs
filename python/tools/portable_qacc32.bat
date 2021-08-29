@rem https://www.videohelp.com/software/qaac
@rem copy qaac_2.72.zip to here firstly.

rd /s /q .\qaac32

rem extract VirtualDub2 x64 Zip pkg
mkdir qaac32
copy qaac*.zip qaac32
cd qaac32
7z x qaac*.zip
del /s qaac*.zip

cd ..
mkdir qvs\tools\AudioEnc
cd qaac32
cd qaac*
copy /y .\x86\* ..\..\qvs\tools\AudioEnc\
cd ..\..\

rd /s /q .\qaac32

@rem TODO: QTfiles

pause
