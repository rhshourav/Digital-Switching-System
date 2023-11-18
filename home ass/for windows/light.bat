echo off

::global variables

:style:hidden
SET "appliance=light"
SET /A "index = 100"
SET /A "count = 107"





echo "Switching " %appliance%

FOR /F "tokens=4 delims= " %%i in ('route print ^| find " 0.0.0.0"') do set localIp=%%i
for /f "tokens=1-3 delims=. " %%a in ("%localIp%") do set ip3=%%a.%%b.%%c



:while
if %index% leq %count% (

	start /MIN CMD.EXE /C curl %ip3%.%index%/%appliance% 

	SET /A "index = index + 1"

	goto :while

)
