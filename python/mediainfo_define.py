import os
import re
import time
import platform

#-------------------------------------------------
#
# This script is used to generate define files for C++.
# The csv files are from the List_Of_Parameters folder in Mediainfo.
#
#-------------------------------------------------

input = 'General.csv', 'Video.csv', 'Audio.csv', 'Generic.csv', 'Image.csv', 'Menu.csv', 'Other.csv', 'Text.csv'
output = 'mediainfo_define.h'
datas = []

def add_flag():
	datas.append('/// -> Option')
	datas.append('#define MI_OPTION_COMPLETE __T("Complete")')
	datas.append('#define MI_OPTION_TRUE __T("1")')
	datas.append('#define MI_OPTION_FALSE __T("0")')
	datas.append('')

def filename_split(filename):
    path, tempfilename = os.path.split(filename);
    shotname, ext = os.path.splitext(tempfilename);
    return path, shotname, ext

def basename(filename):
	return filename_split(filename)[1].upper()

def identify(line):
	return line.upper().replace('/', '_').replace('-', '_').replace('*', '_X_').replace('(', '').replace(')', '')

def todo(filename):
	datas.append('/// -> '+filename)
	with open(filename) as f:
		for line in f.readlines():
			line = re.sub(r';[\s\S]*?$', '', line)
			line = line.replace('\n', '')
			line = '#define MI_{s0}_{s1} __T("{s2}")'.format(s0=basename(filename), s1=identify(line), s2=line)
			datas.append(line)
			print(line)
	datas.append('')

def main():
	add_flag()
	
	for filename in input:
		todo(filename)
	
	with open(output, 'w') as f:
		f.write('#ifndef MEDIAINFO_DEFINE_H\n')
		f.write('#define MEDIAINFO_DEFINE_H\n')
		f.write('//--------------------------------------------------------------------'+'\n')
		f.write('//\n')
		f.write('// Header File created by Python{ver} {time}\n'.format(ver=str(platform.python_version()), time=time.strftime("%Y-%m-%dT%H:%M:%S", time.gmtime())))
		f.write('// For MediaInfo v18.08 or greater version.\n')
		f.write('// The macro definition is derived from the CSV files in Developers/List_Of_Parameters.\n')
		f.write('//\n')
		f.write('//--------------------------------------------------------------------'+'\n')
		f.write('\n')
		f.write('#include "mediaInfo_dll.h"\n')
		f.write('\n')
		for data in datas:
			f.write(data+'\n')
		f.write('#endif // MEDIAINFO_DEFINE_H\n')
	
main()