if "%1"=="build" goto build

cd ..\run
wd /ega43 /trap=rsi /swap tekwar %1 %2
cd ..\src
goto done

:build
cd ..\run
wd /ega43 /trap=rsi /swap build %2
cd ..\src

:done

