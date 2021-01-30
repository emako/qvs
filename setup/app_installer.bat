:Copy .\qvs\* to .\packages\noumenon\data\ firstly.
if not exist .\packages\noumenon\data\qvs.exe (
xcopy /y .\qvs\* .\packages\noumenon\data\
)
binarycreator --offline-only -c config.xml -p packages qvs
@pause
