import vapoursynth as vs
import havsfunc as haf
import mvsfunc as mvf
import muvsfunc as muvf
import nnedi3_resample
import nnedi3_resampleCL as nncl
import xvs
import sys
import os
import re
import math
import glob
import functools
import subprocess
import shutil
import configparser

"""*********************************************
Scripts functions:
	EraseAny*
	EraseDMM*
	LogoNR
	FillMargins
	SpeedGear
	Nnedi3aa
	Dissolve
	FadeIn
	FadeOut
	FadeIO
	TurnLeft
	TurnRight
	SelectEven
	SelectOdd
	SelectHalf
	StackVertical
	StackHorizontal
	Subtitle
	ChangeFPS
	AssumeFPS
	OverlayM
	Overlay
	Overlaymod
	GradualMerge
	Crop
	Diff
	TrimMul
************************************************
Source functions:
	ImageSourceMul
	FFImageSource
	LWLSource
	DirectShowSource
	MplsSource
	D2VSource
	DGSource
	DGSourceNV
	DGSourceIM
************************************************
Deinterlacing functions:
	Nnedi3
	Yadifmod
	QTGMC
	DGBob
************************************************
Inverse Telecine functions:
	VIVTC
	DGIVTC
************************************************
Resizing functions:
	GammaResize
	BoxResize
	BlinearResize
	BicubicResize
	LanczosResize
	Lanczos4Resize
	BlackmanResize
	BlackmanminlobeResize
	Spline16Resize
	Spline36Resize
	Spline64Resize
	SplineResize
	GaussResize
	SincResize
	Nnedi3Resize
************************************************
Denoise functions:
	DGDenoise
	SMDegrain
************************************************
Format Conversion functions:
	ConvertToYV24
	ConvertToYV16
	ConvertToYUY2
	ConvertToYV12
	ConvertToYV411
	ConvertToY8
	ConvertToRGB24
	ConvertToRGB48
	ConvertToRGBS
	ConvertToGrey
	ConvertToGray
	ConvertTo
	SwapUV
	UToY
	VToY
	Depth
************************************************
Configure functions:
	Main
	SetWorkingDir
	GetLgdPath
	GetHomePath
	GetLibPath
	SetConfig
	GetConfig
	TestSuite
************************************************
Assistant functions:
	Default
	SplitClip
	FrameType
	JudgeMatrix
	RemoveFileExt
	RightStr
	LeftStr
	ConvertToTimecode
	ToAscii
	Roma
************************************************
Command functions:
	AddDefEnv
	AddParm
	ToDict
	GetEach
	CreatScripts
	StartScripts
	Muxers
	Muxer
	LsmashMuxers
	LsmashMuxer
	Demuxer
	TsDemuxer
	EacDemuxer
	AudioEnc
	AudioTrimFF
	AudioTrimFFSingle
	AudioTrimAVS
	ExtractModule
	Preview
*********************************************"""

"""*********************************************
### Script    : qvs.py
### Program   : Qvs
### Contact   : http://weibo.com/egosub
### Homepage  : http://egosub.ske48.co
*********************************************"""


##################################################################################################
### Function  : EraseAny
### Function  : EraseAnyRel
### Function  : EraseAnyAbs
### Author    : ema
### Version   : v0.4
### Release   : 2018.06.02
##################################################################################################
### Be used for erase any transparent logo.
### YV12 and YV24 Only.
###
### an [int, default: 0] 
### ------------------
###    >> Using for EraseAny.
###    The alignment parameter takes a number from 1 to 9, corresponding to the positions of the keys on a numpad.
###    But when alignment equals 0, it's equivalent to full screen.
###
### l/t/r/b [int, default: 0]
### ------------------
###    >> Using for EraseAnyRel.
###    Crop is the simplest to use of the two. The arguments specify how many pixels to crop from each side. This function used to be called CropRel which is still an alias for it.
###    left/top/right/bottom pixels to be cropped for logo area.
###
### x/y/width/height [int, default: 0]
### ------------------
###    >> Using for EraseAnyAbs.
###    left/top/right/bottom pixels to be cropped for logo area.
###    CropAbs, on the other hand, is special, because it can accept clips with variable frame sizes and crop out a fixed size area, thus making it a fixed size clip.
###
### d/a/s/h [int, default: 1/2/4/6]
### ------------------
###    >> Using for EraseAny/EraseAnyRel/EraseAnyAbs.
###    The same parameters of KNLMeansCL.
###
### pos_x / pos_y [int, default: 0/0]
### ------------------
###    Adjust logo position, in a quarter pixel.
###
### device_type [string, default: 'gpu']
### ------------------
###    'accelerator' := Dedicated OpenCL accelerators.
###    'cpu' := An OpenCL device that is the host processor.
###    'gpu' := An OpenCL device that is a GPU.
###    'auto' := 'accelerator' -> 'gpu' -> 'cpu'.
### 
### device_id [int, default: 1]
### ------------------
###    The 'device_id' device of type 'device_type' in the system.
###    Example: [device_type = "GPU", device_id = 1] return the second GPU in the system.
###
### +----------------+
### |  REQUIREMENTS  |
### +----------------+
###	-> LogoNR
### 	-> KNLMeansCL
### 	-> RemoveGrain/Repair
##################################################################################################
def EraseAny(src, lgd, chroma=True, an=0, fadein=0, fadeout=0, start=0, end=None, pos_x=0, pos_y=0, depth=128, d=1, a=2, s=4, h=6, device_type='gpu', device_id=1):
	core = vs.get_core()
	
	def multOfTwo(value):
		value = int(value)
		if (value % 2) != 0:
			value += 1
		return value

	w = src.width
	h = src.height
	an_l_dict = {0 : 0,  1 : 0,        2 : (w/3),    3 : (w/3*2),  4 : 0,        5 : (w/3),  6 : (w/3*2),  7 : 0,        8 : (w/3),    9 : (w/3*2)}
	an_t_dict = {0 : 0,  1 : (h/3*2),  2 : (h/3*2),  3 : (h/3*2),  4 : (h/3),    5 : (h/3),  6 : (h/3),    7 : 0,        8 : 0,        9 : 0      }
	an_r_dict = {0 : 0,  1 : (w/3*2),  2 : (w/3),    3 : 0,        4 : (w/3*2),  5 : (w/3),  6 : 0,        7 : (w/3*2),  8 : (w/3),    9 : 0      }
	an_b_dict = {0 : 0,  1 : 0,        2 : 0,        3 : 0,        4 : (h/3),    5 : (h/3),  6 : (h/3),    7 : (h/3*2),  8 : (h/3*2),  9 : (h/3*2)}
	l = multOfTwo(an_l_dict[an])
	t = multOfTwo(an_t_dict[an])
	r = multOfTwo(an_r_dict[an])
	b = multOfTwo(an_b_dict[an])
	
	#raise ValueError('l={l},t={t},r={r},b={b}'.format(l=l, t=t, r=r, b=b))
	
	#Fixed bug of delogo plugin when using fadeout parameter
	if fadeout == 0:	end = Default(end, src.num_frames)
	else:				end = Default(end, src.num_frames - 3)
	dlg = core.delogo.EraseLogo(clip=src, logofile=lgd, start=start, end=end, fadein=fadein, fadeout=fadeout, pos_x=pos_x, pos_y=pos_y, depth=depth)
	try:
		src = LogoNR(dlg, src, chroma=chroma, l=l, t=t, r=r, b=b, d=d, a=a, s=s, h=h, device_type=device_type, device_id=device_id)
	except:
		src = LogoNR(dlg, src, chroma=chroma, l=l, t=t, r=r, b=b, d=d, a=a, s=s, h=h, device_type=device_type, device_id=0)
	return src


def EraseAnyRel(src, lgd, chroma=True, l=0, t=0, r=0, b=0, fadein=0, fadeout=0, start=0, end=None, pos_x=0, pos_y=0, depth=128, d=1, a=2, s=4, h=6, device_type='gpu', device_id=0):
	core = vs.get_core()
	
	#Fixed bug of delogo plugin when using fadeout parameter
	if fadeout == 0:	end = Default(end, src.num_frames)
	else:				end = Default(end, src.num_frames - 3)
	
	dlg = core.delogo.EraseLogo(clip=src, logofile=lgd, start=start, end=end, fadein=fadein, fadeout=fadeout, pos_x=pos_x, pos_y=pos_y, depth=depth)
	try:
		src = LogoNR(dlg, src, chroma=chroma, l=l, t=t, r=r, b=b, d=d, a=a, s=s, h=h, device_type=device_type, device_id=device_id)
	except:
		src = LogoNR(dlg, src, chroma=chroma, l=l, t=t, r=r, b=b, d=d, a=a, s=s, h=h, device_type=device_type, device_id=0)
	return src

def EraseAnyAbs(src, lgd, chroma=True, x=0, y=0, width=0, height=0, fadein=0, fadeout=0, start=0, end=None, pos_x=0, pos_y=0, depth=128, d=1, a=2, s=4, h=6, device_type='gpu', device_id=0):
	core = vs.get_core()
	
	#Fixed bug of delogo plugin when using fadeout parameter
	if fadeout == 0:	end = Default(end, src.num_frames)
	else:				end = Default(end, src.num_frames - 3)

	if width == 0:
		width = src.width
	if height == 0:
		height = src.height
	l = x
	t = y
	r = src.width - x - width
	b = src.height - y - height
	dlg = core.delogo.EraseLogo(clip=src, logofile=lgd, start=start, end=end, fadein=fadein, fadeout=fadeout, pos_x=pos_x, pos_y=pos_y, depth=depth)
	try:
		src = LogoNR(dlg, src, chroma=chroma, l=l, t=t, r=r, b=b, d=d, a=a, s=s, h=h, device_type=device_type, device_id=device_id)
	except:
		src = LogoNR(dlg, src, chroma=chroma, l=l, t=t, r=r, b=b, d=d, a=a, s=s, h=h, device_type=device_type, device_id=0)
	return src


##################################################################################################
### Function  : LogoNR
### Author    : 06_taro
### Version   : v0.1
### Release   : 2012.04.22
##################################################################################################
### Designer  : ema
### Version   : v0.3
### Release   : 2018.06.02
##################################################################################################
### Post-denoise filter of EraseLogo.
### Only process logo areas in logo frames, even if l/t/r/b are not set. Non-logo areas are left untouched.
###
### +---------+
### |  USAGE  |
### +---------+
###
### dlg [clip]
### ------------------
###    Clip after delogo.
###
### src [clip]
### ------------------
###    Clip before delogo.
###
### chroma [bool, default: True]
### ------------------
###    Process chroma plane or not.
###
### l/t/r/b [int, default: 0]
### ------------------
###    left/top/right/bottom pixels to be cropped for logo area.
###    Have the same restriction as CropRel, e.g., no odd value for YV12.
###    logoNR only filters the logo areas in logo frames, no matter l/t/r/b are set or not.
###    So if you have other heavy filters running in a pipeline and don't care much about the speed of logoNR,
###    it is safe to left these values unset.
###    Setting these values only makes logoNR run faster, with rarely noticeable difference in result,
###    unless you set wrong values and the logo is not covered in your cropped target area.
###
### d/a/s/h [int, default: 1/2/4/6]
### ------------------
###    The same parameters of KNLMeansCL.
###
### device_type [string, default: 'gpu']
### ------------------
###    'accelerator' := Dedicated OpenCL accelerators.
###    'cpu' := An OpenCL device that is the host processor.
###    'gpu' := An OpenCL device that is a GPU.
###    'auto' := 'accelerator' -> 'gpu' -> 'cpu'.
### 
### device_id [int, default: 1]
### ------------------
###    The 'device_id' device of type 'device_type' in the system.
###    Example: [device_type = "GPU", device_id = 1] return the second GPU in the system.
###
### +----------------+
### |  REQUIREMENTS  |
### +----------------+
### -> havsfunc
### 	-> KNLMeansCL
### 	-> RGVS(mt_expand_multi)
##################################################################################################
def LogoNR(dlg, src, chroma=True, l=0, t=0, r=0, b=0, d=1, a=2, s=2, h=3, device_type='gpu', device_id=1):
	core = vs.get_core()

	if not (isinstance(dlg, vs.VideoNode) and isinstance(src, vs.VideoNode)):
		raise TypeError('logoNR: This is not a clip')
	if dlg.format.id != src.format.id:
		raise TypeError('logoNR: clips must have the same format')

	if dlg.format.color_family == vs.GRAY:
		chroma = False

	if not chroma and dlg.format.color_family != vs.GRAY:
		dlg_orig = dlg
		dlg = mvf.GetPlane(dlg, 0)
		src = mvf.GetPlane(src, 0)
	else:
		dlg_orig = None

	b_crop = (l != 0) or (t != 0) or (r != 0) or (b != 0)
	if b_crop:
		src = core.std.Crop(src, l, r, t, b)
		last = core.std.Crop(dlg, l, r, t, b)
	else:
		last = dlg

	if chroma:
		clp_nr = haf.KNLMeansCL(last, d=d, a=a, s=s, h=h, device_type=device_type, device_id=device_id)
	else:
		clp_nr = core.knlm.KNLMeansCL(last, d=d, a=a, s=s, h=h, device_type=device_type, device_id=device_id)

	logoM = haf.mt_expand_multi(core.std.Expr([last, src], ['x y - abs 16 *']), mode='losange', sw=3, sh=3).std.Convolution(matrix=[1, 1, 1, 1, 0, 1, 1, 1, 1]).std.Deflate()
	clp_nr = core.std.MaskedMerge(last, clp_nr, logoM)

	if b_crop:
		clp_nr = haf.Overlay(dlg, clp_nr, x=l, y=t)

	if dlg_orig is not None:
		return core.std.ShufflePlanes([clp_nr, dlg_orig], planes=[0, 1, 2], colorfamily=dlg_orig.format.color_family)
	else:
		return clp_nr


##################################################################################################
### Function  : EraseDMM360
### Function  : EraseDMM450
### Function  : EraseDMM720
### Function  : EraseDMM720_2
### Function  : EraseDMM1080
### Function  : EraseDMM1080_2
### Function  : GetLgdPath
### Author    : ema
### Version   : v0.2.2
### Release   : 2018.01.11
##################################################################################################
### All of '*.lgd' files were made from SKE48 Stage Perf.
### EraseDMM720 applies only to SKE48 Stage Perf.
###
### GetLgdPath:
### path [str, default: ''] 
### ------------------
###    Get the '*.lgd' files dir path.
###    Parm of path is '' : True  -> '/Python36/Lib/site-packages/logodata',
###                         False -> path.
###
### +----------------+
### |  REQUIREMENTS  |
### +----------------+
###	-> LogoNR
### 	-> KNLMeansCL
### 	-> RemoveGrain/Repair
##################################################################################################
def EraseDMM360(src, lgd=None, pos_x=0, pos_y=0, device_type='gpu', device_id=1):
	lgd = Default(lgd, GetLgdPath() + '/dmm360.lgd')
	return EraseAnyRel(src, lgd, chroma=True, l=16, t=8, r=494, b=328, pos_x=pos_x, pos_y=pos_y, device_type=device_type, device_id=device_id)

def EraseDMM450(src, lgd=None, pos_x=0, pos_y=0, device_type='gpu', device_id=1):
	lgd = Default(lgd, GetLgdPath() + '/dmm450.lgd')
	return EraseAnyRel(src, lgd, chroma=True, l=20, t=4, r=678, b=420, pos_x=pos_x, pos_y=pos_y, device_type=device_type, device_id=device_id)

def EraseDMM720(src, lgd=None, pos_x=0, pos_y=0, device_type='gpu', device_id=1):
	lgd = Default(lgd, GetLgdPath() + '/dmm_skelive720.lgd')
	return EraseAnyRel(src, lgd, chroma=True, l=928, t=672, r=22, b=14, pos_x=pos_x, pos_y=pos_y, device_type=device_type, device_id=device_id)

def EraseDMM720_2(src, lgd=None, pos_x=0, pos_y=0, device_type='gpu', device_id=1):
	lgd = Default(lgd, GetLgdPath() + '/dmm_skelive720_2.lgd')
	return EraseAnyRel(src, lgd, chroma=True, l=808, t=672, r=26, b=18, pos_x=pos_x, pos_y=pos_y, device_type=device_type, device_id=device_id)

def EraseDMM1080(src, lgd=None, pos_x=0, pos_y=0, device_type='gpu', device_id=1):
	lgd = Default(lgd, GetLgdPath() + '/dmm1080.lgd')
	return EraseAnyRel(src, lgd, chroma=True, l=50, t=20, r=1486, b=984, pos_x=pos_x, pos_y=pos_y, device_type=device_type, device_id=device_id)

def EraseDMM1080_2(src, lgd=None, pos_x=0, pos_y=0, device_type='gpu', device_id=1):
	lgd = Default(lgd, GetLgdPath() + '/dmm1080_2.lgd')
	return EraseAnyRel(src, lgd, chroma=True, l=50, t=20, r=1486, b=984, pos_x=pos_x, pos_y=pos_y, device_type=device_type, device_id=device_id)

def GetLgdPath(path='', show=False):
	try:
		path = GetConfig(section='python', options='logodata')
	except:
		path = GetLibPath(lib='/site-packages/logodata')
	if show:
		list = []
		for file in os.listdir(path):
			if file.split('.')[-1].lower() == 'lgd':
				list.append(file)
		raise ValueError('Show the lgd list = ' + str(list))
	return path


##################################################################################################
### Function  : GetLibPath
### Author    : ema
### Version   : v0.1
### Release   : 2018.01.11
##################################################################################################
### Return the dir path of lib, such as '/Python36/Lib'.
##################################################################################################
def GetLibPath(lib='/site-packages'):
	path = os.path.dirname(os.__file__)
	if os.path.isfile(path):
		path = os.path.dirname(path)
	path += lib
	path = os.path.normpath(path)
	return path


##################################################################################################
### Function  : GetHomePath
### Author    : ema
### Version   : v0.1
### Release   : 2018.08.15
##################################################################################################
### Return the dir path of home, such as '/Python37'.
##################################################################################################
def GetHomePath():
	working_path = os.getcwd()
	path = os.path.dirname(os.__file__)
	if os.path.isfile(path):
		path = os.path.dirname(path)
	path = os.path.normpath(path)
	os.chdir(path)
	path = os.path.abspath('../')
	os.chdir(working_path)
	return path


##################################################################################################
### Function  : Preview
### Author    : ema
### Version   : v0.1
### Release   : 2018.06.02
##################################################################################################
### Preview media file or avisynth script wiht Aviutl.
##################################################################################################
def Preview(path, lgd=None):
	lgd_delogo_auf_ready_path = os.path.normpath(sys.prefix + '/tools/Aviutl/ready_plugins/delogo.auf')
	lgd_delogo_auf_path       = os.path.normpath(sys.prefix + '/tools/Aviutl/plugins/delogo.auf')
	if path == '':
		raise ValueError('Preview: path is empty.')
	lgd = Default(lgd, False)
	if lgd:
		old_filename = lgd_delogo_auf_ready_path
		new_filename = lgd_delogo_auf_path
		#Config file codec of Aviutl can't decode.
		#SetConfig(options='logfile', value=lgd, section='Transparent logo', conf_file=os.path.normpath(sys.prefix + '/tools/Aviutl/aviutl.ini'))
	else:
		old_filename = lgd_delogo_auf_path
		new_filename = lgd_delogo_auf_ready_path
	try:
		shutil.move(old_filename, new_filename)		
	except:
		pass
	subprocess.Popen('aviutl "{path}"'.format(path=path), shell=True)


##################################################################################################
### Function  : SetWorkingDir
### Author    : ema
### Version   : v0.1
### Release   : 2018.01.17
##################################################################################################
### Sets the default directory for AviSynth to the path argument.
###
### path [str, Default: '']
### ------------------
###    Load plugins in a path such as '/Python36/Lib/site-packages/vapoursynth_plugins'.
###
### isAvs [bint, Default: True]
### ------------------
###    True  -> avs plugins : core.avs.LoadPlugin(path)
###    False -> vs plugins  : core.std.LoadPlugin(path)
##################################################################################################
def SetWorkingDir(core, path='', isAvs=True):
	path = GetLibPath(lib='/site-packages/vapoursynth_plugins') if (path == '') else path
	if path[-1] != '/':
		path = path + '/'
	for root, dirs, files in os.walk(path):
		for file in files:
			if file.split('.')[-1].lower() == 'dll':
				if isAvs:
					try:
						core.avs.LoadPlugin(path+file)
					except:
						pass
				else:
					try:
						core.std.LoadPlugin(path+file)
					except:
						pass
	return core


