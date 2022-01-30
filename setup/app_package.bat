del .\qvs\temp*.vpy
del .\qvs\logging.html
del .\qvs\debug.log
del .\qvs\tools\ScriptBlockly\*.js
del .\qvs\tools\ScriptBlockly\*.js.map
rd /s /q .\qvs\tools\ScriptBlockly\blocks\
rd /s /q .\qvs\tools\ScriptBlockly\core\
rd /s /q .\qvs\tools\ScriptBlockly\generators\
rd /s /q .\qvs\tools\ScriptBlockly\media\
rd /s /q .\qvs\tools\ScriptBlockly\msg\
rd /s /q .\qvs\tools\ScriptBlockly\qvs\
@echo package started with 7z at %date:~,4%.%date:~5,2%.%date:~8,2% %time:~,2%:%time:~3,2%:%time:~6,2%.
7z a qvs.7z .\qvs\* -t7z -mx=9 -r -y
@pause
