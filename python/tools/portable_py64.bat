@rem https://www.python.org/downloads/
@rem copy python-3.9.6-embed-amd64.zip to here firstly.
rd /s /q .\py64

rem extract py-amd64 Zip pkg
mkdir py64
copy python-*-embed-*.zip py64
cd py64
7z x python-*-embed-*.zip
del /s python-*-embed-*.zip

rem make py-amd64 portable for qvs

del /s python.cat
del /s LICENSE.txt

mkdir Lib
mkdir Lib\libs
mkdir Lib\site-packages

move python*.zip Lib
move *.pyd Lib\libs

find "python" python*._pth > _pth
for /f "delims=" %%i in (_pth) do @(set /p=%%i<nul) >_pth
set /p pth=<_pth
del /s _pth
set "pth=%pth:~0,8%"
@echo %pth%
del /s %pth%._pth
> %pth%._pth echo .
>> %pth%._pth echo Lib
>> %pth%._pth echo Lib\%pth%.zip
>> %pth%._pth echo Lib\libs
>> %pth%._pth echo Lib\site-packages
>> %pth%._pth echo.
>> %pth%._pth echo # Uncomment to run site.main() automatically
>> %pth%._pth echo #import site

cd ..
mkdir qvs
xcopy /s /e /y .\py64\* .\qvs\
rd /s /q .\py64

pause
