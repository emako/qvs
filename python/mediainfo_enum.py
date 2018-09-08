import os
import requests

#-------------------------------------------------
#
# This script is used to generate header files for C/C++.
#
#-------------------------------------------------
enum_list_url = 'https://raw.githubusercontent.com/MediaArea/MediaInfoLib/master/Source/MediaInfo/File__Analyse_Automatic.h'
output = 'mediainfo_enum.h'
output_tmp = output + '.tmp'
datas = []

def download():
	print('requests: {url}'.format(url=enum_list_url))
	r = requests.get(enum_list_url)
	with open(output_tmp, 'wb') as f:
		f.write(r.content)
		
	with open(output_tmp) as f:
		for line in f.readlines():
			line = line.replace('MediaInfo_File__Analyze_AutomaticH', 'MEDIAINFO_ENUM_H')
			datas.append(line)
			print(line.replace('\n', ''))
	
	with open(output, 'w') as f:
		for data in datas:
			f.write(data)
			
	os.remove(output_tmp)

	print('{filename} download completed!'.format(filename=output))

download()