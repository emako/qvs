import os
import re
import time
import platform

#-------------------------------------------------
#
# This script is used to generate define files for Qt.
# The csv files are from the List_Of_Parameters folder in Mediainfo.
#
#-------------------------------------------------
input = 'General.csv', 'Video.csv', 'Audio.csv', 'Text.csv', 'Other.csv', 'Image.csv', 'Menu.csv', 'Generic.csv'
output = 'mediainfo_define.h'
output_header = 'mediainfo_list.h'
output_source = 'mediainfo_list.cpp'
datas = []
pairs_general = []
pairs_video = []
pairs_audio = []
pairs_text = []
pairs_other = []
pairs_image = []
pairs_menu = []
externs = []

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
			tag_qt = 'MI_QT_{s0}_{s1}'.format(s0=basename(filename), s1=identify(line))
			tag_mi = 'MI_{s0}_{s1}'.format(s0=basename(filename), s1=identify(line))
			line = '#define {tag} QObject::tr("{s2}")'.format(tag=tag_qt, s2=line)
			datas.append(line)
			if filename != 'Generic.csv':
				pair = '{{ {tag_mi}, {{ {tag_qt}, {fully} }} }}'.format(tag_mi=tag_mi, tag_qt=tag_qt, fully='false')
				if filename == 'General.csv':
					pairs_general.append(pair)
				elif filename == 'Video.csv':
					pairs_video.append(pair)
				elif filename == 'Audio.csv':
					pairs_audio.append(pair)
				elif filename == 'Text.csv':
					pairs_text.append(pair)
				elif filename == 'Other.csv':
					pairs_other.append(pair)
				elif filename == 'Image.csv':
					pairs_image.append(pair)
				elif filename == 'Menu.csv':
					pairs_menu.append(pair)
					
			print(line)
	datas.append('')

def pair_define(pairs, name):
	name = name.lower().split('.')[0]
	extern = 'extern QList<QPair<MediaInfoDLL::String, QPair<QString, bool>>> g_mediainfo_list_{name};'.format(name=name)
	externs.append(extern)
	define = '///@brief Kinds of Stream: ' + name + '\n'
	define += '///{extern}\n'.format(extern=extern)
	define += '///\n'
	define += 'QList<QPair<MediaInfoDLL::String, QPair<QString, bool>>> g_mediainfo_list_{name} = {{\n'.format(name=name)
	for pair in pairs:
		define += '\t' + pair + ',\n'
	define += '};\n\n'
	return define
	
def get_comment_header():
	line = ''
	line += '//--------------------------------------------------------------------\n'
	line += '//\n'
	line += '// Header File created by Python{ver} {time}\n'.format(ver=str(platform.python_version()), time=time.strftime("%Y-%m-%dT%H:%M:%S", time.gmtime()))
	line += '// For MediaInfo v18.08 or greater version.\n'
	line += '// The macro definition is derived from the CSV files in Developers/List_Of_Parameters.\n'
	line += '//\n'
	line += '//--------------------------------------------------------------------\n'
	return line
	
def get_comment_source():
	line = ''
	line += '//--------------------------------------------------------------------\n'
	line += '//\n'
	line += '// Source File created by Python{ver} {time}\n'.format(ver=str(platform.python_version()), time=time.strftime("%Y-%m-%dT%H:%M:%S", time.gmtime()))
	line += '// For MediaInfo v18.08 or greater version.\n'
	line += '// The macro definition is derived from the CSV files in Developers/List_Of_Parameters.\n'
	line += '// More: https://github.com/MediaArea/MediaInfoLib/blob/master/Source/MediaInfo/File__Analyse_Automatic.h\n'
	line += '//\n'
	line += '//--------------------------------------------------------------------\n'
	return line
	
def pair_list():
	externs.append('extern QList<QPair<QString, QList<QPair<MediaInfoDLL::String, QPair<QString, bool>>>>> g_mediainfo_lists;')
	line = ''
	line += 'QList<QPair<QString, QList<QPair<MediaInfoDLL::String, QPair<QString, bool>>>>> g_mediainfo_lists = {\n'
	line += '\t{ "General", g_mediainfo_list_general },  // Stream_General\n'
	line += '\t{ "Video",   g_mediainfo_list_video   },  // Stream_Video\n'
	line += '\t{ "Audio",   g_mediainfo_list_audio   },  // Stream_Audio\n'
	line += '\t{ "Text",    g_mediainfo_list_text    },  // Stream_Text\n'
	line += '\t{ "Other",   g_mediainfo_list_other   },  // Stream_Other\n'
	line += '\t{ "Image",   g_mediainfo_list_image   },  // Stream_Image\n'
	line += '\t{ "Menu",    g_mediainfo_list_menu    },  // Stream_Menu\n'
	line += '};\n'
	return line
	
def main():
	for filename in input:
		todo(filename)
	
	with open(output_source, 'w') as f:
		f.write(get_comment_source())
		f.write('\n')
		f.write('#include "{h}"\n'.format(h=output_header))
		f.write('\n')
		#'General.csv', 'Video.csv', 'Audio.csv', 'Text.csv', 'Other.csv', 'Image.csv', 'Menu.csv'
		f.write(pair_define(pairs_general, 'General'))
		f.write(pair_define(pairs_video, 'Video'))
		f.write(pair_define(pairs_audio, 'Audio'))
		f.write(pair_define(pairs_text, 'Text'))
		f.write(pair_define(pairs_other, 'Other'))
		f.write(pair_define(pairs_image, 'Image'))
		f.write(pair_define(pairs_menu, 'Menu'))
		f.write(pair_list())
	
	with open(output_header, 'w') as f:
		f.write('#ifndef MEDIAINFO_DEFINE_QT_H\n')
		f.write('#define MEDIAINFO_DEFINE_QT_H\n')
		f.write(get_comment_header())
		f.write('\n')
		f.write('#include "{h}"\n'.format(h=output))
		f.write('#include <QObject>\n')
		f.write('\n')
		for extern in externs:
			f.write(extern+'\n')
		f.write('\n')
		for data in datas:
			f.write(data+'\n')
		f.write('#endif // MEDIAINFO_DEFINE_QT_H\n')
main()