##################################################################################################
### Function  : FillMargins
### Author    : ema
### Version   : v0.1
### Release   : 2018.01.01
##################################################################################################
###	Fills the borders exactly like the Avisynth filter FillMargins.
###
### l/t/r/b [int, default: 0]
### ------------------
###    left/top/right/bottom pixels to be filled for margins area.
###
### +----------------+
### |  REQUIREMENTS  |
### +----------------+
### -> libfillborders.dll
##################################################################################################
def FillMargins(src, l=0, t=0, r=0, b=0):
	core = vs.get_core()
	src = core.fb.FillBorders(src, left=l, top=t, right=r, bottom=b, mode='fillmargins')
	return src


##################################################################################################
### Function  : AddMargins
### Author    : ema
### Version   : v0.1
### Release   : 2018.02.14
##################################################################################################
###	Add the borders.
###
### l/t/r/b [int, default: 0]
### ------------------
###    left/top/right/bottom pixels to be added for margins area.
###
### fv [bint, default: False]
### ------------------
###    To do FlipVertical(|) when True.
###
### fh [bint, default: False]
### ------------------
###    To do FlipHorizontal(-) when True.
##################################################################################################
def AddMargins(clip, l=0, t=0, r=0, b=0, fv=False, fh=False, blur=True, radius=10):
	core = vs.get_core()
	h = clip.height
	w = clip.width
	c_t = ColorMask(core.std.Crop(clip, left=0, top=0, right=0, bottom=h-t))
	c_b = ColorMask(core.std.Crop(clip, left=0, top=h-b, right=0, bottom=0))
	if fv:
		c_t = core.std.FlipVertical(c_t)
		c_b = core.std.FlipVertical(c_b)
	if fh:
		c_t = core.std.FlipHorizontal(c_t)
		c_b = core.std.FlipHorizontal(c_b)
	if blur:
		c_t = core.std.BoxBlur(c_t, hradius=radius, vradius=radius)
		c_b = core.std.BoxBlur(c_b, hradius=radius, vradius=radius)
	last = core.std.StackVertical([c_t, clip, c_b])
	c_l = ColorMask(core.std.Crop(last, left=0, top=0, right=w-r, bottom=0))
	c_r = ColorMask(core.std.Crop(last, left=w-l, top=0, right=0, bottom=0))
	if fv:
		c_l = core.std.FlipVertical(c_l)
		c_r = core.std.FlipVertical(c_r)
	if fh:
		c_l = core.std.FlipHorizontal(c_l)
		c_r = core.std.FlipHorizontal(c_r)
	if blur:
		c_l = core.std.BoxBlur(c_l, hradius=radius, vradius=radius)
		c_r = core.std.BoxBlur(c_r, hradius=radius, vradius=radius)
	last = core.std.StackHorizontal([c_l, last, c_r])
	return last


##################################################################################################
### Function  : ColorMask
### Author    : ema
### Version   : v0.1
### Release   : 2018.02.14
##################################################################################################
###	Overlay a color mask to your clip with opacity value.
##################################################################################################
def ColorMask(clip, color=None, opacity=0.5):
	core = vs.get_core()
	color_dict = {'RGB' : [255, 255, 255], 'YUV' : [255, 128, 128]}
	if IsRGB(clip):
		color = Default(color, color_dict.get('RGB'))
	else:
		color = Default(color, color_dict.get('YUV'))
	mask = core.std.BlankClip(clip, color=color)
	return Overlay(clip, mask, opacity=opacity)


##################################################################################################
### Function  : SpeedGear
### Author    : ema
### Version   : v0.1
### Release   : 2018.01.01
##################################################################################################
### Redesign function AssumeFPS.
###	SpeedGear.avsi supports modifying audio.
###
### gear [float, default: 1]
### ------------------
###    Multiples for changing the playback speed.
###
### +----------------+
### |  REQUIREMENTS  |
### +----------------+
### -> havsfunc.py
###		-> ChangeFPS
##################################################################################################
def SpeedGear(src, gear=1, keepfps=True):
	core = vs.get_core()
	fpsnum = src.fps_num
	fpsden = src.fps_den
	dec = 1000
	dec = dec*dec*dec
	src = core.std.AssumeFPS(src, fpsnum=fpsnum*int(gear*dec), fpsden=fpsden*dec)
	if keepfps:
		src = haf.ChangeFPS(src, fpsnum=fpsnum, fpsden=fpsden)
	return src


##################################################################################################
### Function  : ForceFilm
### Author    : ema
### Version   : v0.1
### Release   : 2018.01.25
##################################################################################################
### Returns a clip with the framerate changed.
### This does not in any way modify the frames, only their metadata.
### AssumeFPS overwrites the frame properties _DurationNum and _DurationDen with the frame duration computed from the new frame rate.
##################################################################################################
def ForceFilm(clip):
	core = vs.get_core()
	return core.std.AssumeFPS(clip, fpsnum=24000, fpsden=1001)


##################################################################################################
### Function  : ImageSourceMul
### Author    : ema
### Version   : v0.3
### Release   : 2018.01.01
##################################################################################################
### Load mul image file to be a clip.
### 
### path [str, default: '.']
### ------------------
###    Image source files path.
###    It's the working path at the same time when using default val.
###
### filter [str[], default: ['exe', 'vpy', 'py', 'dll', 'lib']]
### ------------------
###    Using when path does not contain wildcards.
###    Setting the filter of file system, 
###    It's the working path at the same time when using default val.
###
### +----------------+
### |  REQUIREMENTS  |
### +----------------+
### -> havsfunc.py
###		-> ChangeFPS
###	-> libHalf.dll
###	-> libIex.dll
###	-> libIexMath.dll
###	-> libIlmImf.dll
###	-> libIlmImfUtil.dll
###	-> libIlmThread.dll
###	-> libImath.dll
###	-> libimwri.dll
##################################################################################################
def ImageSourceMul(path='.', every=30, w=1280, h=720, fps=29.970, filter=None, dslv=True, dslv_f=None):
	core = vs.get_core()
	funcName = 'ImageSourceMul'
	if dslv_f is None:
		if math.floor(every / 2.5) < math.floor(fps / 2.5):
			dslv_f = math.floor(every / 2.5)
		else:
			dslv_f = math.floor(fps / 2.5)
	if dslv:
		every += math.ceil(dslv_f / 2)
	filter = Default(filter, ['exe', 'vpy', 'py', 'dll', 'lib'])
	path = os.path.abspath(path).replace('\\','/')
	filelist = []
	src = core.std.BlankClip(length=1, fpsnum=30, format=vs.RGB24)
	src = ConvertToYV12(src)
	src = core.resize.Lanczos(src, w, h)
	
	if path.find('*') == -1 & path.find('?') == -1:
		for f in os.listdir(path):
			f = os.path.join(path, f).replace('\\','/')
			if not filter == []:
				for exp in filter:
					if f.split('.')[-1].lower() == exp.lower():
						filelist.append(f)
			else:
				filelist.append(f)
	else:
		files = glob.glob(path)
		for f in files:
			filelist.append(f.replace('\\','/'))
	
	isFirstFrame = True
	for f in filelist:
		print(f)
		try:
			img = OverlayM(src=ConvertToYV12(core.imwri.Read(f)), w=w, h=h) * every
		except:
			raise TypeError(funcName + ': Failed to read image properties ' + f)
		if isFirstFrame:
			src += img
			src = core.std.DeleteFrames(src, 0)
			isFirstFrame = False
		else:
			if dslv:
				src = Dissolve(src, img, dslv_f)
			else:
				src += img
	src = ChangeFPS(src, fps=fps)
	return ConvertToYV12(src)


##################################################################################################
### Function  : Overlay
### Author    : ema
### Version   : v0.1
### Release   : 2018.01.01
##################################################################################################
### Redesign the Overlay function to increase the opacity parameter.
###
### +----------------+
### |  REQUIREMENTS  |
### +----------------+
### -> havsfunc.py
###		-> Overlay
##################################################################################################
def Overlay(clipa, clipb, x=0, y=0, mask=None, opacity=1):
	core = vs.get_core()
	return core.std.Merge(clipa, haf.Overlay(clipa, clipb, mask=mask), weight=[opacity, opacity])


##################################################################################################
### Function  : Overlaymod
### Author    : ema
### Version   : v0.1
### Release   : 2018.01.01
##################################################################################################
### Redesign the Overlaymod function to increase the opacity parameter.
###
### +----------------+
### |  REQUIREMENTS  |
### +----------------+
### -> xvs.py
###		-> Overlaymod
##################################################################################################
def Overlaymod(clipa, clipb, x=0, y=0, alpha=None, opacity=1, aa=False):
	core = vs.get_core()
	return core.std.Merge(clipa, xvs.Overlaymod(clipa, clipb, alpha=alpha, aa=False), weight=[opacity, opacity])


##################################################################################################
### Function  : AddLogo
### Author    : ema
### Version   : v0.1
### Release   : 2018.01.01
##################################################################################################
### Add image logo otherwise using *.lgd.
###
### +----------------+
### |  REQUIREMENTS  |
### +----------------+
### -> mvsfunc.py
###		-> ToYUV
### -> xvs.py
###		-> Overlaymod
###	-> libHalf.dll
###	-> libIex.dll
###	-> libIexMath.dll
###	-> libIlmImf.dll
###	-> libIlmImfUtil.dll
###	-> libIlmThread.dll
###	-> libImath.dll
###	-> libimwri.dll
##################################################################################################
def AddLogo(src, path, w=None, h=None, an=None, x=0, y=0, opacity=1, aa=False):
	core = vs.get_core()
	funcName = 'AddLogo'
	if path.split('.')[-1] == 'lgd':
		return core.delogo.AddLogo(clip=src, logofile=path)
	img, img_alpha = core.imwri.Read(path, alpha=True)
	img = mvf.ToYUV(img, css='444')
	if w is not None:
		if h is not None:
			img = core.resize.Lanczos(img, w, h)
	if an is not None:
		if an == 1 | an == 4 | an == 7:
			x = 0
		elif an == 2 | an == 5 | an == 8:
			x = math.floor((src.width - img.width) / 2)
		elif an == 3 | an == 6 | an == 9:
			x = src.width - img.width
		if an == 7 | an == 8 | an == 9:
			y = 0
		elif an == 4 | an == 5 | an == 6:
			y = math.floor((src.height - img.height) / 2)
		elif an == 1 | an == 2 | an == 3:
			y = src.height - img.height
	return Overlaymod(src, img, x=x, y=y, alpha=img_alpha, opacity=opacity, aa=aa)


##################################################################################################
### Function  : FFImageSource
### Author    : ema
### Version   : v0.1
### Release   : 2018.01.01
##################################################################################################
### Redesign ChangeFPS from havsfunc.py
### Enable float val when using fps.
###
### fps [float, int]
### ------------------
###    FrameRate.
###    Priority: fps > fpsnum && fpsden
###
### +----------------+
### |  REQUIREMENTS  |
### +----------------+
### -> ffms2.dll
##################################################################################################
def FFImageSource(src, length=1, fps=29.970, width=None, height=None):
	core = vs.get_core()
	width = Default(width, -1)
	height = Default(height, -1)
	dec = 1000
	fpsnum = int(fps * dec)
	fpsden = dec
	return core.ffms2.Source(source=src, cache=False, fpsnum=fpsnum, fpsden=fpsden, seekmode=-1, width=width, height=height, resizer='BICUBIC') * length


##################################################################################################
### Function  : LWLSource
### Author    : ema
### Version   : v0.1
### Release   : 2018.01.01
##################################################################################################
### Return the default val when it is none.
###
### isCheck [bool, default: True]
### ------------------
###    If true is set, then analyze whether exp belongs to isomedia standard.
###
### See more from github
### ------------------
###    https://github.com/VFR-maniac/L-SMASH-Works/tree/master/VapourSynth
###    https://github.com/VFR-maniac/L-SMASH-Works/tree/master/AviSynth
###
### See more from avisynth.nl
### ------------------
###	   http://avisynth.nl/index.php/LSMASHSource/LSMASHVideoSource
###
### format [default : '']
### ------------------
###    Force specified output pixel format if 'format' is specified and 'variable' is set to 0.
###    The following formats are available currently.
###      "YUV420P8"
###      "YUV422P8"
###      "YUV444P8"
###      "YUV410P8"
###      "YUV411P8"
###      "YUV440P8"
###      "YUV420P9"
###      "YUV422P9"
###      "YUV444P9"
###      "YUV420P10"
###      "YUV422P10"
###      "YUV444P10"
###      "YUV420P16"
###      "YUV422P16"
###      "YUV444P16"
###      "RGB24"
###      "RGB27"
###      "RGB30"
###      "RGB48"
###
### decoder [default : '']
### ----------------
### | V..... = Video
### | A..... = Audio
### | S..... = Subtitle
### | .F.... = Frame-level multithreading
### | ..S... = Slice-level multithreading
### | ...X.. = Codec is experimental
### | ....B. = Supports draw_horiz_band
### | .....D = Supports direct rendering method 1
###	* -----List-----              -----Description-----
### | VFS..D h264                 H.264 / AVC / MPEG-4 AVC / MPEG-4 part 10
### * V....D h264_qsv             H.264 / AVC / MPEG-4 AVC / MPEG-4 part 10 (Intel Quick Sync Video acceleration) (codec h264)
### * V..... h264_cuvid           Nvidia CUVID H264 decoder (codec h264)
### | VFS..D hevc                 HEVC (High Efficiency Video Coding)
### * V....D hevc_qsv             HEVC (Intel Quick Sync Video acceleration) (codec hevc)
### * V..... hevc_cuvid           Nvidia CUVID HEVC decoder (codec hevc)
### | V.S.BD mpeg1video           MPEG-1 video
### | V..... mpeg1_cuvid          Nvidia CUVID MPEG1VIDEO decoder (codec mpeg1video)
### | V.S.BD mpeg2video           MPEG-2 video
### | V.S.BD mpegvideo            MPEG-1 video (codec mpeg2video)
### * V....D mpeg2_qsv            MPEG-2 video (Intel Quick Sync Video acceleration) (codec mpeg2video)
### * V..... mpeg2_cuvid          Nvidia CUVID MPEG2VIDEO decoder (codec mpeg2video)
### | VF..BD mpeg4                MPEG-4 part 2
### * V..... mpeg4_cuvid          Nvidia CUVID MPEG4 decoder (codec mpeg4)
### | V...BD msmpeg4v1            MPEG-4 part 2 Microsoft variant version 1
### | V...BD msmpeg4v2            MPEG-4 part 2 Microsoft variant version 2
### | V...BD msmpeg4              MPEG-4 part 2 Microsoft variant version 3 (codec msmpeg4v3)
### | V....D vc1                  SMPTE VC-1
### * V....D vc1_qsv              VC-1 video (Intel Quick Sync Video acceleration) (codec vc1)
### * V..... vc1_cuvid            Nvidia CUVID VC1 decoder (codec vc1)
### | VF..BD vp3                  On2 VP3
### | V....D vp5                  On2 VP5
### | V....D vp6                  On2 VP6
### | V.S..D vp6a                 On2 VP6 (Flash version, with alpha channel)
### | V....D vp6f                 On2 VP6 (Flash version)
### | V....D vp7                  On2 VP7
### | VFS..D vp8                  On2 VP8
### * V..... vp8_cuvid            Nvidia CUVID VP8 decoder (codec vp8)
### * V....D vp8_qsv              VP8 video (Intel Quick Sync Video acceleration) (codec vp8)
### | VFS..D vp9                  Google VP9
### * V....D libvpx-vp9           libvpx VP9 (codec vp9)
### * V..... vp9_cuvid            Nvidia CUVID VP9 decoder (codec vp9)
### |_______________
###
### +----------------+
### |  REQUIREMENTS  |
### +----------------+
### -> vslsmashsource.dll
##################################################################################################
def LWLSource(path, isCheck=True, threads=0, dr=0, fpsnum=0, fpsden=1, variable=0, format='', decoder='', repeat=0, dominance=0):
	core = vs.get_core()
	path = Default(path, GetLibPath(lib='/..') + '/example.mp4')
	isIsoMedia = False
	if isCheck:
		isoMedia = {'mp4', '3gp', 'mov', '3g2', 'mj2', 'dvb', 'dcf', 'm21'}
		for exp in isoMedia:
			if exp == path.split('.')[-1].lower():
				isIsoMedia = True
				break
	if isCheck & isIsoMedia:
		return core.lsmas.LibavSMASHSource(source=path, threads=threads, dr=dr, fpsnum=fpsnum, fpsden=fpsden, variable=variable, format=format, decoder=decoder)
	else:
		return core.lsmas.LWLibavSource(source=path, cache=1, threads=threads, dr=dr, fpsnum=fpsnum, fpsden=fpsden, variable=variable, format=format, decoder=decoder, repeat=repeat, dominance=dominance)


