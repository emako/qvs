import mediainfodll3

'''*********************************************
MediaInfo functions:
	MediaInfo
	MediaInfoF
	Bitrate
	ColorSpace
	Menu
	MenuList
	ScanType
	ScanOrder
	Delay
*********************************************'''

##################################################################################################
### Function  : MediaInfo
### Author    : ema
### Version   : v0.3
### Release   : 2018.05.26
##################################################################################################
### +----------------+
### |  REQUIREMENTS  |
### +----------------+
###	-> MediaInfo.dll
###	-> mediainfodll3.pyc (or mediainfodll3.py)
##################################################################################################
def MediaInfo(inpath, isShow=False, isOut=False, outpath=None, full=False):
	if full is True:
		return MediaInfoF(inpath=inpath, isShow=isShow, isOut=isOut, outpath=outpath)
	MI = mediainfodll3.MediaInfo()
	MI.Option_Static('Complete', '0')
	MI.Open(inpath)
	inform = MI.Inform()
	MI.Close()
	if isShow:
		print(inform)
	if isOut:
		if outpath is None:
			outpath = '{path}.txt'.format(path=inpath)
		print('MediaInfo was saved in {path}'.format(path=outpath))
		with open(outpath, 'w') as f:
			f.write(inform)
	return inform

def MediaInfoF(inpath, isShow=False, isOut=False, outpath=None):
	MI = mediainfodll3.MediaInfo()
	MI.Option_Static('Complete', '1')
	MI.Open(inpath)
	inform = MI.Inform()
	MI.Close()
	if isShow:
		print(inform)
	if isOut:
		if outpath is None:
			outpath = '{path}.txt'.format(path=inpath)
		print('MediaInfo was saved in {path}'.format(path=outpath))
		with open(outpath, 'w') as f:
			f.write(inform)
	return inform

def Bitrate(path):
	MI = mediainfodll3.MediaInfo()
	MI.Open(path)
	return MI.Get(Stream.Video, 0, 'BitRate')

def ColorSpace(path):
	MI = mediainfodll3.MediaInfo()
	MI.Open(path)
	return MI.Get(Stream.Video, 0, 'ColorSpace')+MI.Get(Stream.Video, 0, 'ChromaSubsampling').replace(':','')+'P'+MI.Get(Stream.Video, 0, 'BitDepth')

def Menu(path):
	MI = mediainfodll3.MediaInfo()
	MI.Open(path)
	return MI.Inform().split('\r\nMenu\r\n')[-1]

def MenuList(path):
	MI = mediainfodll3.MediaInfo()
	MI.Open(path)
	menu_dict = {}
	menu_line_list = MI.Inform().split('\r\nMenu\r\n')[-1].split('\r\n')
	for menu_line in menu_line_list:
		line_list = menu_line[0:12], menu_line.split(':')[-1]
		if line_list[0].find(':') > 0:
			menu_dict[line_list[0]] = line_list[1]
	for key in menu_dict:
		print(key, '=>', menu_dict[key])
	return menu_dict

def ScanType(path, initial=False):
	MI = mediainfodll3.MediaInfo()
	MI.Open(path)
	scanType = MI.Get(Stream.Video, 0, 'ScanType')
	if initial:
		scanType = scanType[0].lower()
	return scanType

def ScanOrder(path):
	MI = mediainfodll3.MediaInfo()
	MI.Open(path)
	return MI.Get(Stream.Video, 0, 'ScanOrder')

def Delay(path):
	MI = mediainfodll3.MediaInfo()
	MI.Open(path)
	return MI.Inform().split('\r\nDelay relative to video')[1].split('\r\n')[-1].split(': ')[1]
