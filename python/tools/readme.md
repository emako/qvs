Usage of portable_*.bat
---
To make qvs portable pacakge.  
Copy the pacakges to here and auto extract it for portable qvs.
  
Usage of mediainfo_list.py
---
Copy the MediaInfo_DLL_21.03_Windows_x64_WithoutInstaller\Developers\List_Of_Parameters to here and run script, and then 'mediainfo_list.cpp' and 'mediainfo_list.h' will be created.
Mediainfo can downloaded from https://mediaarea.net/en/MediaInfo/Download/Windows.
At last, replace them to 'qvs\mediainfo\'.

Usage of mediainfo_enum.py
---
Download the 'File__Analyse_Automatic.h' from 'https://raw.githubusercontent.com/MediaArea/MediaInfoLib/master/Source/MediaInfo/File__Analyse_Automatic.h' and rename it to 'mediainfo_enum.h.tmp', and run this script. Then 'mediainfo_enum.h.tmp' will be repleaced to 'mediainfo_enum.h'.
If raw DNS can't be read, check it out from 'https://github.com/MediaArea/MediaInfoLib/blob/master/Source/MediaInfo/File__Analyse_Automatic.h'.
At last, replace them to 'qvs\mediainfo\'.