##################################################################################################
### Function  : DirectShowSource
### Author    : ema
### Version   : v0.3
### Release   : 2018.06.02
##################################################################################################
### DirectShowSource reads media files using Microsoft DirectShow, 
### the same multimedia playback system that WMP (Windows Media Player) uses. 
### It can read most formats that WMP can, including MP4, MP3, most MOV (QuickTime) files, 
### as well as AVI files that AVISource doesn't support (like DV type 1, or files using DirectShow-only codecs). 
### There is also support for GraphEdit (grf) files.
###
### filename [str, Default: True]
### ------------------
###    The path of the source file.
### 
### fps [float, Default: None]
### ------------------
###    Frames Per Second of the resulting clip.
### 
### seek [bint, Default: True]
### ------------------
###    There is full seeking support available on most file formats.
###    If problems occur, try setting seekzero=true first.
###    If seeking still causes problems, disable seeking completely with seek=false.
###    With seeking disabled and trying to seek backwards, the audio stream returns silence,
###    and the video stream returns the most recently rendered frame.
###    Note the Avisynth cache may provide limited access to the previous few frames,
###    but beyond that the most recently frame rendered will be returned.
### 
### audio [bint, Default: True]
### ------------------
###    Enable audio on the resulting clip.
###    The channel ordering is the same as in the wave-format-extensible format,because the input is always decompressed to WAV.
###    For more information, see also GetChannel.
###    AviSynth loads 8, 16, 24 and 32 bit int PCM samples, and float PCM format, and any number of channels.
### 
### video [bint, Default: True]
### ------------------
###    Enable video on the resulting clip.
### 
### convertfps [bint, Default: False]
### ------------------
###    If true, it turns VFR (variable framerate) video into CFR (constant framerate) video by adding frames.
###    This allows you to open VFR video in AviSynth.
###    It is most useful when fps is set to the least common multiple of the component frame rates, e.g. 120 or 119.880.
### 
### seekzero [bint, Default: False]
### ------------------
###    If true, restrict backwards seeking only to the beginning, and seeking forwards is done the hard way (by reading all samples).
###    Limited backwards seeking is allowed with non-indexed ASF.
### 
### timeout [int, Default: None]
### ------------------
###    ->> For positive values DirectShowSource waits for up to timeout milliseconds for the DirectShow graph to start.
###    timeout is clamped between [5000,300000] milliseconds.
###    If the graph fails to start a compile time exception is thrown.
###    Once the graph starts, each GetFrame/GetAudio call will wait for up to the timeout value and then return a grey frame
###    or silence for the audio. No runtime exceptions are ever thrown because of time-outs.
###    ->> For negative values DirectShowSource waits for up to 2000 milliseconds for the DirectShow graph to start.
###    If the graph fails to start it is ignored at that point and the initial graph start wait is deferred until the first GetFrame/GetAudio call.
###    If any GetFrame/GetAudio call experiences a timeout a runtime exception is then thrown.
###
### pixel_type [str, Default: None]
### ------------------
###    Request a color format from the decompressor. Valid values are:
###    YV24,	YV16,	YV12,	I420,	NV12,	YUY2,	AYUV,	Y41P,	Y411,	ARGB,	RGB32,	RGB24,	YUV,	YUVex,	RGB,	AUTO,	FULL
###
### framecount [int, Default: None]
### ------------------
###    Sometimes needed to specify the frame count of the video.
###    If the framerate or the number of frames is incorrect (this can happen with ASF or MOV clips for example), use this option to force the correct number of frames.
###    If fps is also specified, the length of the audio stream is adjusted.
###    For live sources, specify a very large number.
###
### logfile [str, Default: None]
### ------------------
###    Use this option to specify the name of a log file for debugging.
###
### logmask [int, Default: 35]
### ------------------
###    When a logfile is specified, use this option to select which information is logged.
###
### debug [int, Default: False]
### ------------------
###    Create the avisynth script for testing.
###
### yv12 [bint, Default: False]
### ------------------
###    Output clip with YV12.
###
### +----------------+
### |  REQUIREMENTS  |
### +----------------+
### -> DirectShowSource.dll (32bit, RECOMMENDED)
###    or DirectShowSource.dll (64bit+, NO_RECOMMENDED, MAY_CAUSE_A_FATAL_ERROR)
###	-> avsproxy.dll (32bit, REQUEST_IN_32BIT_AVS)
### -> vsavsreader.dll
##################################################################################################
def DirectShowSource(filename, fps=None, seek=True, audio=True, video=True, convertfps=False, seekzero=False, timeout=None, pixel_type=None, framecount=None, logfile=None, logmask=35, debug=False, yv12=False, proxy32=True):
	core = vs.get_core()
	def _BintToStr(val):
		if val:	return 'True'
		else:	return 'False'
	dss = '"{filename}"'.format(filename=filename)
	seek = _BintToStr(seek)
	audio = _BintToStr(audio)
	video = _BintToStr(video)
	convertfps = _BintToStr(convertfps)
	seekzero = _BintToStr(seekzero)
	seekzero = _BintToStr(seekzero)
	logmask = str(logmask)
	if not fps is None:
		fps = str(fps)
		dss = '{dss}, fps={fps}'.format(dss=dss, fps=fps)
	if not timeout is None:
		timeout = str(timeout)
		dss = '{dss}, timeout={timeout}'.format(dss=dss, timeout=timeout)
	if not framecount is None:
		framecount = str(framecount)
		dss = '{dss}, framecount={framecount}'.format(dss=dss, framecount=framecount)
	if not pixel_type is None:
		dss = '{dss}, pixel_type="{pixel_type}"'.format(dss=dss, pixel_type=pixel_type)
	if not logfile is None:
		dss = '{dss}, logfile="{logfile}"'.format(dss=dss, logfile=logfile)
	dss = '{dss}, seek={seek}, audio={audio}, video={video}, convertfps={convertfps}, seekzero={seekzero}, logmask={logmask}'.format(dss=dss, fps=fps, seek=seek, audio=audio, video=video, convertfps=convertfps, seekzero=seekzero, logmask=logmask)
	dss = 'DirectShowSource({dss})'.format(dss=dss)
	if proxy32:
		dss = 'LoadPlugin("{avsplugins}\\DirectShowSource.dll") {dss}'.format(avsplugins=GetLibPath(lib='./../avisynth32/plugins'), dss=dss)
		#raise ValueError(dss)
		last = core.avsw.Eval(dss)
	else:
		dss = 'LoadPlugin("{avsplugins}\\DirectShowSource.dll") {dss}'.format(avsplugins=GetLibPath(lib='../avisynthplus64/plugins'), dss=dss)
		#raise ValueError(dss)
		last = core.avsr.Eval(dss)
	if debug:
		path = os.getcwd()
		path = path.replace('\\', '/') + '/dss.avs'
		with open(path, 'w+') as f:
			f.write(dss)
		last = Subtitle(last, path + '\r' + dss)
	if yv12:
		last = ConvertToYV12(last)
	return last


##################################################################################################
### Function  : AvsTest
### Author    : ema
### Version   : v0.1
### Release   : 20187.05.28
##################################################################################################
def AvsTest(proxy32=True):
	core = vs.get_core()
	cmd = 'Version()'
	if proxy32:	func = core.avsw.Eval
	else:		func = core.avsr.Eval
	return func(cmd)


##################################################################################################
### Function  : GammaResize
### Author    : 787633258
### Version   : v1.03
### Release   : 2017.08.17
### Modified  : ema
##################################################################################################
### 1. Selectable reize of gamma-aware.
### 2. Matrix transform.
### 3. Simple bit depth transform.
###
### transs [str, default: '709']
### ------------------
###    Transfer of input clip.
###
### transd [str, default: the same as transs]
### ------------------
###    Transfer of output clip.
###
### auto_matrix [bool, default: True]
### ------------------
###	   If true is set, then it will auto to set the output clip matrix based on resolution ratio.
###
### mats [str, default: according to input clip resolution]
### ------------------
###	   Input clip matrix, according to input clip resolution.
###
### matd [str, default: according to output clip resolution and auto_matrix]
### ------------------
###	   Output clip matrix.
###	   Matd is according to output clip resolution when auto_matrix is true, but matd is equals to mats in other cases.
###
### k [str, default: 'spline36']
### ------------------
###	   Resize algorithm for specifying luma planes.
###
### k_c [str, default: k]
### ------------------
###	   Resize algorithm for specifying chroma planes.
###	   The optional value of k and k_c is:
###	       "point":                        Nearest neighbour interpolation. Same as Avisynth’s PointResize.
###	       "rect" or "box":                Box filter.
###	       "linear" or "bilinear":         Bilinear interpolation. Same as Avisynth’s BilinearResize.
###	       "cubic" or "bicubic":           Bicubic interpolation. Same as BicubicResize. The b and c variables are mapped on a1 and a2 and are both set to 1/3 by default.
###	       "lanczos":                      Sinc function windowed by the central lobe of a sinc. Use taps to specify its impulse length. Same as LanczosResize.
###	       "blackman":                     Blackman-Harris windowed sinc. Use taps to control its length. Same as BlackmanResize.
###	       "blackmanminlobe":              Another kind of Blackman windowed sinc, with a bit less ringing. Use taps for you know what.
###	       "spline16":                     Cubic spline based kernel, 4 sample points. Same as Spline16Resize.
###	       "spline36":                     Spline, 6 sample points. Same as Spline36Resize.
###	       "spline64":                     Spline, 8 sample points. Same as Spline64Resize.
###	       "spline":                       Generic splines, number of sample points is twice the taps parameter, so you can use taps = 6 to get a Spline144Resize equivalent.
###	       "gauss" or "gaussian":          Gaussian kernel. The p parameter is mapped on a1 and controls the curve width. The higher p, the sharper. It is set to 30 by default. This resizer is the same as GaussResize, but taps offers a control on the filter impulse length. For low p values (soft and blurry), it’s better to increase the number of taps to avoid truncating the gaussian curve too early and creating artifacts.
###	       "sinc":                         Truncated sinc function. Use taps to control its length. Same as SincResize.
###
### taps, a1, a2 [float, int, default: None]
### ------------------
###    Control the parameters of the selected luma plane resize algorithm.
###
### ctaps, c1, c2 [float, int, default: None]
### ------------------
###    Control the parameters of the selected chroma plane resize algorithm.
###
### gamma-aware [bool, default: based on input clip resolution ratio]
### ------------------
###    Determines whether to use gamma-aware resize.
###    When the length and width of the target resolution are less than or equal to the source, True, otherwise False.
###
### +----------------+
### |  REQUIREMENTS  |
### +----------------+
### -> mvsfunc.py
### 	-> Depth
### -> fmtconv.dll
##################################################################################################
def GammaResize(input, target_width=None, target_height=None, depth=None, transs=None, transd=None, auto_matrix=None, mats=None, matd=None,
		   k=None, taps=None, a1=None, a2=None, k_c=None, c1=None, c2=None, ctaps=None, gamma_aware=None):
	
	#Judge matrix of input clip
	def M(a,b):
		if a <= 1024 and b <= 576:
			return '601'
		elif a <= 2048 and b <= 1536:
			return '709'
		else :
			return '2020'
	
	#Resize algorithm
	def NUM(N):
		if   N == 'point':                    num = 0
		elif N == 'rect' or N=='box':         num = 1
		elif N == 'linear' or N=='bilinear':  num = 2
		elif N == 'cubic' or 'bicubic':       num = 3
		elif N == 'lanczos':                  num = 4
		elif N == 'blackman':                 num = 5
		elif N == 'blackmanminlobe':          num = 6
		elif N == 'spline16':                 num = 7
		elif N == 'spline36':                 num = 8
		elif N == 'spline64':                 num = 9
		elif N == 'spline'  :                 num = 10
		elif N == 'gauss' or N == 'gaussian': num = 11
		elif N == 'sinc':                     num = 12
		else:   raise TypeError(funcName + ': Unknown kernel(k) or chroma kernel(k_c)')
		return num

	#Selector of taps
	def t(num):
		return [None,None,None,None,3,3,3,None,None,None,3,3,3][num]

	#Selector of a1
	def x(num):
		return [None,None,None,1/3,None,None,None,None,None,None,None,30,None][num]

	#Selector of a2
	def y(num):
		return [None,None,None,1/3,None,None,None,None,None,None,None,None,None][num]

	core = vs.get_core()
	
	if not isinstance(input, vs.VideoNode):
		raise TypeError(funcName + ': This is not a clip!')

	funcName = 'GammaResize'

	k = Default(k, 'spline36')
	k_c = Default(k_c, k)

	#Check YV24
	prev_format = input.format.name
	if IsYUV(input):
		if not IsYV24(input):
			conv_format = True
			input = mvf.ToYUV(input, css='444', kernel=k)
	try:
		prev_format = prev_format[3:6]
	except:
		conv_format = False

	#Main
	width  = input.width
	height = input.height
	bit = input.format.bits_per_sample

	Y = core.std.ShufflePlanes(input, 0, colorfamily=vs.GRAY)
	U = core.std.ShufflePlanes(input, 1, colorfamily=vs.GRAY)
	V = core.std.ShufflePlanes(input, 2, colorfamily=vs.GRAY)

	chroma_width  = U.width
	chroma_height = U.height
	w = width/chroma_width
	h = height/chroma_height
	print (chroma_width)

	target_width = Default(target_width, width)
	target_height = Default(target_height, height)
	auto_matrix = Default(auto_matrix, True)
	transs = Default(transs, '709')
	transd = Default(transd, transs)
	depth = Default(depth, bit)
	mats = Default(mats, M(width,height))
	
	if matd is None:
		if auto_matrix == True:
			matd = M(target_width,target_height)
		elif auto_matrix == False:
			matd = mats
		else : raise TypeError(funcName + ': auto_matrix must be True or False')

	knum  = NUM(k)
	kcnum = NUM(k_c)

	taps = Default(taps, t(knum))
	ctaps = Default(ctaps, t(kcnum))
	a1 = Default(a1, x(knum))
	a2 = Default(a2, y(knum))
	c1 = Default(c1, x(kcnum))
	c2 = Default(c2, y(kcnum))

	if gamma_aware is None:
		if target_width <= width and target_height <= height:
			gamma_aware = True
		else:
			gamma_aware = False
			
	if mats != matd :
		if w==1 and h==1:
			input = core.fmtc.matrix(input,mats, mats, matd, bits=16)
		else:
			YA = core.fmtc.resample(Y,chroma_width,chroma_height)
			A = core.std.ShufflePlanes([YA,U,V],[0,0,0],colorfamily=vs.YUV)
			A = core.fmtc.matrix(A,mats, mats, matd, bits=16)
			UB = core.fmtc.resample(U,width,height)
			VB = core.fmtc.resample(V,width,height)
			B = core.std.ShufflePlanes([Y,UB,VB],[0,0,0],colorfamily=vs.YUV)
			B = core.fmtc.matrix(B,mats, mats, matd, bits=16)

	#Todo resize
	if target_width==width and target_height == height:
		if mats!=matd and w!=1 and h!=1:
			input = core.std.ShufflePlanes([B,A],[0,1,2], vs.YUV)
		last = input
		if depth!=bit or mats != matd:
			last = mvf.Depth(last,depth=depth)
	else:
		if mats != matd and w!=1 and h!=1:
			Y = core.std.ShufflePlanes(B, 0, colorfamily=vs.GRAY)
			UV = A
		else:
			if input.format.bits_per_sample<16:
				input = mvf.Depth(input,depth=16)
			Y = core.std.ShufflePlanes(input, 0, colorfamily=vs.GRAY)
			UV = input

		if gamma_aware == True:
			Y = core.fmtc.transfer(Y,transs=transs,transd='linear')
			Y = core.fmtc.resample(Y,target_width,target_height,kernel=k,taps=taps,a1=a1,a2=a2)
			Y = core.fmtc.transfer(Y,transs='linear',transd=transd)
		else:
			Y = core.fmtc.resample(Y,target_width,target_height,kernel=k,taps=taps,a1=a1,a2=a2)
		if mats == matd:
			UV = core.fmtc.resample(UV,target_width,target_height,kernel=k_c,taps=ctaps,a1=c1,a2=c2)
		else:
			UV = core.fmtc.resample(UV,int(target_width/w),int(target_height/h),kernel=k_c,taps=ctaps,a1=c1,a2=c2)
		last = core.std.ShufflePlanes([Y,UV],[0,1,2], vs.YUV)         
		last = mvf.Depth(last,depth=depth)
	
	#Format recovery
	if conv_format:
		last = mvf.ToYUV(last, css=prev_format)
	
	return last


##################################################################################################
### Function  : BoxResize
### Author    : ema
### Version   : v0.1
### Release   : 2018.01.16
##################################################################################################
### Resize clip with rect/box algorithm.
##################################################################################################
def BoxResize(clip, w, h, depth=None):
	depth = Default(depth, clip.format.bits_per_sample)
	return GammaResize(input=clip, target_width=w, target_height=h, depth=depth, k='box', k_c='box')


##################################################################################################
### Function  : BlinearResize
### Author    : ema
### Version   : v0.1
### Release   : 2018.01.16
##################################################################################################
### Resize clip with linear/bilinear algorithm.
##################################################################################################
def BlinearResize(clip, w, h, depth=None):
	depth = Default(depth, clip.format.bits_per_sample)
	return GammaResize(input=clip, target_width=w, target_height=h, depth=depth, k='bilinear', k_c='bilinear')


##################################################################################################
### Function  : BicubicResize
### Author    : ema
### Version   : v0.1
### Release   : 2018.01.16
##################################################################################################
### Resize clip with cubic/bicubic algorithm.
##################################################################################################
def BicubicResize(clip, w, h, depth=None):
	depth = Default(depth, clip.format.bits_per_sample)
	return GammaResize(input=clip, target_width=w, target_height=h, depth=depth, k='bicubic', k_c='bicubic')


##################################################################################################
### Function  : LanczosResize
### Author    : ema
### Version   : v0.1
### Release   : 2018.02.12
##################################################################################################
### Resize clip with lanczos algorithm.
##################################################################################################
def LanczosResize(clip, w, h, depth=None):
	depth = Default(depth, clip.format.bits_per_sample)
	return GammaResize(input=clip, target_width=w, target_height=h, depth=depth, k='lanczos', k_c='lanczos')


##################################################################################################
### Function  : LanczosResize
### Author    : ema
### Version   : v0.1
### Release   : 2018.01.16
##################################################################################################
### Resize clip with lanczos algorithm.
##################################################################################################
def Lanczos4Resize(clip, w, h, depth=None):
	depth = Default(depth, clip.format.bits_per_sample)
	return GammaResize(input=clip, target_width=w, target_height=h, depth=depth, k='lanczos', k_c='lanczos', taps=4)


##################################################################################################
### Function  : BlackmanResize
### Author    : ema
### Version   : v0.1
### Release   : 2018.01.16
##################################################################################################
### Resize clip with blackman algorithm.
##################################################################################################
def BlackmanResize(clip, w, h, depth=None):
	depth = Default(depth, clip.format.bits_per_sample)
	return GammaResize(input=clip, target_width=w, target_height=h, depth=depth, k='blackman', k_c='blackman')


##################################################################################################
### Function  : BlackmanminlobeResize
### Author    : ema
### Version   : v0.1
### Release   : 2018.01.16
##################################################################################################
### Resize clip with blackmanminlobe algorithm.
##################################################################################################
def BlackmanminlobeResize(clip, w, h, depth=None):
	depth = Default(depth, clip.format.bits_per_sample)
	return GammaResize(input=clip, target_width=w, target_height=h, depth=depth, k='blackmanminlobe', k_c='blackmanminlobe')


##################################################################################################
### Function  : Spline16Resize
### Author    : ema
### Version   : v0.1
### Release   : 2018.01.16
##################################################################################################
### Resize clip with spline16 algorithm.
##################################################################################################
def Spline16Resize(clip, w, h, depth=None):
	depth = Default(depth, clip.format.bits_per_sample)
	return GammaResize(input=clip, target_width=w, target_height=h, depth=depth, k='spline16', k_c='spline16')


##################################################################################################
### Function  : Spline36Resize
### Author    : ema
### Version   : v0.1
### Release   : 2018.01.16
##################################################################################################
### Resize clip with spline36 algorithm.
##################################################################################################
def Spline36Resize(clip, w, h, depth=None):
	depth = Default(depth, clip.format.bits_per_sample)
	return GammaResize(input=clip, target_width=w, target_height=h, depth=depth, k='spline36', k_c='spline36')


##################################################################################################
### Function  : Spline64Resize
### Author    : ema
### Version   : v0.1
### Release   : 2018.01.16
##################################################################################################
### Resize clip with spline64 algorithm.
##################################################################################################
def Spline64Resize(clip, w, h, depth=None):
	depth = Default(depth, clip.format.bits_per_sample)
	return GammaResize(input=clip, target_width=w, target_height=h, depth=depth, k='spline64', k_c='spline64')


##################################################################################################
### Function  : SplineResize
### Author    : ema
### Version   : v0.1
### Release   : 2018.01.16
##################################################################################################
### Resize clip with spline algorithm.
##################################################################################################
def SplineResize(clip, w, h, depth=None):
	depth = Default(depth, clip.format.bits_per_sample)
	return GammaResize(input=clip, target_width=w, target_height=h, depth=depth, k='spline', k_c='spline')


##################################################################################################
### Function  : GaussResize
### Author    : ema
### Version   : v0.1
### Release   : 2018.01.16
##################################################################################################
### Resize clip with gauss/gaussian algorithm.
##################################################################################################
def GaussResize(clip, w, h, depth=None):
	depth = Default(depth, clip.format.bits_per_sample)
	return GammaResize(input=clip, target_width=w, target_height=h, depth=depth, k='gauss', k_c='gauss')


##################################################################################################
### Function  : SincResize
### Author    : ema
### Version   : v0.1
### Release   : 2018.01.16
##################################################################################################
### Resize clip with sinc algorithm.
##################################################################################################
def SincResize(clip, w, h, depth=None):
	depth = Default(depth, clip.format.bits_per_sample)
	return GammaResize(input=clip, target_width=w, target_height=h, depth=depth, k='sinc', k_c='sinc')


##################################################################################################
### Function  : Nnedi3Resize
### Author    : ema
### Version   : v0.2
### Release   : 2018.01.24
##################################################################################################
### Resize clip with Nnedi3 using OpenCL.
###
### +----------------+
### |  REQUIREMENTS  |
### +----------------+
### -> libnnedi3.dll
### -> nnedi3_weights.bin
### -> NNEDI3CL.dll
##################################################################################################
def Nnedi3Resize(clip, w, h, cl=False, device=2, list_device=False):
	if cl:
		try:
			last = nncl.nnedi3_resample(input=clip, target_width=w, target_height=h, device=device, list_device=list_device)
		except:
			try:
				last = nncl.nnedi3_resample(input=clip, target_width=w, target_height=h, device=1, list_device=list_device)
			except:
				last = nncl.nnedi3_resample(input=clip, target_width=w, target_height=h, device=0, list_device=list_device)
	else:
		last = nnedi3_resample.nnedi3_resample(input=clip, target_width=w, target_height=h)
	return last


