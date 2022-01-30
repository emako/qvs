copy qvs.7z packages\noumenon\data\
move packages\noumenon\data\qvs.7z packages\noumenon\data\data.7z 
binarycreator --offline-only -c config.xml -p packages qvs
@pause
