@rem https://gpac.wp.imt.fr/downloads/gpac-nightly-builds/
@rem copy gpac-1.1.0-DEV-latest-master-x64.exe to here firstly.

rd /s /q .\gpac64

rem extract gpac x64 7zip pkg
mkdir gpac64
copy gpac*.exe gpac64
cd gpac64
7z x gpac*.exe
del /s gpac*.exe

cd ..
mkdir qvs\tools\GPAC
copy gpac64\libcryptoMD.dll qvs\tools\GPAC
copy gpac64\libgpac.dll qvs\tools\GPAC
copy gpac64\libsslMD.dll qvs\tools\GPAC
copy gpac64\mp4box.exe qvs\tools\GPAC

@rem new version files:
copy gpac64\OpenSVCDecoder.dll qvs\tools\GPAC

@rem old version files:
::copy gpac64\js.dll qvs\tools\GPAC
::copy gpac64\libeay32.dll qvs\tools\GPAC
::copy gpac64\ssleay32.dll qvs\tools\GPAC

rd /s /q .\gpac64
pause