##################################################################################################
### Function  : Nnedi3aa
### Author    : ema
### Version   : v0.1
### Release   : 2018.01.17
##################################################################################################
### Modified Version of using NNEDI3CL from muvsfunc. 
### Read the document of Avisynth version for more details.
###
### +----------------+
### |  REQUIREMENTS  |
### +----------------+
### -> fmtconv.dll
### -> libnnedi3.dll
### -> nnedi3_weights.bin
### -> NNEDI3CL.dll
##################################################################################################
def Nnedi3aa(a, device=None, list_device=False):
	core = vs.get_core()
	funcName = 'Nnedi3aa'
	
	if not isinstance(a, vs.VideoNode):
		raise TypeError(funcName + ': \"a\" must be a clip!')

	bits = a.format.bits_per_sample
	
	last = Nnedi3(a, field=1, dh=True, device=device, list_device=list_device).std.Transpose()
	last = Nnedi3(last, field=1, dh=True, device=device, list_device=list_device).std.Transpose()
	last = core.fmtc.resample(last, a.width, a.height, [-0.5, -0.5 * (1 << a.format.subsampling_w)], [-0.5, -0.5 * (1 << a.format.subsampling_h)], kernel='spline36')

	if last.format.bits_per_sample == bits:
		return last
	else:
		return core.fmtc.bitdepth(last, bits=bits)


##################################################################################################
### Function  : Depth
### Author    : ema
### Version   : v0.1
### Release   : 2018.01.17
##################################################################################################
### Bit depth conversion.
###
### +----------------+
### |  REQUIREMENTS  |
### +----------------+
### -> mvsfunc.py
### 	-> Depth
### -> fmtconv.dll
##################################################################################################
def Depth(input, depth):
	return mvf.Depth(input=input, depth=depth)


##################################################################################################
### Function  : GradualMerge
### Author    : 787633258
### Version   : v0.1
### Release   : 2018.01.01
##################################################################################################
### Merge clipa and clipb gradually.
##################################################################################################
def GradualMerge(clipa, clipb):
	core = vs.get_core()
	length = len(clipa)
	depth = clipa.format.bits_per_sample
	mask = core.std.BlankClip(clipa[0], color=[1 / length * (2**depth - 1)] * clipa.format.num_planes)
	for i in range(2, length + 1):
		v = i / length * (2**depth - 1)
		maski = core.std.BlankClip(clipa[0], color=[v] * clipa.format.num_planes)
		mask += maski
	return core.std.MaskedMerge(clipa, clipb, mask)


##################################################################################################
### Function  : Dissolve
### Author    : ema
### Version   : v0.1
### Release   : 2018.01.01
##################################################################################################
### Dissolve is like AlignedSplice, except that the clips are combined with some overlap.
##################################################################################################
def Dissolve(clipa, clipb, overlap, fps=None):
	core = vs.get_core()
	if fps is not None:
		overlap = int(overlap * clipa.fps / fps)
	clipa_num_frames = clipa.num_frames - 1
	clipb_num_frames = clipb.num_frames - 1
	clipa_fadein = core.std.Trim(clipa, 0, clipa_num_frames - overlap - 1)
	clipa_fadeout = core.std.Trim(clipa, clipa_num_frames - overlap, clipa_num_frames)
	clipb_fadein = core.std.Trim(clipb, 0, overlap)
	clipb_fadeout = core.std.Trim(clipb, overlap + 1, clipb_num_frames)
	return clipa_fadein + GradualMerge(clipa_fadeout, clipb_fadein) + clipb_fadeout


##################################################################################################
### Function  : FadeIn
### Function  : FadeOut
### Function  : FadeIO
### Author    : ema
### Version   : v0.1
### Release   : 2018.01.01
##################################################################################################
### Causes the video stream to fade linearly to black at the start or end.
##################################################################################################
def FadeIn(clip, num_frames, color=[255, 255, 255], fps=None):
	core = vs.get_core()
	if fps is not None:
		num_frames = int(num_frames * clip.fps / fps)
	clip_fx, clip_nofx = SplitClip(clip, num_frames)
	clip_blank = core.std.BlankClip(clip_fx, color=color, format=vs.RGB24)
	clip_blank = core.resize.Bicubic(clip_blank, format=clip_fx.format.id, matrix_s='709')
	return GradualMerge(clip_blank, clip_fx) + clip_nofx

def FadeOut(clip, num_frames, color=[255, 255, 255], fps=None):
	core = vs.get_core()
	if fps is not None:
		num_frames = int(num_frames * clip.fps / fps)
	clip_nofx, clip_fx = SplitClip(clip, clip.num_frames - num_frames)
	clip_blank = core.std.BlankClip(clip_fx, color=color, format=vs.RGB24)
	clip_blank = core.resize.Bicubic(clip_blank, format=clip_fx.format.id, matrix_s='709')
	return clip_nofx + GradualMerge(clip_fx, clip_blank)

def FadeIO(clip, num_frames, color=[255, 255, 255], fps=None):
	core = vs.get_core()
	if fps is not None:
		num_frames = int(num_frames * clip.fps / fps)
	last = FadeIn(clip, num_frames, color=color, fps=fps)
	last = FadeOut(last, num_frames, color=color, fps=fps)
	return last

def SplitClip(clip, num_frames):
	core = vs.get_core()
	return [core.std.Trim(clip, 0, num_frames), core.std.Trim(clip, num_frames + 1, clip.num_frames - 1)]


##################################################################################################
### Function  : TurnLeft
### Function  : TurnRight
### Function  : Turn180
### Author    : ema
### Version   : v0.1
### Release   : 2018.01.01
##################################################################################################
### Turns the frames in a clip ±90,180 degrees.
##################################################################################################
def TurnLeft(clip):
	core = vs.get_core()
	last = core.std.Transpose(clip)
	last = core.std.FlipVertical(last)
	return last

def TurnRight(clip):
	core = vs.get_core()
	last = core.std.Transpose(clip)
	last = core.std.FlipHorizontal(last)
	return last

def Turn180(clip):
	core = vs.get_core()
	return core.std.Turn180(last)


##################################################################################################
### Function  : SelectEven
### Function  : SelectOdd
### Author    : ema
### Version   : v0.1
### Release   : 2018.01.01
##################################################################################################
### SelectEven : Return even numbered frames, starting with 0(clip[1::2]).
### SelectOdd  : Return odd  numbered frames, starting with 1(clip[0::2]).
###              Merger even and odd frames with core.std.Interleave([clip1,clip2]).
##################################################################################################
def SelectEven(clip):
	core = vs.get_core()
	return core.std.SelectEvery(clip=clip, cycle=2, offsets=0)

def SelectOdd(clip):
	core = vs.get_core()
	return SelectEvery(clip=clip, cycle=2, offsets=1)


##################################################################################################
### Funciton  : SelectHalf
### Author    : ema
### Version   : v0.1
### Release   : 2018.01.22
##################################################################################################
### VDecimate is a decimation filter.
### It drops one in every 2 frames.
##################################################################################################
def SelectHalf(clip):
	core = vs.get_core()
	return core.vivtc.VDecimate(clip, cycle=2)


##################################################################################################
### Function  : FrameType
### Author    : Frog
### Version   : v0.1
### Release   : 2018.01.01
##################################################################################################
### Display frame type, like 'I', 'P', 'B'.
##################################################################################################
def FrameType(clip):
	core = vs.get_core()
	avgclip = core.std.PlaneStats(clip, plane=0)
	mvsclip = mvf.PlaneStatistics(clip, plane=0)
	def avg(n, f, clip):
		atype = f.props._PictType
		type_dict = {73:'I', 80:'P', 66:'B'}
		type = type_dict.get(atype[0], 'Err')
		return vsq.Subtitle(clip, type)
	last = core.std.FrameEval(clip, functools.partial(avg, clip=clip, f=mvsclip), prop_src=avgclip)
	return last


##################################################################################################
### Function  : Nnedi3
### Author    : ema
### Version   : v0.2
### Release   : 2018.01.11
##################################################################################################
### NNEDI3 is an intra-field only deinterlacer.
### It takes in a frame, throws away one field, and then interpolates the missing pixels using only information from the kept field.
### It has same rate and double rate modes, and works with YV12, YUY2, and RGB24 input.
### NNEDI3 is also very good for enlarging images by powers of 2.
### 
### NNEDI3CL:  https://github.com/HomeOfVapourSynthEvolution/VapourSynth-NNEDI3CL
### nnedi3:    https://github.com/dubhater/vapoursynth-nnedi3
### 
### field [int, default: None]
### ------------------
###    Controls the mode of operation (double vs same rate) and which field is kept.
###       0 = same rate, keep bottom field
###       1 = same rate, keep top field
###       2 = double rate (alternates each frame), starts with bottom
###       3 = double rate (alternates each frame), starts with top
###
### dh [bint, default: False]
### ------------------
###     Doubles the height of the input.
###     Each line of the input is copied to every other line of the output and the missing lines are interpolated.
###     If field=0, the input is copied to the odd lines of the output.
###     If field=1, the input is copied to the even lines of the output. field must be set to either 0 or 1 when using dh=True.
###
### dw [bint, default: False]
### ------------------
###     >> Using when isCL = true.
###     Doubles the width of the input.
###     It does the same thing as Transpose().nnedi3(dh=True).Transpose() but also avoids unnecessary data copies when you scale both dimensions.
###
### device [int, default: 2]
### ------------------
###     >> Using when isCL = true.
###     Sets target OpenCL device.
###     Use list_device to get the index of the available devices.
###     By default the default device is selected.
###
### list_device [bint, default: False]
### ------------------
###     >> Using when isCL = true.
###     Whether the devices list is drawn on the frame.
###
### +----------------+
### |  REQUIREMENTS  |
### +----------------+
### -> libnnedi3.dll
### -> nnedi3_weights.bin
### -> NNEDI3CL.dll
##################################################################################################
def Nnedi3(clip, field, isCL=True, dh=False, dw=None, planes=None, nsize=6, nns=1, qual=1, etype=0, pscrn=2, device=None, list_device=False):
	core = vs.get_core()
	try:
		if isCL is True:
			dw = Default(dw, False)
			device = Default(device, 2)
			planes = Default(planes, [0, 1, 2])
			try:
				last = core.nnedi3cl.NNEDI3CL(clip=clip, field=field, dh=dh, dw=dw, planes=planes, nsize=nsize, nns=nns, qual=qual, etype=etype, device=device, list_device=list_device)
			except:
				try:
					device = 1
					last = core.nnedi3cl.NNEDI3CL(clip=clip, field=field, dh=dh, dw=dw, planes=planes, nsize=nsize, nns=nns, qual=qual, etype=etype, device=device, list_device=list_device)
				except:
					device = 0
					last = core.nnedi3cl.NNEDI3CL(clip=clip, field=field, dh=dh, dw=dw, planes=planes, nsize=nsize, nns=nns, qual=qual, etype=etype, device=device, list_device=list_device)
			return last
	except:
		planes = Default(planes, [0, 1, 2])
		return core.nnedi3.nnedi3(clip=clip, field=field, dh=dh, planes=planes, nsize=nsize, nns=nns, qual=qual, etype=etype, pscrn=pscrn)


##################################################################################################
### Function  : Yadifmod
### Author    : ema
### Version   : v0.1
### Release   : 2018.01.11
##################################################################################################
### Redesign ChangeFPS from havsfunc.py
### Enable float val when using fps.
###
### order [string, default: 'tff']
### ------------------
###    Sets the field order.
###    The filter will use the field order specified in the source frames and will only fall back to the specified order if not present.
###
### mode [int, default: 0]
### ------------------
###    Controls double rate vs same rate output, and whether or not the spatial interlacing check is performed.
###     0 = same rate, do spatial check
###     1 = double rate, do spatial check
###     2 = same rate, no spatial check
###     3 = double rate, no spatial check
###
### +----------------+
### |  REQUIREMENTS  |
### +----------------+
### -> libnnedi3.dll
### -> nnedi3_weights.bin
### -> NNEDI3CL.dll
##################################################################################################
def Yadifmod(src, order='tff', mode=0):
	core = vs.get_core()
	order = order.lower()
	if order == 'tff':
		last = core.yadifmod.Yadifmod(clip=src, edeint=Nnedi3(src, field=1), order=1, field=-1, mode=mode)
	elif order == 'bff':
		last = core.yadifmod.Yadifmod(clip=src, edeint=Nnedi3(src, field=0), order=0, field=-1, mode=mode)
	else:
		raise ValueError("Yadifmod: The expected value of order is 'tff' or 'bff'")
	return last


##################################################################################################
### Function  : ViewNoise
### Author    : Frog
### Version   : v0.1
### Release   : 2018.01.01
##################################################################################################
### View the clip noise.
##################################################################################################
def ViewNoise(clip, t=150, optmode=1):
	core = vs.get_core()
	d=clip.format.bits_per_sample
	clip = core.std.ShufflePlanes(clip, [0], colorfamily=vs.GRAY)
	if '16' not in clip.format.name:
		clip = mvf.Depth(clip,16)
	try:
		denoise = clip.knlm.KNLMeansCL( d=1, a=2, s=1, h=1.5, wmode=2, device_type='GPU', device_id=1)
	except:
		denoise = clip.knlm.KNLMeansCL( d=1, a=2, s=1, h=1.5, wmode=2, device_type='GPU', device_id=0)
	difference = core.std.Expr([clip,denoise],['x y - {0} >= 65535 0 ?'.format(t)])
	if optmode==1:
		try:
			return mvf.ToYUV(difference,full=False,css=clip.format.name[3:6],depth=clip.format.bits_per_sample)
		except:
			return mvf.ToYUV(difference,full=False,css='420',depth=d)
	else:
		return difference


##################################################################################################
### Function  : Default
### Author    : ema
### Version   : v0.1
### Release   : 2018.01.01
##################################################################################################
### Return the default val when it is none.
##################################################################################################
def Default(value, default_value):
	if value is None:
		return default_value
	return value


##################################################################################################
### Function  : Subtitle
### Author    : ema
### Version   : v0.1
### Release   : 2018.01.01
##################################################################################################
###	Using like the Avisynth function Subtitle.
###
### an [int, default: 7] 
### ------------------
###    The alignment parameter takes a number from 1 to 9, corresponding to the positions of the keys on a numpad.
##################################################################################################
def Subtitle(src, text, an=7):
	core = vs.get_core()
	src = core.text.Text(src, str(text), alignment=an)
	return src


##################################################################################################
### Function  : MediaInfo
### Author    : ema
### Version   : v0.1
### Release   : 2018.05.26
##################################################################################################
###	Show media information in the clip.
###
### an [int, default: 7] 
### ------------------
###    The alignment parameter takes a number from 1 to 9, corresponding to the positions of the keys on a numpad.
##################################################################################################
def MediaInfo(src, path, full=False, an=7):
	import mediainfo as mi
	return Subtitle(src, text=mi.MediaInfo(inpath=path, full=full), an=an)


##################################################################################################
### Function  : OverlayM
### Author    : ema
### Version   : v0.1
### Release   : 2018.01.01
##################################################################################################
### Auto resize the given clip and to be overlay in a blankclip of center.
### M is the initial of Mannaka, means center in Japanese.
###
### color [[int, int, int], default(White) : [255, 255, 255]]
### ------------------
###     Background Color.
###
### +----------------+
### |  REQUIREMENTS  |
### +----------------+
### -> havsfunc.py
###		-> Overlay
##################################################################################################
def OverlayM(src, w, h, color=[255, 255, 255]):
	core = vs.get_core()
	fps = src.fps
	dec = 1000
	blank = core.std.BlankClip(length=src.num_frames, width=w, height=h, color=color, fpsnum=int(fps*dec), fpsden=dec, format=vs.RGB24)
	blank = ConvertToYV12(blank)
	src_w = src.width
	src_h = src.height
	src_sar = src_w / src_h
	sar = w / h
	isRW = False
	if src_sar > sar:
		isRW = True
	w_target = round(src_w * h / src_h)
	h_target = h
	if isRW:
		w_target = w
		h_target = round(src_h * w / src_w)
	src = core.resize.Lanczos(src, w_target, h_target)
	x = w / 2 - w_target / 2
	y = 0
	if isRW:
		x = 0
		y = h / 2 - h_target / 2
	return haf.Overlay(blank, src, x=int(x), y=int(y))


##################################################################################################
### Function  : ConvertToYV24
### Function  : ConvertToYV16
### Function  : ConvertToYUY2
### Function  : ConvertToYV12
### Function  : ConvertToYV411
### Function  : ConvertToY8
### Function  : ConvertToRGB24
### Function  : ConvertToRGB48
### Function  : ConvertToRGBS
### Function  : ConvertToGrey
### Function  : ConvertToGray
### Function  : ConvertTo
### Author    : ema
### Version   : v0.1
### Release   : 2018.01.01
##################################################################################################
### Format constants exactly describe a format.
###
### The Avisynth YUV color formats:
### ------------------
### 	Color_format	Image_format	Chroma_resolution
### 	YV24			planar			4:4:4 (full chroma)
### 	YV16			planar			4:2:2 (chroma shared between 2 horizontal pixels)
### 	YUY2			interleaved		4:2:2 (chroma shared between 2 horizontal pixels)
### 	YV12			planar			4:2:0 (chroma shared between 2 horizontal x 2 vertical pixels) 
### 	YV411			planar			4:1:1 (chroma shared between 4 vertical pixels)
### 	Y8				(both)			4:0:0 (no chroma but IsYUV returns true)
###
### Interleaved:
### ------------------
###     Interleaved image format is a format for storing images where all color components needed to
###     represent a pixel are placed at the same place in memory.
###     This is in contrast with how planar images are stored in memory.
###
### Color Family Constants:
### ------------------
###    RGB  YUV  GRAY  YCOCG  COMPAT
###
### Format Constants:
### ------------------
###    GRAY8, 	  GRAY16, 	 GRAYH, 	GRAYS
###    YUV420P8,  YUV422P8,  YUV444P8,  YUV410P8, YUV411P8, YUV440P8
###    YUV420P9,  YUV422P9,  YUV444P9
###    YUV420P10, YUV422P10, YUV444P10
###    YUV420P12, YUV422P12, YUV444P12
###    YUV420P14, YUV422P14, YUV444P14
###    YUV420P16, YUV422P16, YUV444P16
###    YUV444PH,  YUV444PS
###    RGB24, RGB27, RGB30, RGB48, RGBH, RGBS
###    COMPATBGR32, COMPATYUY2
##################################################################################################
def ConvertToYV24(clip):
	core = vs.get_core()
	return mvf.ToYUV(clip, css='444')

def ConvertToYV16(clip):
	core = vs.get_core()
	return mvf.ToYUV(clip, css='422')

def ConvertToYUY2(clip):
	core = vs.get_core()
	return core.resize.Bicubic(clip=clip, format=vs.COMPATYUY2)

def ConvertToYV12(clip):
	core = vs.get_core()
	return mvf.ToYUV(clip, css='420')

def ConvertToYV411(clip):
	core = vs.get_core()
	return core.resize.Bicubic(clip=clip, format=vs.YUV411P8)

def ConvertToY8(clip):
	core = vs.get_core()
	return core.std.ShufflePlanes(clips=clips, planes=0, colorfamily=vs.GRAY)
	
def ConvertToRGB24(clip, matrix='709'):
	core = vs.get_core()
	return core.resize.Bicubic(clip=clip, format=vs.RGB24, matrix_in_s=matrix)

def ConvertToRGB48(clip, matrix='709'):
	core = vs.get_core()
	return core.resize.Bicubic(clip=clip, format=vs.RGB48, matrix_in_s=matrix)

def ConvertToRGBS(clip, matrix='709'):
	core = vs.get_core()
	return core.resize.Bicubic(clip=clip, format=vs.RGBS, matrix_in_s=matrix)

