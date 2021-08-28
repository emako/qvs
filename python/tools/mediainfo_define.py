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

input = 'General.csv', 'Video.csv', 'Audio.csv', 'Text.csv', 'Other.csv', 'Image.csv', 'Menu.csv', 'Generic.csv'
output = 'mediainfo_define.h'
datas = []
options = \
	'acquisitiondataoutputmode', \
	'all', \
	'blockmethod', \
	'blockmethod_get', \
	'carriagereturnreplace', \
	'carriagereturnreplace_get', \
	'charset_config', \
	'charset_output', \
	'columnseparator', \
	'columnseparator_get', \
	'complete', \
	'complete_get', \
	'container', \
	'cover_data', \
	'cover_data_get', \
	'create_dummy', \
	'custommapping', \
	'decimalpoint', \
	'decimalpoint_get', \
	'demux', \
	'demux_get', \
	'details', \
	'details_get', \
	'detailsformat', \
	'detailsformat_get', \
	'detailslevel', \
	'detailslevel_get', \
	'detailsmodificator', \
	'detailsmodificator_get', \
	'elementary', \
	'event_callbackfunction', \
	'externalmetadata', \
	'externalmetadataconfig', \
	'file_details_clear', \
	'file_seek', \
	'format_profile_split', \
	'format_profile_split_get', \
	'formatdetection_maximumoffset', \
	'formatdetection_maximumoffset_get', \
	'frame', \
	'hideparameter', \
	'https', \
	'https_get', \
	'info_canhandleurls', \
	'info_capacities', \
	'info_codecs', \
	'info_outputformats', \
	'info_outputformats_csv', \
	'info_outputformats_json', \
	'info_parameters', \
	'info_parameters_csv', \
	'info_url', \
	'info_version', \
	'inform', \
	'inform_compress', \
	'inform_compress_get', \
	'inform_get', \
	'inform_replace', \
	'inform_replace_get', \
	'initdatanotrepeated_giveup', \
	'initdatanotrepeated_giveup_get', \
	'initdatanotrepeated_occurences', \
	'initdatanotrepeated_occurences_get', \
	'input_compressed', \
	'input_compressed_get', \
	'internet', \
	'internet_get', \
	'language', \
	'language_get', \
	'language_update', \
	'legacy', \
	'legacy_get', \
	'legacystreamdisplay', \
	'legacystreamdisplay_get', \
	'lineseparator', \
	'lineseparator_get', \
	'maxml_fields', \
	'maxml_streamkinds', \
	'mpegts_forcestreamdisplay', \
	'mpegts_forcestreamdisplay_get', \
	'mpegts_forcetextstreamdisplay', \
	'mpegts_forcetextstreamdisplay_get', \
	'mpegts_maximumoffset', \
	'mpegts_maximumoffset_get', \
	'mpegts_maximumscanduration', \
	'mpegts_maximumscanduration_get', \
	'mpegts_vbrdetection_delta', \
	'mpegts_vbrdetection_delta_get', \
	'mpegts_vbrdetection_giveup', \
	'mpegts_vbrdetection_giveup_get', \
	'mpegts_vbrdetection_occurences', \
	'mpegts_vbrdetection_occurences_get', \
	'multiplevalues', \
	'multiplevalues_get', \
	'no-https', \
	'output', \
	'output_get', \
	'parseonlyknownextensions', \
	'parseonlyknownextensions_get', \
	'parseonlyknownextensions_getlist', \
	'parsespeed', \
	'parsespeed_get', \
	'parseunknownextensions', \
	'parseunknownextensions_get', \
	'quote', \
	'quote_get', \
	'readbyhuman', \
	'readbyhuman_get', \
	'showfiles_set', \
	'showparameter', \
	'skipbinarydata', \
	'skipbinarydata_get', \
	'ssh_ignoresecurity', \
	'ssh_ignoresecurity', \
	'ssh_knownhostsfilename', \
	'ssh_privatekeyfilename', \
	'ssh_publickeyfilename', \
	'ssl_certificateauthorityfilename', \
	'ssl_certificateauthoritypath', \
	'ssl_certificatefilename', \
	'ssl_certificateFormat', \
	'ssl_certificaterevocationlistfilename', \
	'ssl_ignoresecurity', \
	'ssl_privatekeyfilename', \
	'ssl_privatekeyformat', \
	'streammax', \
	'streammax_get', \
	'tagseparator', \
	'tagseparator_get', \
	'thousandspoint', \
	'thousandspoint_get', \
	'thread', \
	'trace_format', \
	'trace_format_get', \
	'trace_level', \
	'trace_level_get', \
	'trace_timesection_onlyfirstoccurrence', \
	'trace_timesection_onlyfirstoccurrence_get', \
	'trytofix', \
	'urlencode', \
	'variablegopdetection_giveup', \
	'variablegopdetection_giveup_get', \
	'variablegopdetection_occurences', \
	'variablegopdetection_occurences_get', \
	'verbosity', \
	'verbosity_get', \
	'version', \
	'version_get'
