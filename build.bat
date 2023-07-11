@ECHO OFF
SETLOCAL ENABLEDELAYEDEXPANSION
CLS

SET glfw_dir=lib\glfw
SET glad_dir=lib\glad
SET cglm_dir=lib\cglm

REM Build GLFW
cmake -DGLFW_BUILD_EXAMPLES=OFF -DGLFW_BUILD_TESTS=OFF -DGLFW_BUILD_DOCS=OFF -S lib\glfw\ -B lib\glfw\build
msbuild lib\glfw\build\GLFW.sln -p:Configuration=Release

SET out=pec.exe
SET sources=
SET ext_sources=%glad_dir%\src\glad.c
SET ext_obj=bin\glad.obj

PUSHD src
FOR /R %%x IN (*.c) DO SET sources=!sources! %%x
POPD

SET cl_flags=/nologo /Zi /Fdbin\ /Fobin\ /MD /D_DEBUG
SET cl_warning_flags=/external:W0 /external:I%cglm_dir%\include /W4 /D_CRT_SECURE_NO_WARNINGS
SET deps=/Isrc\ /I%glfw_dir%\include /I%glad_dir%\include /I%cglm_dir%\include
SET linker_flags=/link /LIBPATH:%glfw_dir%\build\src\Release\ glfw3.lib opengl32.lib shell32.lib gdi32.lib user32.lib
IF NOT EXIST bin MKDIR bin

REM Build glad
ECHO Building external dependencies...
cl /c %cl_flags% /external:Isrc\external /external:W0 /I%glad_dir%\include %ext_sources%

REM Build pec.exe
ECHO Building %out%...
cl %cl_flags% %cl_warning_flags% %deps% /Febin\%out% %sources% %ext_obj% %linker_flags%

IF %ERRORLEVEL% NEQ 0 (
    ECHO Failed to build %out%. Aborting...
    EXIT
)
ECHO Removing unnecessary object files...
DEL bin\*.obj
ECHO Successfully built %out%