def ConvertToGrey(clips=[]):
	core = vs.get_core()
	return core.std.ShufflePlanes(clips=clips, planes=0, colorfamily=vs.GRAY)

def ConvertToGray(clips=[]):
	core = vs.get_core()
	return core.std.ShufflePlanes(clips=clips, planes=0, colorfamily=vs.GRAY)

def ConvertTo(clip, format, matrix=None):
	core = vs.get_core()
	return core.resize.Bicubic(clip=clip, format=format, matrix_in_s=matrix)


##################################################################################################
### Function  : IsRGB
### Function  : IsYUV
### Function  : IsYV24
### Function  : IsYV12
### Author    : ema
### Version   : v0.1
### Release   : 2018.02.04
##################################################################################################
### Clip format simple checker.
##################################################################################################
def IsRGB(clip):
	return clip.format.name.startswith('RGB')

def IsYUV(clip):
	return clip.format.name.startswith('YUV')

def IsYV24(clip):
	return clip.format.name.startswith('YUV444')

def IsYV12(clip):
	return clip.format.name.startswith('YUV420')


##################################################################################################
### Function  : SwapUV
### Function  : UToY
### Function  : VToY
### Author    : ema
### Version   : v0.1
### Release   : 2018.01.16
##################################################################################################
### Swap U and V in (Cast)YUV.
### Copies U or V chroma plane to the Y luma plane.
##################################################################################################
def SwapUV(clip=[]):
	core = vs.get_core()
	return core.std.ShufflePlanes(clips=clip, planes=[0, 2, 1], colorfamily=vs.YUV)

def UToY(clip=[]):
	core = vs.get_core()
	return core.std.ShufflePlanes(clips=clip, planes=[0, 0, 2], colorfamily=vs.YUV)

def VToY(clip=[]):
	core = vs.get_core()
	return core.std.ShufflePlanes(clips=clip, planes=[0, 1, 1], colorfamily=vs.YUV)


##################################################################################################
### Function  : ChangeFPS
### Author    : ema
### Version   : v0.2
### Release   : 2018.01.01
##################################################################################################
### Redesign ChangeFPS from havsfunc.py
### Enable float val when using fps.
###
### fps [float]
### ------------------
###    FrameRate.
###
### +----------------+
### |  REQUIREMENTS  |
### +----------------+
### -> havsfunc.py
###		-> ChangeFPS
##################################################################################################
def ChangeFPS(src, fps, dec=None):
	dec = Default(dec, 1000)
	return haf.ChangeFPS(src, fpsnum=int(fps*dec), fpsden=dec)


##################################################################################################
### Function  : ChangeFPS
### Author    : ema
### Version   : v0.2
### Release   : 2018.01.01
##################################################################################################
### Redesign ChangeFPS from havsfunc.py
### Enable float val when using fps.
###
### fps [float]
### ------------------
###    FrameRate.
###
### +----------------+
### |  REQUIREMENTS  |
### +----------------+
### -> havsfunc.py
###		-> ChangeFPS
##################################################################################################
def AssumeFPS(src, fps, dec=None):
	core = vs.get_core()
	dec = Default(dec, 1000)
	return core.std.AssumeFPS(src, fpsnum=int(fps*dec), fpsden=dec)


##################################################################################################
### Function  : Crop
### Author    : ema
### Version   : v0.1
### Release   : 2018.01.11
##################################################################################################
### Crops the frames in a clip.
###
### auto [bint, Default: False]
### ------------------
###    Do autocrop with autocrop plugin func.
###    Ignore parameters of 'l', 't', 'r', 'b' when true.
###
### +----------------+
### |  REQUIREMENTS  |
### +----------------+
### -> autocrop.dll
##################################################################################################
def Crop(src, l=0, t=0, r=0, b=0, auto=False, range=1000):
	core = vs.get_core()
	if auto:
		last = core.acrop.AutoCrop(src, range=range)
	else:
		last = core.std.Crop(src, left=abs(l), top=abs(t), right=abs(r), bottom=abs(b))
	return last


##################################################################################################
### Function  : StackVertical
### Function  : StackHorizontal
### Author    : ema
### Version   : v0.1
### Release   : 2018.01.14
##################################################################################################
### Stacks all given clips together.
##################################################################################################
def StackVertical(clips=[]):
	core = vs.get_core()
	return core.std.StackVertical(clips)

def StackHorizontal(clips=[]):
	core = vs.get_core()
	return core.std.StackHorizontal(clips)


##################################################################################################
### Function  : QTGMC
### Author    : ema
### Version   : v0.1
### Release   : 2018.01.14
##################################################################################################
### A high quality deinterlacer using motion-compensated temporal smoothing, 
### with a range of features for quality and convenience.
###
### Preset [str, Default: 'Slow']
### ------------------
###    The Preset used selects sensible settings for a given encoding speed.
###    Choose a preset from:
###        'Placebo', 'Very Slow', 'Slower', 'Slow', 'Medium', 
###        'Fast", 'Faster', 'Very Fast', 'Super Fast',
###        'Ultra Fast' & 'Draft'
###
### FPSDivisor [int, Default: 1] (1,2...)
### ------------------
###		1 = Double-rate output,
###		2 = Single-rate output.
###		Higher values can be used too (e.g. 60fps & FPSDivisor=3 gives 20fps output).
###		Important: You do not need SelectEven() in the calling script if you use FPSDivisor=2.
###
### +----------------+
### |  REQUIREMENTS  |
### +----------------+
### -> havsfunc.py
### 	-> MVTools
### 	-> znedi3
### 	-> RGVS
### 	-> fmtconv
##################################################################################################
def QTGMC(src, Preset='slow', TFF=True, FPSDivisor=2, opencl=False):
	return haf.QTGMC(src, Preset=Preset, TFF=TFF, FPSDivisor=FPSDivisor, opencl=opencl)


##################################################################################################
### Function  : JudgeMatrix
### Author    : ema
### Version   : v0.1
### Release   : 2018.08.13
##################################################################################################
### Judge matrix of input clip.
##################################################################################################
def JudgeMatrix(a, b):
	if a <= 1024 and b <= 576:
		return "601"
	elif a <= 2048 and b <= 1536:
		return "709"
	else:
		return "2020"


##################################################################################################
### Function  : Diff
### Author    : ema
### Version   : v0.1
### Release   : 2017.08.17
##################################################################################################
### A filter to check the difference of source clip and filtered clip.
###
### noise [bint, Default: False]
### ------------------
###    Diff noise.
###
### power [float, Default: 1.5]
### ------------------
###    The variable in the processing kernel which controls the "strength" to increase difference.
###
### chroma [bint, Default: False]
### ------------------
###    Whether to process chroma.
###
### mode [bint, Default: 2]
### ------------------
###    Different processing kernel.
###    mode = 1: non-linear
###    mode = 2: linear
###
### +----------------+
### |  REQUIREMENTS  |
### +----------------+
### -> muvsfunc.py
### 	-> Compare
##################################################################################################
def Diff(src, flt, noise=False, stack=False, power=1.5, chroma=False, mode=2):
	if noise:
		src = ViewNoise(src)
		flt = ViewNoise(flt)
	if stack:
		diff = StackVertical([src, flt])
	else:
		diff = muvf.Compare(src, flt, power=power, chroma=chroma, mode=mode)
	return diff


##################################################################################################
### Function  : D2VSource
### Author    : ema
### Version   : v0.1
### Release   : 2018.01.20
##################################################################################################
### D2V Witch indexes MPEG (1, 2) streams and writes D2V files.
###
### path [str]
### ------------------
###    The path of input clip.
###
### dir [str, Default: None]
### ------------------
###    The dir of d2vwitch.
###    Get from qvs.conf -> 'python' : 'd2v'.
###
### audio [bint, Default: True]
### ------------------
###    Demux all of audio from clip file.
###    D2VWitch Options: --audio-ids "all".
###
### d2v_out [str, Default: path + '.d2v']
### ------------------
###    The path of output d2v file.
###
### index_bin [str, Default: 'd2vwitch']
### ------------------
###    The path of d2v index exec file.
###
### force_index [bint, Default: False]
### ------------------
###    Force to do index when true.
###
### nocrop [bint, Default: True]
### ------------------
###    Always use direct-rendered buffer, which may need cropping.
###    Provides a speedup when you know you need to crop your image anyway, by avoiding extra memcpy calls.
###
### rff [bint, Default: False]
### ------------------
###    Invoke ApplyRFF.
###
### threads [int, Default: 0(auto)]
### ------------------
###    Number of threads FFmpeg should use.
###
### D2VWitch Usage:
### ------------------
###    d2vwitch [options] input_file1 input_file2 ...
###
### D2VWitch Options:
### ------------------
###    --help
###        Display this message.
###
###    --version
###        Display version numbers and ffmpeg configuration.
###
###    --info
###        Display relevant information about the input file(s), such as a
###        list of all the video and audio tracks and their ids.
###
###    --quiet
###        Do not print progress information or warnings. Fatal errors are
###        always printed.
###
###    --output <d2v name>
###        Specify the name of the D2V file. The special name "-" means
###        standard output. If not specified, the name of the D2V file is
###        deduced from the name of the first input file.
###
###    --audio-ids <id1,id2,...>
###        Demux the audio tracks with the specified ids. The special
###        value "all" means that all audio tracks should be demuxed. By
###        default, no audio tracks are demuxed. The names of the audio
###        files are deduced from the name of the D2V file.
###
###    --video-id <id>
###        Process the video track with this id. By default, the first
###        video track found will be processed.
###
###    --input-range <range>
###        Set the YUVRGB_Scale field in the d2v file according to the
###        video's input colour range. Possible values are "limited" and
###        "full". By default, the video is assumed to have limited range.
###
### +----------------+
### |  REQUIREMENTS  |
### +----------------+
### -> d2vsource.dll
##################################################################################################
def D2VSource(path, dir=None, index_bin='d2vwitch', audio=True, d2v_out=None, force_index=False, nocrop=True, rff=False, threads=0):
	core = vs.get_core()
	bin_path = GetConfig(section='python', options='d2v')
	dir = Default(dir, bin_path)
	if index_bin == 'd2vwitch':
		index_bin = '{dir}/{index_bin}'.format(dir=dir, index_bin=index_bin)
	if audio:
		audio_options = '--audio-ids "all"'
	else:
		audio_options = ''
	d2v_out = Default(d2v_out, path+'.d2v')
	if (not os.path.isfile(d2v_out)) | (force_index):
		print('DGIndex: {d2v_out}'.format(d2v_out=d2v_out))
		cmd = '{index_bin} {audio_options} --output "{d2v_out}" "{path}"'.format(index_bin=index_bin, audio_options=audio_options, d2v_out=d2v_out, path=path)
		print(cmd)
		subprocess.run(cmd, shell=True)
	last = core.d2v.Source(input=d2v_out, threads=threads, nocrop=nocrop, rff=True)
	if rff:
		last = core.d2v.ApplyRFF(last, d2v=d2v_out)
	return last


##################################################################################################
### Function  : DGSource
### Author    : ema
### Version   : v0.1
### Release   : 2018.01.20
##################################################################################################
### DGIndex indexes MPEG (1, 2) streams and writes D2V files.
###
### path [str]
### ------------------
###    The path of input clip.
###
### dir [str, Default: None]
### ------------------
###    The dir of DGIndex.
###    Get from qvs.conf -> 'python' : 'dg'.
###
### audio [bint, Default: True]
### ------------------
###    Demux all of audio from clip file.
###    D2VWitch Options: --audio-ids "all".
###
### d2v_out [str, Default: path]
### ------------------
###    The path of output d2v file.(auto output with a name of path + '.d2v')
###
### index_bin [str, Default: 'DGIndex']
### ------------------
###    The path of d2v index exec file.
###
### force_index [bint, Default: False]
### ------------------
###    Force to do index when true.
###
### nocrop [bint, Default: True]
### ------------------
###    Always use direct-rendered buffer, which may need cropping.
###    Provides a speedup when you know you need to crop your image anyway, by avoiding extra memcpy calls.
###
### threads [int, Default: 0(auto)]
### ------------------
###    Number of threads FFmpeg should use.
###
### field_operation [int, Default: 0]
### ------------------
###    Field Operation.
###       0=Honor Pulldown Flags,
###       1=Force Film,
###       2=Ignore Pulldown Flags.
###
### options [str, Default: '']
### ------------------
###    Options of DGIndex.
###
### log [bint, Default: False]
### ------------------
###    Auto remove the log and info files,like *.log and *.fix.txt.
###
### bad [bint, Default: True]
### ------------------
###    True : Using *.d2v.bad when it exists.
###    False: Not using *.d2v.bad but not remove it.
###
### +----------------+
### |  REQUIREMENTS  |
### +----------------+
### -> d2vsource.dll
##################################################################################################
def DGSource(path, dir=None, index_bin='DGIndex', d2v_out=None, force_index=False, nocrop=True, threads=0, field_operation=0, options='', log=False, bad=True):
	core = vs.get_core()
	bin_path = GetConfig(section='python', options='dg')
	dir = Default(dir, bin_path)
	if index_bin == 'DGIndex':
		index_bin = '{dir}/{index_bin}'.format(dir=dir, index_bin=index_bin)
	if field_operation != 0:
		options = '{options} -fo={field_operation}'.format(options=options, field_operation=field_operation)
	else:
		options = '{options} -hide -exit'.format(options=options)
	d2v_out = Default(d2v_out, path)
	if path.split('.')[-1].lower() == 'd2v':
		return core.d2v.Source(input=path, threads=threads, nocrop=nocrop, rff=True)
	if (not os.path.isfile(d2v_out+'.d2v')) | (force_index):
		print('DGIndex: {d2v_out}'.format(d2v_out=d2v_out+'.d2v'))
		cmd = '{index_bin} -i "{path}" -o "{d2v_out}" {options}'.format(index_bin=index_bin, d2v_out=d2v_out, path=path, options=options)
		print(cmd)
		subprocess.run(cmd, shell=True)
		if bad:
			if os.path.isfile(d2v_out+'.d2v.bad'):
				print('DGIndex: Auto using {d2v_out}'.format(d2v_out=d2v_out+'.d2v.bad'))
				try:
					os.remove(d2v_out+'.d2v')
					os.rename(d2v_out+'.d2v.bad', d2v_out+'.d2v')
				except:
					pass
		if not log:
			try:
				os.remove(RemoveFileExt(d2v_out)+'.log')
				os.remove(d2v_out+'.fix.txt')
			except:
				pass
	return core.d2v.Source(input=d2v_out+'.d2v', threads=threads, nocrop=nocrop, rff=True)


##################################################################################################
### Function  : DGSourceNV
### Author    : ema
### Version   : v0.1
### Release   : 2018.01.21
##################################################################################################
### DGIndexNV, part of the DGDecNV package, is primarily designed to create an index of an AVC/HEVC/MPG/VC1 video stream, 
### containing the location of each frame in the input stream, and some additional information about each frame. 
### This index, or project file, is used by the companion Avisynth filter DGDecodeNV to provide frame-accurate serving of the video via an Avisynth script. 
### DGDecNV can also be used with Vapoursynth because Vapoursynth can load and use Avisynth source filters. 
### DGIndexNV can open AVC/HEVC/MPG/VC1 video in elementary streams, and in program, transport, Matroska, and MP4 containers.
### 
### path [str]
### ------------------
###    The path of input clip.
###
### dir [str, Default: None]
### ------------------
###    The dir of DGIndexNV.
###    Get from qvs.conf -> 'python' : 'dgnv'.
###
### audio [bint, Default: True]
### ------------------
###    Demux all of audio from clip file.
###    D2VWitch Options: --audio-ids "all".
###
### dgi_out [str, Default: path]
### ------------------
###    The path of output dgi file.(auto output with a name of path + '.dgi')
###
### index_bin [str, Default: 'DGIndexNV']
### ------------------
###    The path of dgi index exec file.
###
### force_index [bint, Default: False]
### ------------------
###    Force to do index when true.
###
### options [str, Default: '']
### ------------------
###    Options of DGIndex.
###
### log [bint, Default: False]
### ------------------
###    Auto remove the log and info files,like *.log and *.fix.txt.
###
### bad [bint, Default: True]
### ------------------
###    True : Using *.dgi.bad when it exists.
###    False: Not using *.dgi.bad but not remove it.
###
### i420 [bint, Default: False]
### ------------------
###    Deliver i420 instead of YV12.
###
### deinterlace [int, Default: 0]
### ------------------
###    Nvidia PureVideo Deinterlacer
###     0: no deinterlacing
###     1: single rate deinterlacing
###     2: double rate deinterlacing (bobbing)
###
### use_top_field [bint, Default: True]
### ------------------
###    Use the top field for single rate deinterlacing.
###    When this parameter is true, the top field is used for single rate deinterlacing;
###    When false the bottom field is used. When deinterlace=0 or deinterlace=2, this parameter is ignored.
###
### use_pf [bint, Default: False]
### ------------------
###    Use the progressive_frame indication from NVCUVID.
###    If deinterlace=1 or deinterlace=2, and use_pf=true, then only frames marked as interlaced by NVCUVID will be deinterlaced.
###    If deinterlace=1 or deinterlace=2, and use_pf=false, then all frames will be deinterlaced.
###
### crop_t/crop_b/crop_l/crop_r [int, Default: 0]
### ------------------
###    Use the GPU to crop the video.
###    Any non-zero value for one of these parameters overrides any cropping that may have been defined in DGIndexNV for that value.
###    These options give you the flexibility to define GPU cropping either in DGIndexNV or in the DGSource() parameters.
###
### resize_w/resize_h [int, Default: 0]
### ------------------
###    Use the GPU to resize the video. The resizing is applied after deinterlacing.
###    If either resize_w or resize_h is 0, no resizing is performed.
###    If you need to crop before resizing, use the cropping filter in DGIndexNV, or the crop_t/b/l/r parameters described above.
###
### fieldop [int, Default: 0]
### ------------------
###    0: Honor Pulldown Flags
###    1: Force Film
###    2: Ignore Pulldown Flags
###
### show [bint, Default: False]
### ------------------
###    Enable textual information overlay on the output video frames.
###    Currently the information displayed is the DGDecodeNV version number, the GOP number, the display and coded frame numbers, and the frame coding type.
###    Note that if leading orphaned B frames exist at the beginning of the stream, they are replaced with copies of the first I frame, and so the overlay will show data for the first I frame for each of the leading orphaned B frames.
###    Also note that the frame numbers appropriately reflect the setting of the fieldop option.
###
### fulldepth [bint, Default: False]
### ------------------
###    When fulldepth=true and the encoded video is HEVC 10-bit or 12-bit, then DGSource() delivers 16-bit data to Avisynth with the unused lower bits zeroed.
###    The reported pixel format is CS_YUV420P16.
###    If either of the two conditions are not met, then DGSource() delivers 8-bit YV12 or I420 data, as determined by the i420 parameter.
###    When fulldepth=false and the video is HEVC 10-bit or 12-bit, then the video is dithered down to 8-bit for delivery.
###    If you need a reduced color space (less than 16 bits) for your high-bit-depth processing, you can use ConvertBits() as needed after your DGSource() call.
###
### +----------------+
### |  REQUIREMENTS  |
### +----------------+
### -> DGDecodeNV.dll
###    -> license.txt
##################################################################################################
def DGSourceNV(path, dir=None, index_bin='DGIndexNV', audio=True, dgi_out=None, force_index=False, options='', log=False, bad=True,
				plugin_path='', core=None, i420=False, deinterlace=0, use_top_field=True, use_pf=False, 
				crop_t=0, crop_b=0, crop_l=0, crop_r=0, resize_w=0, resize_h=0, fieldop=0, show=False, fulldepth=False):
	core = Default(core, vs.get_core())
	bin_path = GetConfig(section='python', options='dgnv')
	dir = Default(dir, bin_path)
	#raise TypeError(bin_path)
	if (index_bin == 'DGIndexNV') & (dir != ''):
		index_bin = '{dir}/{index_bin}'.format(dir=dir, index_bin=index_bin)

	if not core is None:
		if not CheckRegFunc('DGSource'):
			SetWorkingDir(core=core, path=dir, isAvs=True)
	
	if audio:
		options = '{options} -a'.format(options=options)
	options = '{options} -h -e'.format(options=options)
	dgi_out = Default(dgi_out, path)
	
	if (not os.path.isfile(dgi_out+'.dgi')) | (force_index):
		print('DGIndexNV: {dgi_out}'.format(dgi_out=dgi_out+'.dgi'))
		cmd = '{index_bin} -i "{path}" -o "{dgi_out}" {options}'.format(index_bin=index_bin, dgi_out=dgi_out, path=path, options=options)
		print(cmd)
		subprocess.run(cmd)
		if bad:
			if os.path.isfile(dgi_out+'.dgi.bad'):
				print('DGIndexNV: Auto using {dgi_out}'.format(dgi_out+'.dgi.bad'))
				try:
					os.remove(dgi_out+'.dgi')
					os.rename(dgi_out+'.dgi.bad', dgi_out+'.dgi')
				except:
					pass
		if not log:
			try:
				os.remove(RemoveFileExt(dgi_out)+'.log')
				os.remove(dgi_out+'.fix.txt')
			except:
				pass
	return core.avs.DGSource(dgi=dgi_out+'.dgi', i420=i420, deinterlace=deinterlace, use_top_field=use_top_field, use_pf=use_pf, crop_t=crop_t, crop_b=crop_b, crop_l=crop_l, crop_r=crop_r,resize_w=resize_w, resize_h=resize_h, fieldop=fieldop, show=show, fulldepth=fulldepth)


