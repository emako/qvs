import os
import re
import time

#-------------------------------------------------
#
# This script is used to generate define files for C++.
# The csv files are from the List_Of_Parameters folder in Mediainfo.
#
#-------------------------------------------------

file_names = 'Audio.csv', 'General.csv', 'Generic.csv', 'Image.csv', 'Menu.csv', 'Other.csv', 'Text.csv', 'Video.csv'
data = []

def filename_split(filename):
    path, tempfilename = os.path.split(filename);
    shotname, ext = os.path.splitext(tempfilename);
    return path, shotname, ext
	
def todo(file_name):
	datas.append('/// -> '+file_name)
	with open(file_name) as f:
		for line in f.readlines():
			line = re.sub(r';[\s\S]*?$', '', line)
			line = line.replace('\n', '')
			line = '#define MI_{s0}_{s1} __T("{s2}")'.format(s0=filename_split(file_name)[1].upper(), s1=line.upper().replace('/', '_').replace('-', '_').replace('*', '_X_').replace('(', '').replace(')', ''), s2=line)
			print(line)
			datas.append(line)
	datas.append('')

for file_name in file_names:
	todo(file_name)
	
with open('mediainfo_define.h', "w") as f:
	f.write('//-------------------------------------------------'+'\n')
	f.write('//'+'\n')
	f.write('// '+'Header File created by Python '+time.strftime("%Y-%m-%dT%H:%M:%S", time.gmtime())+'\n')
	f.write('//'+'\n')
	f.write('//-------------------------------------------------'+'\n')
	f.write('#ifndef MEDIAINFO_DEFINE_H'+'\n')
	f.write('#define MEDIAINFO_DEFINE_H'+'\n')
	f.write('\n')
	f.write('#include "mediaInfo_dll.h"'+'\n')
	f.write('\n')
	for data in datas:
		f.write(data+'\n')
	f.write('#endif // MEDIAINFO_DEFINE_H'+'\n')