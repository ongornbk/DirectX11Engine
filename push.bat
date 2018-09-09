@echo off
cls
:start
echo DirectX11Engine
date /t
type version.ver
echo:
set /p input="Commit Message : "
echo %input% > version.ver
git add *
git commit -m "%input%"
git push
pause