##################################################################################################
### Function  : DGSourceIM
### Author    : ema
### Version   : v0.1
### Release   : 2018.01.21
##################################################################################################
### !!! It's very likely that can't work in the vapoursynth environment !!!
### DGIndexNV can be used to make the index file if desired, as DGDecodeIM
### can read the DGIndexNV DGI file. The only caveat is that the CLIP line is
### ignored, so you cannot use cropping in DGIndexNV.
###
### path [str]
### ------------------
###    The path of input clip.
###
### dir [str, Default: None]
### ------------------
###    The dir of DGIndexIM.
###    Get from qvs.conf -> 'python' : 'dgim'.
###
### audio [bint, Default: True]
### ------------------
###    Demux all of audio from clip file.
###    D2VWitch Options: --audio-ids "all".
###
### dgi_out [str, Default: path]
### ------------------
###    The path of output dgi file.(auto output with a name of path + '.dgi')
###
### index_bin [str, Default: 'DGIndexIM']
### ------------------
###    The path of dgi index exec file.
###
### force_index [bint, Default: False]
### ------------------
###    Force to do index when true.
###
### options [str, Default: '']
### ------------------
###    Options of DGIndex.
###
### log [bint, Default: False]
### ------------------
###    Auto remove the log and info files,like *.log and *.fix.txt.
###
### bad [bint, Default: True]
### ------------------
###    True : Using *.dgi.bad when it exists.
###    False: Not using *.dgi.bad but not remove it.
###
### engine [int, Default: 2]
### ------------------
###    engine = 0: Intel automatic (uses HW if available, otherwise uses SW)
###    engine = 1: Intel HW
###    engine = 2: Intel SW
###
### +----------------+
### |  REQUIREMENTS  |
### +----------------+
### -> DGDecodeIM.dll
###    -> libmfxsw32.dll or libmfxsw64.dll
##################################################################################################
def DGSourceIM(path, dir=None, index_bin='DGIndexIM', audio=True, dgi_out=None, force_index=False, options='', log=False, bad=True,
				core=None, engine=2, debug=False):
	core = Default(core, vs.get_core())
	bin_path = GetConfig(section='python', options='dgim')
	dir = Default(dir, bin_path)
	if (index_bin == 'DGIndexIM') & (dir != ''):
		index_bin = '{dir}/{index_bin}'.format(dir=dir, index_bin=index_bin)
	if not core is None:
		if not CheckRegFunc('DGSourceIM'):
			SetWorkingDir(core=core, path=dir, isAvs=True)
	
	if audio:
		options = '{options} -a'.format(options=options)
	options = '{options} -hide -exit'.format(options=options)
	dgi_out = Default(dgi_out, path+'.dgi')
	
	if (not os.path.isfile(dgi_out)) | (force_index):
		print('DGIndexIM: {dgi_out}'.format(dgi_out=dgi_out))
		cmd = '{index_bin} -i "{path}" -o "{dgi_out}" {options}'.format(index_bin=index_bin, dgi_out=dgi_out, path=path, options=options)
		print(cmd)
		subprocess.run(cmd)
		if bad:
			if os.path.isfile(dgi_out+'.dgi.bad'):
				print('DGIndexIM: Auto using {dgi_out}'.format(dgi_out+'.bad'))
				try:
					os.remove(dgi_out)
					os.rename(dgi_out+'.bad', dgi_out)
				except:
					pass
		if not log:
			try:
				os.remove(RemoveFileExt(dgi_out)+'.log')
				os.remove(dgi_out+'.fix.txt')
			except:
				pass
	return core.avs.DGSourceIM(dgi=dgi_out, engine=engine, debug=debug)

##################################################################################################
### Function  : VIVTC
### Author    : ema
### Version   : v0.1
### Release   : 2018.08.14
##################################################################################################
### Inverse telecine (IVTC) (for hard 3:2 pulldown).
###
### clip [clip]
### ------------------
###		Input clip. YUV420P8, YUV422P8, YUV440P8, YUV444P8, and GRAY8 are supported.
###		Must have constant format and dimensions.
###
### order [int, Default: 1]
### ------------------
### 	Sets the field order of the clip.
### 	Normally the field order is obtained from the _FieldBased frame property.
### 	This parameter is only used for those frames where the _FieldBased property has an invalid value or doesn’t exist.
### 	If the field order is wrong, VFM’s output will be visibly wrong in mode 0.
### 		0 - bottom field first
### 		1 - top field first
##################################################################################################
def VIVTC(clip, order=1):
	last = core.vivtc.VFM(clip, order=order)
	last = core.vivtc.VDecimate(last)
	return last


##################################################################################################
### Function  : DGIVTC
### Author    : ema
### Version   : v0.1
### Release   : 2018.01.21
##################################################################################################
### Inverse telecine (IVTC) (for hard 3:2 pulldown).
###
### dir [str, Default: None]
### ------------------
###    The dir of DGIndexNV.
###    Get from qvs.conf -> 'python' : 'dgnv'.
###
### pthresh [float, Default: 3.5]
### ------------------
###    Threshold for postprocessing.
###    If the metric for a matched frame exceeds pthresh, the frame will be deinterlaced.
###    Use the show option to see the metrics and thereby set an appropriate pthresh value.
###    Postprocessing applies only to frames with no good match and it allows DGTelecide() to deliver reasonable looking frames in such instances. 
###
### device [int, Default: 255]
### ------------------
###    When set to 255, the first GPU found is used.
###    When set to any other value the GPU with that ordinal value is used.
###
### +----------------+
### |  REQUIREMENTS  |
### +----------------+
### -> DGDecodeNV.dll
###    -> license.txt
##################################################################################################
def DGIVTC(src, dir=None, core=None, pthresh=3.5, device=255):
	core = Default(core, vs.get_core())
	bin_path = GetConfig(section='python', options='dgnv')
	dir = Default(dir, bin_path)
	if not core is None:
		if (not CheckRegFunc('DGTelecide')) & (not CheckRegFunc('DGDecimate')):
			SetWorkingDir(core=core, path=dir, isAvs=True)
	last = core.avs.DGTelecide(src, mode=1, pthresh=pthresh, device=device)
	last = core.avs.DGDecimate(last, device=device)
	return last


##################################################################################################
### Function  : DGDenoise
### Author    : ema
### Version   : v0.1
### Release   : 2018.01.24
##################################################################################################
### DGDenoise() is a fast stand-alone CUDA filter that implements NLM denoising.
### The input clip must be in the YV12 format.
###
### dir [str, Default: None]
### ------------------
###    The dir of DGIndexNV.
###    Get from qvs.conf -> 'python' : 'dgnv'.
###
### strength [float, Default: 0.15]
### ------------------
###    Strength of the Non-Local Means (NLM) denoising.
###    Typical values for strength are in the range 0.1-1.0.
###    Note that if you have interlaced source you should deinterlace with deinterlace=1 or deinterlace=2.
###    If you have hard pulldown, or you have soft pulldown that is being honored, then invoke it through DGDenoise() after performing external IVTC.
###    The essential point to remember is that denoising should be applied to progressive frames.
###    If you must retain interlacing, then separate the fields, apply DGDenoise(), and then re-weave the fields.
###
### blend [float, Default: 0.1]
### ------------------
###    Blending coefficient for the NLM denoising with range 0.0 to 1.0.
###    Use lower values to blend in less of the original pixel.
###
### chroma [bint, Default: True]
### ------------------
###    When set to true NLM denoising is applied to the chroma as well as the luma.
###
### searchw [int, Default: 5, range 5/7/9]
### ------------------
###    Width of the search window for the NLM denoising.
###    Wider windows may improve quality at the expense of speed.
###
### device [int, Default: 255]
### ------------------
###    When set to 255, the first GPU found is used.
###    When set to any other value the GPU with that ordinal value is used.
###
### +----------------+
### |  REQUIREMENTS  |
### +----------------+
### -> DGDecodeNV.dll
###    -> license.txt
##################################################################################################
def DGDenoise(src, dir=None, core=None, strength=0.15, blend=0.1, chroma=True, searchw=5, device=255):
	core = Default(core, vs.get_core())
	bin_path = GetConfig(section='python', options='dgnv')
	dir = Default(dir, bin_path)
	if not core is None:
		if not CheckRegFunc('DGDenoise'):
			SetWorkingDir(core=core, path=dir, isAvs=True)
	last = core.avs.DGDenoise(src, strength=strength, blend=blend, chroma=chroma, searchw=searchw, device=device)
	return last


##################################################################################################
### Function  : DGDecimate
### Author    : ema
### Version   : v0.1
### Release   : 2018.01.24
##################################################################################################
### DGDecimate() is a fast stand-alone CUDA filter that implements N-in-M frame decimation.
### The input clip must be in the YV12 format.
###
### dir [str, Default: None]
### ------------------
###    The dir of DGIndexNV.
###    Get from qvs.conf -> 'python' : 'dgnv'.
###
### cycle [int, Default: 5, max 40]
### ------------------
###    Decimation cycle size M.
###    For every cycle of M frames, N frames will be retained, where N is given by the keep parameter.
###    The M - N frames that differ least from their predecessors are discarded. 
###
### keep [int, Default: 4]
### ------------------
###    Decimation keep number N.
###    For every cycle of M frames, N frames will be retained, where N is given by the keep parameter.
###    The M - N frames that differ least from their predecessors are discarded. 
###
### device [int, Default: 255]
### ------------------
###    When set to 255, the first GPU found is used.
###    When set to any other value the GPU with that ordinal value is used.
###
### show [int, Default: False]
### ------------------
###    When set to true, metrics information is overlaid onto the frame.
###    Note that if the cycle size is greater than 10, only the first 10 frame metrics are shown.
###
### +----------------+
### |  REQUIREMENTS  |
### +----------------+
### -> DGDecodeNV.dll
###    -> license.txt
##################################################################################################
def DGDecimate(src, dir=None, core=None, cycle=5, keep=4, device=255, show=False):
	core = Default(core, vs.get_core())
	bin_path = GetConfig(section='python', options='dgnv')
	dir = Default(dir, bin_path)
	if not core is None:
		if not CheckRegFunc('DGDecimate'):
			SetWorkingDir(core=core, path=dir, isAvs=True)
	last = core.avs.DGDecimate(src, cycle=cycle, keep=keep, device=device, show=show)
	return last


##################################################################################################
### Function  : DGBob
### Author    : ema
### Version   : v0.1
### Release   : 2018.01.21
##################################################################################################
### DGBob() is a fast stand-alone CUDA filter that implements the YADIF deinterlacing algorithm (original concept by Michael Niedermayer).
### The input clip must be in the YV12 format.
### Note that DGBob() requires the field order to be properly specified. DGBob can take the order from Avisynth but the safest policy is to set the correct order using the 'order' parameter. For example, AVISource() is dangerous without doing so because it always sets BFF. Note that DGSource() sets the correct field order, so when it is used as the source filter it is safe to omit the 'order' parameter or set it to -1.
###
### dir [str, Default: None]
### ------------------
###    The dir of DGIndexNV.
###    Get from qvs.conf -> 'python' : 'dgnv'.
###
### order [int, Default: -1]
### ------------------
###    Field order: -1: take order from Avisynth, 0: BFF, 1: TFF.
###
### mode [int, Default: 0]
### ------------------
###    Rendering mode:
###     0: single-rate deinterlacing,
###     1: double-rate deinterlacing,
###     2: double-rate deinterlacing but retain the original frame rate (for slow motion).
###
### device [int, Default: 255]
### ------------------
###    When set to 255, the first GPU found is used.
###    When set to any other value the GPU with that ordinal value is used.
###
### pv [bint, Default: False]
### ------------------
###    True : DGBob()
###    False: PVBob()
###
### +----------------+
### |  REQUIREMENTS  |
### +----------------+
### -> DGDecodeNV.dll
###    -> license.txt
##################################################################################################
def DGBob(src, dir=None, core=None, order=-1, mode=0, device=255, pv=False):
	core = Default(core, vs.get_core())
	bin_path = GetConfig(section='python', options='dgnv')
	dir = Default(dir, bin_path)
	if not core is None:
		if (not CheckRegFunc('DGBob')) & (not CheckRegFunc('PVBob')):
			SetWorkingDir(core=core, path=dir, isAvs=True)
	if not pv:
		last = core.avs.DGBob(src, mode=mode, order=order, device=device)
	else:
		last = core.avs.PVBob(src, mode=mode, order=order, device=device)
	return last


##################################################################################################
### Function  : RemoveFileExt
### Author    : ema
### Version   : v0.1
### Release   : 2018.01.20
##################################################################################################
### Return the filepath without ext.
##################################################################################################
def RemoveFileExt(path):
	spliter = path.split('.')
	i = 0
	out = ''
	for s in spliter:
		if i >= len(spliter) - 1:
			break
		if out == '':
			out = s
		else:
			out = out + '.' + s
		i = i + 1
	return out


##################################################################################################
### Function  : SetConfig
### Function  : GetConfig
### Author    : ema
### Version   : v0.2
### Release   : 2018.06.02
##################################################################################################
### Setting save in qvs.conf.
##################################################################################################
def SetConfig(options, value, section='python', conf_file=None):
	conf = configparser.ConfigParser()
	conf_file = Default(conf_file, GetLibPath() + '/qvs.conf')
	conf.read(conf_file)
	try:
		print('Before=' + conf.get(section, options))
	except:
		print('Before=<NULL>')
	conf.set(section, options, value)
	conf.write(open(conf_file, 'w'))
	print('After=' + conf.get(section, options))

def GetConfig(options, section='python', conf_file=None):
	conf = configparser.ConfigParser()
	conf_file = Default(conf_file, GetLibPath() + '/qvs.conf')
	conf.read(conf_file)
	rel_path_options = {'python':'d2v;dg;dgnv;dgim;logodata'}
	try:
		value = conf.get(section, options)
		if value.startswith('.'):
			for _key, _values in rel_path_options.items():
				if _values.find(';') != -1:
					_values = _values.split(';')
				else:
					_values = [_values]
				for _value in _values:
					if (_key == section) & (_value == options):
						cwd = os.getcwd()
						os.chdir(GetHomePath())
						print(value)
						value = os.path.abspath(value).replace('\\\\', '/').replace('\\', '/')
						print(value)
						os.chdir(cwd)
	except:
		value = ''
		err = 'Get value of "{section}":"{options}" error.'.format(section=section, options=options)
		raise ValueError(err)
		print('Please using SetConfig(options, value, section) to set your value.')
	return value


##################################################################################################
### Function  : ToDict
### Author    : ema
### Version   : v0.1
### Release   : 2018.01.19
##################################################################################################
### Cast x to dict type.
##################################################################################################
def ToDict(x):
	if not isinstance(x, type([])):
		x = [x]
	return x


##################################################################################################
### Function  : AddParm
### Author    : ema
### Version   : v0.1
### Release   : 2018.01.19
##################################################################################################
### Add Encoder Parm.
##################################################################################################
def AddEncParm(str, parm):
	return '{str} {parm}'.format(str=str, parm=parm)


##################################################################################################
### Function  : GetEach
### Author    : ema
### Version   : v0.1
### Release   : 2018.01.19
##################################################################################################
### Get each clip path.
### 
### path [str, default: '.']
### ------------------
###    Image source files path.
###    It's the working path at the same time when using default val.
###
### filter [dict, default: []]
### ------------------
###    Using when path does not contain wildcards.
###    Setting the filter of file system, 
###    It's the working path at the same time when using default val.
##################################################################################################
def GetEach(path='.', filter=None):
	filter = Default(filter, [])
	filter = ToDict(filter)
	path = os.path.abspath(path).replace('\\','/')
	filelist = []
	if path.find('*') == -1 & path.find('?') == -1:
		for f in os.listdir(path):
			f = os.path.join(path, f).replace('\\','/')
			if not filter == []:
				for exp in filter:
					if f.split('.')[-1].lower() == exp.lower():
						if os.path.isfile(f):
							filelist.append(f)
			else:
				if os.path.isfile(f):
					filelist.append(f)
	else:
		files = glob.glob(path)
		for f in files:
			if os.path.isfile(f):
				filelist.append(f.replace('\\','/'))
	for f in filelist:
		print('GetEach: {f}'.format(f=f))
	return filelist


##################################################################################################
### Function  : CreatScripts
### Author    : ema
### Version   : v0.1
### Release   : 2018.01.19
##################################################################################################
### Creat scripts base on base script.
### 
### clip_filelist [dict]
### ------------------
###    Clip file list.
###
### script_file [str]
### ------------------
###    Base script file path.
###
### mark [str, Default: '%']
### ------------------
###    %1=clip
###    %2=ass
###    %3=tc
##################################################################################################
def CreatScripts(clip_filelist, script_file, mark='%'):
	script_file_object = open(script_file)
	try:
		script = script_file_object.read()
	finally:
		script_file_object.close()
	clip_filelist = ToDict(clip_filelist)
	script_clip_filelist = []
	for clip_file in clip_filelist:
		script_clip_file = RemoveFileExt(clip_file) + '.' + script_file.split('.')[-1]
		print(script_clip_file)
		script_clip_filelist.append(script_clip_file)
		file_object = open(script_clip_file, 'w')
		_script = script.replace(mark+'1', clip_file)
		_script = _script.replace(mark+'2', RemoveFileExt(clip_file) + '.ass')
		_script = _script.replace(mark+'3', RemoveFileExt(clip_file) + '_tc.txt')
		file_object.write(_script)
		file_object.close()
	return script_clip_filelist


