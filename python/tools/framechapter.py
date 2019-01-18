import os
import re
import argparse
import sys

###########################
#input-example
"""""""""""""""""""""""""""
#framechapter
#framerate=30000/1001
framenum	title
0	Chapter 1
100	Chapter 2
200	Chapter 3
300	Chapter 4
400	Chapter 5
500	Chapter 6
600	Chapter 7
700	Chapter 8
800	Chapter 9
900	Chapter 10
"""""""""""""""""""""""""""

###########################
#output-example
"""""""""""""""""""""""""""
CHAPTER01=00:00:00.000
CHAPTER01NAME=Chapter 1
CHAPTER02=00:00:03.337
CHAPTER02NAME=Chapter 2
CHAPTER03=00:00:06.673
CHAPTER03NAME=Chapter 3
CHAPTER04=00:00:10.010
CHAPTER04NAME=Chapter 4
CHAPTER05=00:00:13.347
CHAPTER05NAME=Chapter 5
CHAPTER06=00:00:16.683
CHAPTER06NAME=Chapter 6
CHAPTER07=00:00:20.020
CHAPTER07NAME=Chapter 7
CHAPTER08=00:00:23.357
CHAPTER08NAME=Chapter 8
CHAPTER09=00:00:26.693
CHAPTER09NAME=Chapter 9
CHAPTER10=00:00:30.030
CHAPTER10NAME=Chapter 10
"""""""""""""""""""""""""""

class singlechapter:
    template="CHAPTER{i:02d}={t}\nCHAPTER{i:02d}NAME={n}\n"
    def __init__(self,frame:int,name:str):
        self.frame=frame
        self.name=name

    def __str__(self):
        return str(self.frame)+"\t"+self.name

    def __repr__(self):
        return repr(self.__str__())

    def tochapter(self,i:int,fps:float,tc=None):
        if tc is None:
            return singlechapter.template.format(i=i,t=frame2time(self.frame,fps),n=self.name)
        else:
            return singlechapter.template.format(i=i,t=ms2time(tc[self.frame]),n=self.name)


def ms2time(t:int):
    return "{h:02d}:{m:02d}:{s:02d}.{ms:03d}".format(ms=t%1000,
        s=int(t/1000)%60,m=int(t/60000)%60,h=int(t/3600000))

def frame2time(n:int,fps:float):
    return ms2time(round(n*1000/fps))

def read(p:str,encoding="utf-8"):
    with open(p,"r",encoding=encoding) as file:
        lines=[i.rstrip("\n") for i in file.readlines()]
    if "framechapter" in lines[0]:
        return lines
    else:
        raise TypeError("read:only framechapter format support")

def readtc(p:str,encoding=None):
    rex=re.compile(r"[0-9.]+")
    with open(p,"r",encoding=encoding) as file:
        lines=[i.rstrip("\n") for i in file.readlines()]
    if "timestamp format v2" not in lines[0] and "timecodes format v2" not in lines[0]:
        print(lines[0])
        raise TypeError("unsupport tc format")
    return [round(float(i)) for i in lines if rex.match(i)]

def main(path:str,output=None,fps=None,tc=None):
    os.chdir(os.path.dirname(path))
    cflist=read(path)
    if output is None:
        output=os.path.splitext(path)[0]+".chapter.txt"

    fpsrex=re.compile(r"^#framerate=([0-9/.]+)",re.I)
    tcrex=re.compile(r"^#tc=(.+)")

    clist=[]
    start=False
    for line in cflist:
        if line[0]=="#":
            match=fpsrex.match(line)
            if match and fps is None:
                fps=eval(match.group(1))
            else:
                match=tcrex.match(line)
                if match and tc is None:
                    tc=match.group(1)
        elif line=="framenum\ttitle":
            start=True
        elif start:
            tmp=line.split("\t")
            if len(tmp)==2:
                clist.append(singlechapter(int(tmp[0]),tmp[1]))
            elif len(tmp)==1:
                clist.append(singlechapter(int(tmp[0]),""))
            else:
                pass
        else:
            pass

    if fps is None and tc is None:
        raise ValueError("must have fps or tc")

    if tc is not None:
        tc=readtc(tc)
    clist=sorted(clist,key=lambda x:x.frame)

    chapter=""
    for i in range(len(clist)):
        chapter+=clist[i].tochapter(i+1,fps,tc)
    chapter=chapter.rstrip("\n")

    print(chapter)

    with open(output,"w",encoding="utf-8") as file:
        file.write(chapter)

if __name__ == '__main__':
    class args:
        pass
    parser=argparse.ArgumentParser(description='framechapter')
    parser.add_argument('-i','--input',help='Input')
    parser.add_argument('-o','--output',default=None,help='Output')
    parser.add_argument('-fn','--fpsnum',default=0,type=float,help=r'fps=fpsnum/fpsden')
    parser.add_argument('-fd','--fpsden',default=1,type=float,help=r'fps=fpsnum/fpsden')
    parser.add_argument('-tc','--timecodes',default=None,help=r'Timecode File Location')
    parser.parse_args(sys.argv[1:],args)
    fps=None if args.fpsnum/args.fpsden<=0 else args.fpsnum/args.fpsden
    main(args.input,args.output,fps,args.timecodes)