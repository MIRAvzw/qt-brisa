@ECHO off
SET QMAKE=qmake
SET MAKE=nmake
SET PROJECT_ROOT=%CD%
SET TESTDIR=%PROJECT_ROOT%\config.tests
SET CONFIG_LOG=config.log
SET LAST_FUNC_RET=0

if exist %PROJECT_ROOT%\config.in   del %PROJECT_ROOT%\config.in
if exist %PROJECT_ROOT%\config.log  del %PROJECT_ROOT%\config.log

echo #depends.pri > %PROJECT_ROOT%\depends.pri

shift
set QMAKEBIN=qmake
set QXT=1
set OPENSSL=0
set FCGI=0
set DB=0

echo include(depends.pri) > %PROJECT_ROOT%\config.in
echo BRISA_stability += unknown >> %PROJECT_ROOT%\config.in
echo CONFIG += release >> %PROJECT_ROOT%\config.in

:top
if "%1" == ""            goto finish
if "%1" == "-qmake-bin"  goto setqmake
if "%1" == "-bootstrap"  goto bootstrap
if "%1" == "-verbose"    goto verbose
if "%1" == "-prefix"     goto prefix
if "%1" == "-libdir"     goto libdir 
if "%1" == "-docdir"     goto docdir
if "%1" == "-headerdir"  goto headerdir
if "%1" == "-bindir"     goto bindir
if "%1" == "-static"     goto static
if "%1" == "-debug"      goto debug
if "%1" == "-release"    goto release
if "%1" == "-qws"        goto qws
if "%1" == "-help"       goto help
if "%1" == "--help"      goto help

echo Unrecognized configure option: %1
del %PROJECT_ROOT%\config.in
goto end

:help
    echo Usage: configure [-prefix (dir)] [-libdir (dir)] [-docdir (dir)]
    echo        [-bindir (dir)] [-headerdir (dir)] [-qmake-bin (path)]
    echo        [-static] [-debug] [-release]
    echo        [-no-openssl] [-nomake (module)] [-msvc]
    echo.
    echo Installation options:
    echo.
    echo -prefix (dir) ....... This will install everything relative to (dir)
    echo                       default: C:\qt-brisa
    echo -libdir (dir) ....... Libraries will be installed to (dir)
    echo                       default: PREFIX/lib
    echo -docdir (dir) ....... Documentation will be installed to (dir)
    echo                       default: PREFIX/share/doc
    echo -bindir (dir) ....... Executables will be installed to (dir)
    echo                       default: PREFIX/bin
    echo -headerdir (dir) .... Include files will be installed to (dir)
    echo                       default: PREFIX/include
    echo -qmake-bin (path) ... Specifies the path to the qmake executable
    echo                       default: search the system path
    echo -static ............. Compile Brisa as a static library
    echo -debug .............. Build Brisa with debugging symbols
    echo -release ............ Build Brisa without debugging support
    echo -no-openssl ......... Do not link to OpenSSL
    echo -coverage ........... Collect coverage information

    del %PROJECT_ROOT%\config.in
    goto end

:debug
echo CONFIG -= release >> %PROJECT_ROOT%\config.in
echo CONFIG += debug >> %PROJECT_ROOT%\config.in
    
:finish
echo    Testing for qmake...
qmake -v >> %PROJECT_ROOT%\%CONFIG_LOG% 2>&1
if errorlevel 1 goto qmakeERR
goto qmakeOK

:qmakeERR
echo    You don't seem to have 'qmake' in your PATH.
echo    Cannot proceed.
goto end

:qmakeOK
if "%QMAKESPEC%" == "win32-msvc"     goto testnmake
if "%QMAKESPEC%" == "win32-msvc.net" goto testnmake
if "%QMAKESPEC%" == "win32-msvc2005" goto testnmake

:testmingw
echo    Testing for mingw32-make...
call mingw32-make -v >> %PROJECT_ROOT%\%CONFIG_LOG% 2>&1
if errorlevel 1 goto testnmake
echo        Using mingw32-make. 
SET MAKE=mingw32-make
GOTO detectTools_end_test_make 

:qt4fail
cd ../..
echo qt4 not found, can not proceed
goto end


:qxtfail
cd ../..
echo qxt not found, can not proceed
goto end

:detectTools_end_test_make
echo    Testing for external libraries.
echo    If a test fails, installation won't proceed.
if "%QXT%"=="0" goto qxtfail
echo    Testing for qxt...
echo QXT... >> %PROJECT_ROOT%\%CONFIG_LOG%
cd %TESTDIR%\qxt
%QMAKE% >> %PROJECT_ROOT%\%CONFIG_LOG% 2>&1
if errorlevel 1 goto qxtfail
call %MAKE% clean >> %PROJECT_ROOT%\%CONFIG_LOG% 2>&1
call %MAKE% >> %PROJECT_ROOT%\%CONFIG_LOG% 2>&1
if errorlevel 1 goto qxtfail
echo DEFINES += HAVE_QXT >> %PROJECT_ROOT%\config.in
echo        QXT enabled.

echo   Installing dependencies.

echo   Installing QtSoap 2.6...
cd deps\qtsoap-2.6-opensource
%MAKE% >> qtsoap_build.log
cd ../..

echo    Configuration successful.
echo    Generating makefiles...
copy %PROJECT_ROOT%\config.pri %PROJECT_ROOT%\config.pri.bak >> %PROJECT_ROOT%\%CONFIG_LOG%
copy %PROJECT_ROOT%\config.in %PROJECT_ROOT%\config.pri >> %PROJECT_ROOT%\%CONFIG_LOG%
del %PROJECT_ROOT%\config.in >> %PROJECT_ROOT%\%CONFIG_LOG%
%QMAKE% -recursive
if errorlevel 1 goto mainqmakeERR

echo    Makefiles generated. Run %MAKE% now.
goto end

:mainqmakeERR
echo    Error running qmake. Cannot proceed.
goto end

:end