##################################################################################################
### Function  : StartScripts
### Author    : ema
### Version   : v0.2
### Release   : 2018.01.28
##################################################################################################
### Start encode with scripts.
### 
### script_filelist [dict]
### ------------------
###    Script file list.
###
### cmd [str, Default: '--crf 23']
### ------------------
###    Encoder parm.
###    %1=input, %2=output, %3=tmp
###
### pipe_bin [str, Default: 'vspipe']
### ------------------
###    Pipe exec file path.
###
### enc_bin [str, Default: 'x264_32-8bit']
### ------------------
###    Encoder exec file path.
###
### mux_bin [str, Default: 'mp4box']
### ------------------
###    Muxer(Mp4Box) exec file path.
###
### pipe_auto [bint, Default: True]
### ------------------
###    Seclect pipe exec file path auto by the first script file.
###
### example:
### ------------------
###    fs = qvs.GetEach('H:/qvs/*.mp4')
###    cs = qvs.CreatScripts(fs, 'H:/qvs/base.avs')
###    qvs.StartScripts(cs, pipe_bin='avs4x26x', cmd='--crf 20', enc_bin='x265_32-8bit')
##################################################################################################
def StartScripts(script_filelist, cmd='--crf 23', pipe_bin='vspipe', enc_bin='x264_32-8bit', mux_bin='mp4box', pipe_auto=True):
	script_filelist = ToDict(script_filelist)
	output_list = []
	if pipe_auto:
		for script_file in script_filelist:
			script_ext = script_file.split('.')[-1]
			if script_ext == 'vpy':
				pipe_bin = 'vspipe'
			elif script_ext == 'avs':
				pipe_bin = 'avs4x26x'
			else:
				raise ValueError('StartScripts: Auto set pipe bin error! No avs or vpy file!')
			break

	if (pipe_bin == 'vspipe') & enc_bin.startswith('x264'):
		cmd = '{pipe_bin} --y4m "%1" - | {enc_bin} --demuxer y4m {cmd} -o "%2" -'.format(pipe_bin=pipe_bin, enc_bin=enc_bin, cmd=cmd)
	elif (pipe_bin == 'vspipe') & enc_bin.startswith('x265'):
		cmd = '{pipe_bin} --y4m "%1" - | {enc_bin} --demuxer y4m {cmd} -o "%3" -\r\n{mux_bin} -add  "%3#trackID=1:name=" -new "%2"'.format(pipe_bin=pipe_bin, enc_bin=enc_bin, mux_bin=FindFirstFilePath(mux_bin), cmd=cmd)
	elif (pipe_bin == 'avs4x26x') & enc_bin.startswith('x264'):
		cmd = '{pipe_bin} --x264-binary {enc_bin} {cmd} -o "%2" "%1"'.format(pipe_bin=pipe_bin, enc_bin=enc_bin, cmd=cmd)
	elif (pipe_bin == 'avs4x26x') & enc_bin.startswith('x265'):
		cmd = '{pipe_bin} --x265-binary {enc_bin} {cmd} -o "%3" "%1"\r\n{mux_bin} -add  "%3#trackID=1:name=" -new "%2"'.format(pipe_bin=pipe_bin, enc_bin=enc_bin, mux_bin=FindFirstFilePath(mux_bin), cmd=cmd)
	else:
		raise ValueError('StartScripts: Error Parm of pipe_bin or enc_bin!')
	i = 1
	for script in script_filelist:
		input = script
		if (pipe_bin == 'vspipe') | (script.split('.')[-1] == 'vpy'):
			output = RemoveFileExt(script) + '_vpy.mp4'
		elif (pipe_bin == 'avs4x26x') | (script.split('.')[-1] == 'avs'):
			output = RemoveFileExt(script) + '_avs.mp4'
		else:
			raise ValueError('StartScripts: Error Parm of pipe_bin!')
		output_list.append(output)
		if enc_bin.startswith('x265'):
			tmp = RemoveFileExt(script) + '_tmp.hevc'
		else:
			tmp = ''
		_cmd = cmd.replace('%1', input)
		_cmd = _cmd.replace('%2', output)
		_cmd = _cmd.replace('%3', tmp)
		print('[{i}/{n}]Script: {script}'.format(i=i, n=len(script_filelist), script=script))
		i = i + 1
		__cmds = _cmd.split('\r\n')
		for __cmd in __cmds:
			print('[cmd]{cmd}'.format(cmd=__cmd))
			os.system('"%s"' % __cmd)
			print('')
	return output_list


##################################################################################################
### Function  : Muxers
### Author    : ema
### Version   : v0.2
### Release   : 2018.01.28
##################################################################################################
### Muxer the clips with video and audio.
### 
### paths [dict]
### ------------------
###    Clip file list.
###
### audio_ext [str, Default: '']
### ------------------
###    Ext filter of audio path.
###
### delay [int, Default: 0]
### ------------------
###    Audio delay's value.
###
### mux_bin [str, Default: 'mp4box']
### ------------------
###    Muxer(Mp4Box) exec file path.
###
### par [str, Default: '1:1']
### ------------------
###    1.PAR - pixel aspect ratio;
###    2.DAR - display aspect ratio;
###    3.SAR - storage aspect ratio;
###    -> PAR * SAR = DAR.
###    -> PAR = DAR / SAR.
###
### example:
### ------------------
###    fs = qvs.GetEach('H:/qvs/*.vob')
###    cs = qvs.CreatScripts(fs, 'H:/qvs/base.avs')
###    qvs.StartScripts(cs, pipe_bin='avs4x26x', cmd='--crf 20', enc_bin='x265_32-8bit')
###    qvs.Muxers('H:/qvs/*.mp4', 'ac3')
##################################################################################################
def Muxers(paths, audio_ext='', delay=0, mux_bin='mp4box', par='1:1'):
	paths = ToDict(paths)
	outputs = []
	check_paths = False
	for path in paths:
		if (path.find('*') != -1) | (path.find('?') != -1):
			_paths = GetEach(path)
			check_paths = True
		break
	if check_paths:
		paths = _paths
	delay = str(delay)
	for path in paths:
		output = '{path}_mux.mp4'.format(path=RemoveFileExt(path))
		if len(audio_ext) != 0:
			if audio_ext[0] == '.':
				audio_ext = audio_ext.split('.')[-1]
		audio_path = RemoveFileExt(path)
		audio_path = audio_path.replace('_avs', '*').replace('_vpy', '*')
		match_cases = GetEach('{audio_path}*.{audio_ext}'.format(audio_path=audio_path, audio_ext=audio_ext))
		match_cases = ToDict(match_cases)
		for match_case in match_cases:
			audio_path = match_case
			ext = match_case.split('.')[-1].lower()
			if audio_ext == '':
				seek = False
				for track in range(5):
					_path = RemoveFileExt(path)
					if _path.endswith('_avs') | _path.endswith('_vpy'):
						_path = _path[0:len(_path) - 4]
					f = '{path}_a{track}.{ext}'.format(path=_path, ext=path.split('.')[-1], track=str(track))
					if os.path.isfile(f):
						audio_path = f
						seek = True
						break
				if seek:
					pass
				elif (ext != 'aac') & (ext != 'ac3') & (ext != 'mp3') & (ext != 'alac') & (ext != 'm4a'):
					continue
			index_delay = match_case.lower().find('delay')
			index_ms = match_case.lower().find('ms')
			if (index_delay != -1) & (index_ms != -1):
				delay = match_case[(index_delay + 5):index_ms].strip()
			cmd = '{mux_bin} -add "{path}#trackID=1:par={par}:name=" -add "{audio_path}:delay={delay}:name=" -new "{output}"'.format(mux_bin=FindFirstFilePath(mux_bin), path=path, audio_path=audio_path, par=par, delay=delay, output=output)
			print('[cmd]{cmd}'.format(cmd=cmd))
			os.system('"%s"' % cmd)
			outputs.append(output)
			break
			print('')
	return outputs


##################################################################################################
### Function  : LsmashMuxers
### Author    : ema
### Version   : v0.1
### Release   : 2018.05.07
##################################################################################################
### Muxer the clips with video and audio.
### 
### paths [dict]
### ------------------
###    Clip file list.
###
### audio_ext [str, Default: '']
### ------------------
###    Ext filter of audio path.
###
### format [str, Default: '']
### ------------------
###    Output file formats: mp4, mov, 3gp, 3g2, m4a, m4v.
###
### delay [int, Default: 0]
### ------------------
###    Audio delay's value.
###
### mux_bin [str, Default: 'muxer']
### ------------------
###    Muxer(muxer) exec file path.
###
### par [str, Default: '1:1']
### ------------------
###    1.PAR - pixel aspect ratio;
###    2.DAR - display aspect ratio;
###    3.SAR - storage aspect ratio;
###    -> PAR * SAR = DAR.
###    -> PAR = DAR / SAR.
###
### example:
### ------------------
###    fs = qvs.GetEach('H:/qvs/*.vob')
###    cs = qvs.CreatScripts(fs, 'H:/qvs/base.avs')
###    qvs.StartScripts(cs, pipe_bin='avs4x26x', cmd='--crf 20', enc_bin='x265_32-8bit')
###    qvs.LsmashMuxers('H:/qvs/*.mp4', 'ac3')
##################################################################################################
def LsmashMuxers(paths, audio_ext='', delay=0, mux_bin='muxer', format='mp4', chapter=None, copyright=None, language=None, par='1:1'):
	paths = ToDict(paths)
	outputs = []
	check_paths = False
	for path in paths:
		if (path.find('*') != -1) | (path.find('?') != -1):
			_paths = GetEach(path)
			check_paths = True
		break
	if check_paths:
		paths = _paths
	delay = str(delay)
	for path in paths:
		output = '{path}_mux.mp4'.format(path=RemoveFileExt(path))
		if len(audio_ext) != 0:
			if audio_ext[0] == '.':
				audio_ext = audio_ext.split('.')[-1]
		audio_path = RemoveFileExt(path)
		audio_path = audio_path.replace('_avs', '*').replace('_vpy', '*')
		match_cases = GetEach('{audio_path}*.{audio_ext}'.format(audio_path=audio_path, audio_ext=audio_ext))
		match_cases = ToDict(match_cases)
		for match_case in match_cases:
			audio_path = match_case
			ext = match_case.split('.')[-1].lower()
			if audio_ext == '':
				seek = False
				for track in range(5):
					_path = RemoveFileExt(path)
					if _path.endswith('_avs') | _path.endswith('_vpy'):
						_path = _path[0:len(_path) - 4]
					f = '{path}_a{track}.{ext}'.format(path=_path, ext=path.split('.')[-1], track=str(track))
					if os.path.isfile(f):
						audio_path = f
						seek = True
						break
				if seek:
					pass
				elif (ext != 'aac') & (ext != 'ac3') & (ext != 'mp3') & (ext != 'alac') & (ext != 'm4a'):
					continue
			index_delay = match_case.lower().find('delay')
			index_ms = match_case.lower().find('ms')
			if (index_delay != -1) & (index_ms != -1):
				delay = match_case[(index_delay + 5):index_ms].strip()
			cmd = '{mux_bin} --file-format {format} '.format(mux_bin=FindFirstFilePath(mux_bin), format=format)
			if chapter != None:
				cmd += '--chapter {chapter} '.format(chapter=chapter)
			if language != None:
				cmd += '--language {language} '.format(language=language)
			if copyright != None:
				cmd += '--copyright-notice {copyright} '.format(copyright=copyright)
			cmd += '-i "{path}"?par={par} -i "{audio_path}"?encoder-delay={delay}, -o "{output}"'.format(path=path, par=par, audio_path=audio_path, delay=delay, output=output)
			print('[cmd]{cmd}'.format(cmd=cmd))
			os.system('"%s"' % cmd)
			outputs.append(output)
			break
			print('')
	return outputs


##################################################################################################
### Function  : LsmashMuxer
### Author    : ema
### Version   : v0.1
### Release   : 2018.05.07
##################################################################################################
### Muxer a clip with video and audio.
### 
### video_path [str]
### ------------------
###    Clip file path.
###
### audio_path [str]
### ------------------
###    Clip file path.
###
### format [str, Default: '']
### ------------------
###    Output file formats: mp4, mov, 3gp, 3g2, m4a, m4v.
###
### example:
### ------------------
###    qvs.LsmashMuxer('H:/qvs/1.mp4', 'H:/qvs/1.aac')
##################################################################################################
def LsmashMuxer(video_path, audio_path, delay=0, mux_bin='muxer', format='mp4', chapter=None, copyright=None, language=None, par='1:1'):
	if len(audio_ext) != 0:
		if audio_ext[0] == '.':
			audio_ext = audio_ext.split('.')[-1]
	output = audio_path + '.' + audio_ext
	delay = str(delay)
	index_delay = audio_path.lower().find('delay')
	index_ms = audio_path.lower().find('ms')
	if (index_delay != -1) & (index_ms != -1):
		delay = audio_path[(index_delay + 5):index_ms].strip()
	cmd = '{mux_bin} --file-format {format} '.format(mux_bin=FindFirstFilePath(mux_bin), format=format)
	if chapter != None:
		cmd += '--chapter {chapter} '.format(chapter=chapter)
	if language != None:
		cmd += '--language {language} '.format(language=language)
	if copyright != None:
		cmd += '--copyright-notice {copyright} '.format(copyright=copyright)
	cmd += '-i "{path}"?par={par} -i "{audio_path}"?encoder-delay={delay}, -o "{output}"'.format(path=path, par=par, audio_path=audio_path, delay=delay, output=output)
	print(cmd)
	os.system('"%s"' % cmd)
	return output


##################################################################################################
### Function  : Demuxer
### Author    : ema
### Version   : v0.1
### Release   : 2018.01.28
##################################################################################################
### Demux a clip of some track(a/v).
### 
### paths [dict]
### ------------------
###    Clip file list.
###
### audio_track [int, Default: 1]
### ------------------
###    Demux number of audio track.
###
### video_track [int, Default: None]
### ------------------
###    Demux number of video track.
###
### demux_bin [str, Default: 'ffmpeg']
### ------------------
###    Demuxer(FFmpeg) exec file path.
###
### example:
### ------------------
###    qvs.Demuxer('H:/qvs/*.mp4', audio_track=0)
##################################################################################################
def Demuxer(paths, audio_track=0, video_track=None, demux_bin='ffmpeg'):
	paths = ToDict(paths)
	check_paths = False
	outputs = []
	for path in paths:
		if (path.find('*') != -1) | (path.find('?') != -1):
			_paths = GetEach(path)
			check_paths = True
		break
	if check_paths:
		paths = _paths
	for path in paths:
		input = path
		if audio_track != None:
			filter = '-vn -sn -c:a'
			track_type = 'a'
			track_num = str(audio_track)
			output = '{path}_{track_type}{track_num}.{ext}'.format(path=RemoveFileExt(input), track_type=track_type, track_num=track_num, ext=input.split('.')[-1])
			cmd = '{demux_bin} -i "{input}" {filter} copy -y -map 0:{track_type}:{track_num} "{output}"'.format(demux_bin=FindFirstFilePath(demux_bin), input=input, filter=filter, track_type=track_type, track_num=track_num, output=output)
			print('[cmd]{cmd}'.format(cmd=cmd))
			os.system(cmd)
			outputs.append(output)
			continue
		if video_track != None:
			filter = '-an -sn -c:v'
			track_type = 'v'
			track_num = str(video_track)
			output = '{path}_{track_type}{track_num}.{ext}'.format(path=RemoveFileExt(input), track_type=track_type, track_num=track_num, ext=input.split('.')[-1])
			cmd = '{demux_bin} -i "{input}" {filter} copy -y -map 0：{track_type}:{track_num} "{output}"'.format(demux_bin=FindFirstFilePath(demux_bin), input=input, filter=filter, track_type=track_type, track_num=track_num, output=output)
			print('[cmd]{cmd}'.format(cmd=cmd))
			os.system('"%s"' % cmd)
			outputs.append(output)
			continue
	return outputs


##################################################################################################
### Function  : TsDemuxer
### Author    : ema
### Version   : v0.1
### Release   : 2018.01.28
##################################################################################################
### Demux a clip of some track(a/v).
### Only supports for *.ts.
### 
### paths [dict]
### ------------------
###    Clip file list.
###
### audio_track [int, Default: 1]
### ------------------
###    Demux number of audio track.
###
### video_track [int, Default: None]
### ------------------
###    Demux number of video track.
###
### demux_bin [str, Default: 'tsdemux']
### ------------------
###    Demuxer(tsdemux) exec file path.
###
### example:
### ------------------
###    qvs.TsDemuxer('H:/qvs/*.ts', encode=1)
##################################################################################################
def TsDemuxer(paths, encode=1, demux_bin='tsdemux'):
	paths = ToDict(paths)
	check_paths = False
	outputs = []
	for path in paths:
		if (path.find('*') != -1) | (path.find('?') != -1):
			_paths = GetEach(path)
			check_paths = True
		break
	if check_paths:
		paths = _paths
	for path in paths:
		input = path
		if (encode > 4) | (encode < 1):
			encode = 1
		encode_dict = {1:'aac', 2:'m2v+aac', 3:'wav', 4:'m2v+wav'}
		encode_type = encode_dict[encode]
		cmd = '{demux_bin} -i "{input}" -encode Demux({encode})'.format(demux_bin=FindFirstFilePath(demux_bin), input=input, encode=encode_type)
		print('[cmd]{cmd}'.format(cmd=cmd))
		os.system('"%s"' % cmd)
		outputs.append(output)
	return outputs


##################################################################################################
### Function  : EacDemuxer
### Author    : ema
### Version   : v0.1a
### Release   : 2018.02.14
##################################################################################################
### Demux a clip of some track(a/v).
### Only supports for *.vob, *.m2ts, *.ts, *.mkv.
### 
### paths [dict]
### ------------------
###    Clip file list.
###
### track [int, Default: 2]
### ------------------
###    Demux number of track in all tracks.
###
### track_list [bint, Default: False]
### ------------------
###    Show all tracks in cui.
###    It will not demux anything when true.
###
### out_ext [int, Default: None]
### ------------------
###    Set the output file ext.
###
### demux_bin [str, Default: 'eac3to']
### ------------------
###    Demuxer(eac3to) exec file path.
###
### log [bint, Default: False]
### ------------------
###    Auto remove the log file(*Log.txt).
###
### ret_delay [bint, Default: False]
### ------------------
###    Return the first path delay value which is in paths.
###
### example:
### ------------------
###    qvs.EacDemuxer('H:/qvs/*.ts', track=2, out_ext=None)
##################################################################################################
def EacDemuxer(paths, track=2, track_list=False, out_ext=None, demux_bin='eac3to', log=False, ret_delay=False):
	paths = ToDict(paths)
	check_paths = False
	for path in paths:
		if (path.find('*') != -1) | (path.find('?') != -1):
			_paths = GetEach(path)
			check_paths = True
		break
	if check_paths:
		paths = _paths
	outputs = []
	for path in paths:
		#Gain the real format and the delay(ms) value.
		input = path
		cmd = '{demux_bin} "{input}"'.format(demux_bin=FindFirstFilePath(demux_bin), input=input)
		cmd = cmd.replace('/', '\\')
		print('[cmd]{cmd}'.format(cmd=cmd))
		result = os.popen(cmd)
		res = result.read()
		delay = None
		n = 0
		for line in res.splitlines():
			if track_list:
				print(line.strip())
			else:
				if n == track:
					line = line.strip()
					line_index = line.find(':')
					print('[track]{line}'.format(line=line[line_index - 1 : len(line)]))
					_format = line.split(',')[0]
					format = _format[_format.find(' ') : len(_format)]
					format = format.strip().lower()
					print('[format]{format}'.format(format=format))
					for text in line.split(','):
						text = text.strip()
						if text.find('ms') != -1:
							delay = text[0 : len(text) - 2]
					if delay != None:
						print('[delay]{delay}'.format(delay=delay))
					if ret_delay:
						return delay
			n += 1
		if track_list:
			continue
		#Demux the track.
		if out_ext == None:
			format_dict = {
				'h264/avc'			:	'h264',
				'mpegh/iso/hevc'	:	'hevc',
				'raw/pcm'			:	'wav',
				'chapters'			:	'txt',
			}
			if format in format_dict.keys():
				ext = format_dict[format]
			else:
				ext = format.lower()
			out_ext = ext
		if delay == None:
			output = '{path} track{track}.{ext}'.format(path=RemoveFileExt(input), track=str(track), ext=out_ext)
		else:
			output = '{path} track{track} DELAY {delay}ms.{ext}'.format(path=RemoveFileExt(input), delay=delay, track=str(track), ext=out_ext)
		cmd = '{demux_bin} "{input}" {track}: "{output}"'.format(demux_bin=FindFirstFilePath(demux_bin), input=input, track=track, output=output)
		cmd = cmd.replace('/', '\\')
		print('[cmd]{cmd}'.format(cmd=cmd))
		os.system('"%s"' % cmd)
		#Remove the log file.
		if log is False:
			try:
				os.remove('{path} - Log.txt'.format(path=RemoveFileExt(output)))
			except:
				pass
		outputs.append(output)
	return outputs


