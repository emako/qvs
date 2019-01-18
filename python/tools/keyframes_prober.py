import os
import sys

#-------------------------------------------------
#
# This script is used to prober and generate key frames file.
# And you can compare the key frames file with qvs keyframes generated file.
#
#-------------------------------------------------

src = u'example.mp4'
try:
	src = sys.argv[1]
except:
	pass

csv = src + '_src.csv'
txt = src + '_src.txt'

count = 0
keyFrameList = []

os.system('ffprobe -loglevel error -select_streams v -show_frames -show_entries frame=key_frame,pict_type -of csv "{src}" > "{csv}"'.format(src=src, csv=csv))  

with open(csv, 'r') as fin:
	lines = fin.readlines()
	for line in lines:
		if (line == '') or (not line.startswith('frame')):
			continue
		items = line.split(',')
		pitFormat = str(items[2])
		if pitFormat.startswith('I'):
			keyFrameList.append(count)
		count += 1
	
with open(txt, 'w+') as fout:
	for keyFrameItem in keyFrameList:
		fout.write(str(keyFrameItem) + '\n')

