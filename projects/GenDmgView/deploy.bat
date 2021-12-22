set BinDir=%1
set DeployDir=%2
set ProjectDir=%~dp0
set ProjectName=GenDmgView
set SrcRoot=%ProjectDir%..\..\src\%ProjectName%\
set IncRoot=%ProjectDir%..\..\include\%ProjectName%\
setlocal enableextensions enabledelayedexpansion
call :find-cpp-files %SrcRoot%
call :find-sub-dirs %IncRoot%



XCOPY %BinDir%* %DeployDir% /s /d /y

echo cppPath =%ProjectDir%..\..\%ProjectName%\src\
echo ProjectDir=%ProjectDir%
echo SUB_DIRS=%SUB_DIRS%
echo CPP_PATHS=%CPP_PATHS%

@rem 可以通过修改TS_FILE_LIST来控制生成那些ts文件
set TS_FILE_LIST=zh en

set LUPDATE_ST_TARGETS=
(for %%a in (%TS_FILE_LIST%) do (
	set LUPDATE_ST_TARGETS=!LUPDATE_ST_TARGETS! %ProjectDir%\res\ts\%%a.ts
))

echo LUPDATE_ST_TARGETS=%LUPDATE_ST_TARGETS%

lupdate -I %ProjectDir%\..\..\%ProjectName%\include\ %SUB_DIRS% %CPP_PATHS% -ts %LUPDATE_ST_TARGETS%

(for %%a in (%TS_FILE_LIST%) do (
	lrelease %ProjectDir%\res\ts\%%a.ts -qm %ProjectDir%\res\ts\%%a.qm
))


rcc -binary %ProjectDir%\res\res.qrc -o %DeployDir%\res.rcc



:find-sub-dirs
	set SUB_DIRS=
	for /d /r "%~1" %%D in (*) do (
		 set SUB_DIRS=!SUB_DIRS! "%%~fD" 
		 echo %%~fD
	)
goto :eof

:find-cpp-files
    set CPP_PATHS=
    for /r "%~1" %%P in ("*.cpp") do (
        set CPP_PATHS=!CPP_PATHS! "%%~fP"
    )
goto :eof