values = \
	'Tree', \
	'Text', \
	'CSV', \
	'HTML', \
	'XML', \
	'MAXML', \
	'JSON', \
	'EBUCore_1.8_ps', \
	'EBUCore_1.8_sp', \
	'EBUCore_1.8_ps_JSON', \
	'EBUCore_1.8_sp_JSON', \
	'EBUCore_1.6', \
	'FIMS_1.3', \
	'MPEG-7', \
	'PBCore_2.1', \
	'PBCore_2.0', \
	'PBCore_1.2', \
	'NISO_Z39.87'
rets = \
	'All', \
	'Frame', \
	'Container', \
	'Elementary', \
	'Option not known'

def add_flag():
	#String MediaInfo::Option (const String &Option, const String &Value)
	#String MediaInfo::Option_Static (const String &Option, const String &Value)
	#String MediaInfo_Internal::Option (const String &Option, const String &Value)
	#Ztring MediaInfo_Config::Option (const String &Option, const String &Value_Raw)
	datas.append('/// -> Option')
	for option in options:
		datas.append('#define MI_OPTION_{option_upper} __T("{option}")'.format(option_upper=option.upper().replace('-', '_'), option=option))
	datas.append('')
	datas.append('/// -> Value')
	datas.append('#define MI_VALUE_EMPTY __T("")')
	datas.append('#define MI_VALUE_TRUE __T("1")')
	datas.append('#define MI_VALUE_FALSE __T("0")')
	for value in values:
		datas.append('#define MI_VALUE_{value_upper} __T("{value}")'.format(value_upper=value.upper().replace('-', '_').replace('.', '_'), value=value))
	datas.append('')
	datas.append('/// -> Return')
	for ret in rets:
		datas.append('#define MI_RETURN_{ret_upper} __T("{ret}")'.format(ret_upper=ret.upper().replace(' ', '_'), ret=ret))
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
		if os.path.exists('List_Of_Parameters'):
			filename = 'List_Of_Parameters/' + filename
		todo(filename)
	
	with open(output, 'w') as f:
		f.write('#ifndef MEDIAINFO_DEFINE_H\n')
		f.write('#define MEDIAINFO_DEFINE_H\n')
		f.write('//--------------------------------------------------------------------\n')
		f.write('//\n')
		f.write('// Header File created by Python{ver} {time}\n'.format(ver=str(platform.python_version()), time=time.strftime("%Y-%m-%dT%H:%M:%S", time.gmtime())))
		f.write('// For MediaInfo v18.08 or greater version.\n')
		f.write('// The macro definition is derived from the CSV files in Developers/List_Of_Parameters.\n')
		f.write('//\n')
		f.write('//--------------------------------------------------------------------\n')
		f.write('\n')
		f.write('#include "mediaInfo_dll.h"\n')
		f.write('\n')
		for data in datas:
			f.write(data+'\n')
		f.write('#endif // MEDIAINFO_DEFINE_H\n')
	
main()