compopts =    /4r /s /zq /or

objs     =    tekgame.obj    tekprep.obj    teksnd.obj     tektag.obj
objs     +=   tektxt.obj     tekstat.obj    tekchng.obj    tekspr.obj
objs     +=   tekgun.obj     tekmsc.obj     tekmap.obj     tekldsv.obj
objs     +=   teksmk.obj     tekasm.obj     jstick.obj     tekcdr.obj
objs     +=   engine.obj     a.obj          multi.obj      cache1d.obj
objs     +=   tekctm.obj     tekvfx1.obj    sndhmir.obj    av_wc10r.obj

..\run\tekwar.exe :     $(objs)
    wlink     @tekwar.lnk

tekgame.obj : tekgame.c      build.h   names.h   tekwar.h
    wcc386    tekgame   $(compopts)    

tekprep.obj : tekprep.c      build.h   names.h   tekwar.h
    wcc386    tekprep   $(compopts)    

teksnd.obj  : teksnd.c       build.h   names.h   tekwar.h
    wcc386    teksnd    $(compopts)    

tektag.obj  : tektag.c       build.h   names.h   tekwar.h
    wcc386    tektag    $(compopts)    

tektxt.obj  : tektxt.c       build.h   names.h   tekwar.h
    wcc386    tektxt    $(compopts)    

tekstat.obj : tekstat.c      build.h   names.h   tekwar.h
    wcc386    tekstat   $(compopts)    

tekchng.obj : tekchng.c      build.h   names.h   tekwar.h
    wcc386    tekchng   $(compopts)    

tekspr.obj :  tekspr.c       build.h   names.h   tekwar.h
    wcc386    tekspr    $(compopts)    

tekgun.obj :  tekgun.c       build.h   names.h   tekwar.h
    wcc386    tekgun    $(compopts)    

tekmsc.obj :  tekmsc.c       build.h   names.h   tekwar.h
    wcc386    tekmsc    $(compopts)    

tekmap.obj :  tekmap.c       build.h   names.h   tekwar.h
    wcc386    tekmap    $(compopts)    

tekldsv.obj : tekldsv.c      build.h   names.h   tekwar.h
    wcc386    tekldsv   $(compopts)    

teksmk.obj :  teksmk.c       build.h   names.h   tekwar.h  smack.h
    wcc386    teksmk    $(compopts)    

tekctm.obj :  tekctm.c       serial.h
    wcc386    tekctm    $(compopts)

tekvfx1.obj :  tekvfx1.c     vfx1.h
    wcc386    tekvfx1   $(compopts)

tekasm.obj :  tekasm.asm     build.h  names.h   
    wasm      tekasm    -4pr -mf -zq

jstick.obj :  jstick.asm     build.h  
    wasm      jstick    -4pr -mf -zq

tekcdr.obj :  tekcdr.c       build.h
    wcc386    tekcdr    $(compopts)

