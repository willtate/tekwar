..\run\build.exe   :    build.obj bstub.obj engine.obj cache1d.obj a.obj 
	wlink debug all @build.lnk

bstub.obj : bstub.c
	wcc386 bstub /4r /s /d2 /zq /or
