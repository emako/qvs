import vapoursynth as vs
import havsfunc as haf
import mvsfunc as mvf
import qvs

core = vs.get_core()
src = qvs.LWLSource(r'C:\Users\ema\Desktop\splashscreen_meitu_2.png')
src = core.std.AddBorders(src,4,4,4,4,color=[240,215,48])
src = core.std.AddBorders(src,8,8,8,8,color=[240,48,147])
src.set_output()
