set BinDir=%1
set DeployDir=%2
set ProjectDir=%~dp0
XCOPY %BinDir%* %DeployDir% /s /d /y

rcc -binary %ProjectDir%\res\res.qrc -o %DeployDir%\res.rcc