##################################################################################################
### Function  : AudioEnc
### Author    : ema
### Version   : v0.1
### Release   : 2018.01.28
##################################################################################################
### Demux a clip of some track(a/v).
### 
### paths [dict]
### ------------------
###    Clip file list.
###
### bitrate [int, Default: 160]
### ------------------
###    Audio bitrate(kbps).
###
### enc [int, Default: 1]
### ------------------
###    1:aac  -> bitrate(v)
###    2:flac -> bitrate(x)
###    3:alac -> bitrate(x)
###
### enc_bin [str, Default: 'qaac']
### ------------------
###    Encoder(qaac) exec file path.
###
### enc_flac_bin [str, Default: 'flac']
### ------------------
###    Encoder(flac) exec file path.
###
### enc_alac_bin [str, Default: 'refalac']
### ------------------
###    Encoder(refalac) exec file path.
###
### pipe_bin [str, Default: 'ffmpeg']
### ------------------
###    Pipe(FFmpeg) exec file path.
###
### example:
### ------------------
###    qvs.AudioEnc('H:/qvs/*.m2ts', bitrate=160, enc=1)
##################################################################################################
def AudioEnc(paths, bitrate=160, enc=1, enc_bin='qaac', enc_flac_bin='flac', enc_alac_bin='refalac', pipe_bin='ffmpeg'):
	paths = ToDict(paths)
	check_paths = False
	for path in paths:
		if (path.find('*') != -1) | (path.find('?') != -1):
			_paths = GetEach(path)
			check_paths = True
		break
	if check_paths:
		paths = _paths
	enc_dict = {1:'aac', 2:'flac', 3:'alac'}
	if (enc > 3) | (enc < 1):
		enc = 1
	enc_type = enc_dict[enc]
	outputs = []
	for path in paths:
		input = path
		output = '{path}.{enc_type}'.format(path=RemoveFileExt(input), enc_type=enc_type)
		pipe_cmd = '{pipe_bin} -i "{input}" -vn -sn -v 0 -c:a pcm_s16le -f wav pipe: |'.format(pipe_bin=FindFirstFilePath(pipe_bin), input=input)
		if enc == 1:
			cmd = '{enc_bin} -q 2 --ignorelength -c {bitrate} - -o "{output}"'.format(enc_bin=pipe_cmd+FindFirstFilePath(enc_bin), bitrate=str(bitrate), output=output)
		elif enc == 2:
			cmd = '{enc_bin} -f --ignore-chunk-sizes -5 - -o "{output}"'.format(enc_bin=pipe_cmd+FindFirstFilePath(enc_flac_bin), output=output)
		elif enc == 3:
			cmd = '{enc_bin} -f --ignorelength - -o "{output}"'.format(enc_bin=pipe_cmd+FindFirstFilePath(enc_alac_bin), output=output)
		print('[cmd]{cmd}'.format(cmd=cmd))
		os.system('"%s"' % cmd)
		outputs.append(output)
	return outputs


##################################################################################################
### Function  : AudioTrimFF
### Function  : AudioTrimFFSingle
### Function  : AudioTrims
### Author    : ema
### Version   : v0.1
### Release   : 2018.02.04
##################################################################################################
### Trim a audio clip losslessly with ffmpeg.
### 
### path [str]
### ------------------
###    Audio clip file path.
###
### clip [clip, Default: None]
### ------------------
###    Video clip (for get fps value).
###
### codec [str, Default: 'aac']
### ------------------
###    Ext of output file.
###
### delay [int, Default: None]
### ------------------
###    Audio clip fixd delay value.
###
### fps [str, Default: None]
### ------------------
###    Convert frame to timecode with fps value.
###
### enc_bin [str, Default: 'ffmpeg']
### ------------------
###    Enc(FFmpeg) exec file path.
###
### example1:
### ------------------
###    clip = qvs.D2VSource('Video.ts')
###    frame = [[100,200], [1000,2000]]
###    qvs.AudioTrimFF('Audio DELAY -99ms.aac', frame=frame, clip=clip, delay=-99)
###
### example2:
### ------------------
###    frame = [[100,200], [1000,2000]]
###    qvs.AudioTrimFF('Audio DELAY -99ms.aac', frame=frame, fps=29.970, delay=-99)
##################################################################################################
def AudioTrimFF(path, frame=[], clip=None, codec='aac', delay=None, fps=None, enc_bin='ffmpeg'):
	input = path
	if not os.path.isfile(input):
		raise ValueError('AudioTrimFF: param of path is not a file path.')
	index_delay = input.lower().find('delay')
	index_ms = input.lower().find('ms')
	delay_orgin = None
	if (index_delay != -1) & (index_ms != -1):
		try:
			delay_orgin = int(input[(index_delay + 5):index_ms].strip())
		except:
			pass
	delay = Default(delay, Default(delay_orgin, 0))
	outputs = []
	n = 1
	for f in frame:
		start_frame = f[0]
		end_frame = f[1]
		outputs.append(AudioTrimFFSingle(path=path, start_frame=start_frame, end_frame=end_frame, clip=clip, codec=codec, delay=delay, fps=fps, enc_bin=FindFirstFilePath(enc_bin), n=n))
		n += 1
	concat = ''
	for o in outputs:
		concat = '{concat}|{o}'.format(concat=concat, o=o)
	concat = concat[1:len(concat)]
	if delay_orgin != None:
		input = input[0:(index_delay + 5)] + ' ' + str(delay_orgin-delay) + input[index_ms:len(input)]
	output = '{path}_split.{codec}'.format(path=RemoveFileExt(input), n=str(n), codec=codec)
	cmd = '{enc_bin} -i "concat:{concat}" -c copy "{output}" -y'.format(enc_bin=FindFirstFilePath(enc_bin), concat=concat, output=output)
	print('[cmd]{cmd}'.format(cmd=cmd))
	os.system('"%s"' % cmd)
	for o in outputs:
		try:
			os.remove(o)
		except:
			pass
	return output

def AudioTrimFFSingle(path, start_frame, end_frame, clip=None, codec='aac', delay=0, fps=None, enc_bin='ffmpeg', n=1):
	if not clip is None:
		clip_fps = clip.fps_num/clip.fps_den
	else:
		if fps is None:
			raise ValueError('AudioTrim: clip or fps is none!')
		clip_fps = None
	fps = Default(fps, clip_fps)
	input = path
	output = '{path}_split{n}.{codec}'.format(path=RemoveFileExt(input), n=str(n), codec=codec)
	cmd = '{enc_bin} -i "{input}" -vn -acodec copy -ss {start_tc} -to {end_tc} "{output}" -y'.format(enc_bin=enc_bin, input=input, start_tc=ConvertToTimecode(start_frame, fps, delay), end_tc=ConvertToTimecode(end_frame, fps, delay), output=output)
	print('[cmd]{cmd}'.format(cmd=cmd))
	os.system('"%s"' % cmd)
	return output

def AudioTrims(clip=None, path=None, frame=[], codec=None, delay=None, fps=None, enc_bin='ffmpeg', ret_output=False):
	if path is None:
		raise ValueError(path)
	temp_path, temp_basename, ext = PathSplit(path)
	ext = ext.replace('.', '')
	output = AudioTrimFF(path=path, frame=frame, clip=clip, codec=ext, delay=delay, fps=fps, enc_bin=enc_bin)
	if ret_output:
		return output
	return clip

##################################################################################################
### Function  : AudioTrimAVS
### Author    : ema
### Version   : v0.1
### Release   : 2018.02.05
##################################################################################################
### AudioTrim (from Avisynth v2.60) trims a clip based on time, not on frames.
### This is most useful for audio-only clips, where "frames" have no meaning anyway,
### and you may want to edit with finer precision than whole frames (at 30fps, 1 frame=33.3ms).
### Return the outpu avisynth script path.
###
### path [str]
### ------------------
###    Audio clip file path.
###
### clip [clip, Default: None]
### ------------------
###    Video clip (for get fps value).
###
### fps [str, Default: None]
### ------------------
###    Convert frame to timecode with fps value.
###
### delay [int, Default: None]
### ------------------
###    Audio clip fixd delay value.
###
### plugin_path [str, Default: 'LSMASHSource.dll']
### ------------------
###    The plugin path of avisynth for audio source.
###
### func_name [str, Default: 'LWLibavAudioSource']
### ------------------
###    The function name of avisynth for audio source.
###
### example:
### ------------------
###    frame = [[933,40642],[44239,51282]]
###    path = qvs.AudioTrimAVS('Audio DELAY -173ms.aac', frame=frame, fps=29.970)
###    qvs.AudioEnc(path, bitrate=160, enc=1)
##################################################################################################
def AudioTrimAVS(path, frame=[], clip=None, fps=None, delay=None, plugin_path='LSMASHSource.dll', func_name='LWLibavAudioSource'):
	def _ToTime(frame, fps, delay=0):
		frame_delay = int(fps * delay / 1000)
		frame -= frame_delay
		if frame < 0:
			frame = 0
		time = frame / fps
		return time
	input = path
	if not clip is None:
		clip_fps = clip.fps_num / clip.fps_den
	else:
		if fps is None:
			raise ValueError('AudioTrim: clip or fps is none!')
		clip_fps = None
	fps = Default(fps, clip_fps)
	index_delay = input.lower().find('delay')
	index_ms = input.lower().find('ms')
	delay_orgin = None
	if (index_delay != -1) & (index_ms != -1):
		try:
			delay_orgin = int(input[(index_delay + 5):index_ms].strip())
		except:
			pass
	delay = Default(delay, Default(delay_orgin, 0))
	audio_trim_list = []
	for f in frame:
		start_frame = f[0]
		end_frame = f[1]
		start_time = _ToTime(start_frame, fps, delay)
		end_time = _ToTime(end_frame, fps, delay)
		audio_trim_list.append('AudioTrim({start_time},{end_time})'.format(start_time=start_time, end_time=end_time))
	audio_trim = '+'.join(audio_trim_list)
	avs = 'LoadPlugin("{plugin_path}")\r\n{func_name}("{path}")\r\n{audio_trim}'.format(plugin_path=plugin_path, func_name=func_name, path=path, audio_trim=audio_trim)
	avs = '{avs}\r\n__END__\r\ndelay={delay}'.format(avs=avs, delay=delay)
	if delay_orgin != None:
		input = input[0:(index_delay + 5)] + ' ' + str(delay_orgin-delay) + input[index_ms:len(input)]
	output = input + '_split.avs'
	with open(output, 'w+') as f:
		f.write(avs)
	return output


##################################################################################################
### Function  : TrimMul
### Function  : Trims
### Author    : ema
### Version   : v0.1
### Release   : 2018.02.04
##################################################################################################
### Trim returns a clip with only the frame lists between the arguments first and last.
###
### example:
### ------------------
###    clip = qvs.D2VSource('H:/Video.ts')
###    frame = [[100,200], [1000,2000]]
###    clip = qvs.TrimMul(clip=clip, frame=frame)
##################################################################################################
def TrimMul(clip, frame=[]):
	core = vs.get_core()
	for f in frame:
		start_frame = f[0]
		end_frame = f[1]
		last = core.std.Trim(clip, start_frame, end_frame)
		break
	i = 0
	for f in frame:
		start_frame = f[0]
		end_frame = f[1]
		if i != 0:
			last += core.std.Trim(clip, start_frame, end_frame)
		i += 1
	return last

def Trims(clip, frame=[]):
	return TrimMul(clip, frame)

##################################################################################################
### Function  : RightStr
### Function  : LeftStr
### Author    : ema
### Version   : v0.1
### Release   : 2018.01.29
##################################################################################################
### Returns last int count of characters.
### Returns first int count of characters.
##################################################################################################
def RightStr(str, len):
	return str[len(str) - len : len(str)]

def LeftStr(str, len):
	return str[0 : len]


##################################################################################################
### Function  : ConvertToTimecode
### Author    : ema
### Version   : v0.1
### Release   : 2018.01.29
##################################################################################################
### Convert frame to timecode with fps and delay value.
##################################################################################################
def ConvertToTimecode(frame, fps, delay=0):
	def _ToStr2(rv_int):
		ret = str(rv_int)
		if len(ret) < 2:
			ret = '0' + ret
		return ret[0 : 2]
	frame_delay = int(fps * delay / 1000)
	frame -= frame_delay
	if frame < 0:
		frame = 0
	hh = int(frame / 3600 / fps)
	mm = int((frame - hh * 3600 * fps) / 60 / fps)
	ss = int((frame - hh * 3600 * fps - mm * 60 * fps) / fps)
	ff = str((frame / fps) - int(frame / fps))[2:]
	if len(ff) >= 3:
		ff = ff[0:3]
	smpte = '{hh}:{mm}:{ss}.{ff}'.format(hh=_ToStr2(hh), mm=_ToStr2(mm), ss=_ToStr2(ss), ff=ff)
	return smpte


##################################################################################################
### Function  : CheckRegFunc
### Author    : ema
### Version   : v0.1
### Release   : 2018.02.04
##################################################################################################
### Check function if is in register list.
###
### avs [bint, Default: True]
### ------------------
###    True  : check list key form core.avs.get_functions().
###    False : check list key from core.std.get_functions().
##################################################################################################
def CheckRegFunc(func_name, avs=True):
	core = vs.get_core()
	if avs:
		func_list = core.avs.get_functions()
	else:
		func_list = core.std.get_functions()
	if func_list.get(func_name) != None:
		return True
	return False


##################################################################################################
### Function  : MplsSource
### Author    : ema
### Version   : v0.1
### Release   : 2018.02.14
##################################################################################################
### Read Mpls file and get source with ffm2.
### Caching in temp dir, like 'x:/Users/ema/AppData/Local/Temp'.
###
### +----------------+
### |  REQUIREMENTS  |
### +----------------+
### -> ReadMpls.dll
### -> ffms2.dll
##################################################################################################
def MplsSource(filename, cachedir=None):
	core = vs.get_core()
	cachedir = Default(cachedir, os.environ['tmp'].replace('\\', '/'))
	mpls = core.mpls.Read(filename)
	clips = []
	for i in range(mpls['count']):
		clips.append(core.ffms2.Source(source=mpls['clip'][i], cachefile='{dir}/{filename}.ffindex'.format(dir=cachedir, filename=mpls['filename'][i].decode())))
	return core.std.Splice(clips)


##################################################################################################
### Function  : MplsEach
### Author    : ema
### Version   : v0.1
### Release   : 2018.02.14
##################################################################################################
### Read Mpls file and get filelist.
###
### +----------------+
### |  REQUIREMENTS  |
### +----------------+
### -> ReadMpls.dll
##################################################################################################
def MplsEach(filename):
	core = vs.get_core()
	mpls = core.mpls.Read(filename)
	return mpls['clip']


##################################################################################################
### Function  : TestSuite
### Author    : ema
### Version   : v0.1
### Release   : 2018.05.13
##################################################################################################
### Tesing.
##################################################################################################
def TestSuite():
	print('TestSuite')


##################################################################################################
### Function  : ToAscii
### Author    : ema
### Version   : v0.1
### Release   : 2018.05.26
##################################################################################################
### Delete chr which is out of ascii table.
##################################################################################################
def ToAscii(filename):
	pattern = r"([0-9|a-z|A-Z|_|!|#|$|%|\^|&|\(|\)|\+|,|\-|\.|;|=|@|\[|\]|`|\{|\}|~|'|\\\\|/| ]|:)"
	result_list = re.compile(pattern, re.ASCII).findall(filename)
	new_filename = ''
	for i in result_list:
		new_filename += i
	return new_filename


##################################################################################################
### Function  : Roma
### Author    : ema
### Version   : v0.1
### Release   : 2018.05.26
##################################################################################################
### Change filename to Romaji filename.
### +----------------+
### |  REQUIREMENTS  |
### +----------------+
### -> pkg_resources
### -> pykakasi.7z
### -> semidbm.7z
### -> six.pyc
##################################################################################################
def Roma(filename, space=False):
	old_filename = filename
	
	try:
		from pykakasi import kakasi as kks
	except ModuleNotFoundError:
		ExtractModule(module='pykakasi')
		ExtractModule(module='semidbm')
	finally:
		from pykakasi import kakasi as kks
	
	kks = kks()
	kks.setMode('H', 'a')  # Hiragana to ascii, default: no conversion.
	kks.setMode('K', 'a')  # Katakana to ascii, default: no conversion.
	kks.setMode('J', 'a')  # Japanese to ascii, default: no conversion.
	kks.setMode("s", space) # add space, default: no separator.

	conv = kks.getConverter()
	filename = conv.do(filename) # Convert to Romaji.
	new_filename = ToAscii(filename) # Delete chr which is out of ascii table.

	# Make new file dir
	new_dir = os.path.dirname(new_filename)
	new_dir = os.path.normpath(new_dir)
	if not os.path.isdir(new_dir):
		os.mkdir(new_dir)
	
	# Rename file
	if os.path.isfile(new_filename):
		#Case 1: old_filename equal new_filename.
		#Case 2: new_filename is exists.
		return new_filename
	os.rename(old_filename, new_filename)
	
	# Backup filename (win)
	fp = open(old_filename + '.rename.cmd', 'w+')
	fp.write('ren "{old}" "{new}"'.format(old=new_filename, new=os.path.basename(old_filename)))
	fp.close
	
	return new_filename


##################################################################################################
### Function  : ExtractModule
### Author    : ema
### Version   : v0.1
### Release   : 2018.05.26
##################################################################################################
### Extract module archive.
### See GetLibPath func.
##################################################################################################
def ExtractModule(module, lib='/libs', bin='7z'):
	path = GetLibPath(lib=lib)
	archive = '{path}/{module}.7z'.format(path=path, module=module)
	if bin.find(' ') != -1:
		bin = '"{bin}"'.format(bin=bin) #Binary file path is with word.
	cmd = '{bin} x "{archive}" -o"{path}" -aoa'.format(bin=FindFirstFilePath(bin, 'exe'), archive=os.path.normpath(archive), path=path)
	print('[cmd]{cmd}'.format(cmd=cmd))
	os.system('"%s"' % cmd)


##################################################################################################
### Function  : PathSplit
### Author    : ema
### Version   : v0.1
### Release   : 2018.08.17
##################################################################################################
### Split filename to path, basename, ext.
### Such as:
###		Arg: filename='D:/Python36/python.exe'
###		Return: 'D:/Python36', 'python', '.exe'
##################################################################################################
def PathSplit(filename):
	path, tempfilename = os.path.split(filename)
	basename, ext = os.path.splitext(tempfilename)
	return path, basename, ext


##################################################################################################
### Function  : FindFirstFilePath
### Author    : ema
### Version   : v0.1
### Release   : 2018.08.17
##################################################################################################
### Find the first file path start at python home folder.
##################################################################################################
def FindFirstFilePath(filename, fileext=None):
	for root, dirs, files in os.walk(GetHomePath()):
		for file in files:
			path, basename, ext = PathSplit(file)
			if basename.lower() == filename.lower():
				if fileext != None:
					fileext = fileext.replace('.', '')
					ext = ext.replace('.', '')
					if fileext.lower() != ext.lower():
						continue
				first_filename = os.path.join(root, file)
				return '"' + first_filename + '"'
	return filename


##################################################################################################
### Function  : AddDefEnv
### Author    : ema
### Version   : v0.1
### Release   : 2018.05.26
##################################################################################################
### Add default temporary environ.
##################################################################################################
def AddDefEnv():
	env_list = []
	env_list.append(os.path.dirname(os.path.abspath(__file__)))
	env_list.append(GetLibPath(lib='/..'))
	env_list.append(GetLibPath(lib='/../avisynth/avisynth32/plugins'))
	env_list.append(GetLibPath(lib='/../avisynth/avisynthplus64/plugins'))
	env_list.append(GetLibPath(lib='/site-packages'))
	
	for root, dirs, files in os.walk(GetLibPath(lib='/../tools')):
		for dir in dirs:
			env_list.append(root + os.sep + dir)
	for env in env_list:
		os.environ['path'] = os.environ['path'] + os.path.pathsep + env
	#raise ValueError(os.environ['path'])


##################################################################################################
### Function  : Main
##################################################################################################
def Main():
	AddDefEnv()


##################################################################################################
### TODO      : Initialize the environment variables
##################################################################################################
Main()