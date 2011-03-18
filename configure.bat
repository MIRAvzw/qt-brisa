@ECHO off

@rem -- defaults
set QMAKE_BIN=qmake
set MAKE_BIN=
set STATIC=0
set DEBUG_OR_RELEASE=0
set MSVCMODE=
set DB=1
set ZEROCONF=1
set BRISA_MODULES=core upnp utils

@rem -- initialize
set BRISA_INSTALL_PREFIX=
set BRISA_INSTALL_LIBS=
set BRISA_INSTALL_BINS=
set BRISA_INSTALL_HEADERS=
set BRISA_INSTALL_FEATURES=
set BRISA_INSTALL_DOCS=

@rem -- working directories
set BRISA_BUILD_TREE=%CD%
cd "%0\..\"
SET BRISA_SOURCE_TREE=%CD%
cd %BRISA_BUILD_TREE%
if not exist %BRISA_BUILD_TREE%\tests mkdir %BRISA_BUILD_TREE%\tests 2>&1 >NUL 2>&1

@rem -- output files
set CONFIG_LOG=%BRISA_BUILD_TREE%\config.log
set QMAKE_CACHE=%BRISA_BUILD_TREE%\.qmake.cache
set BRISA_VARS=%BRISA_BUILD_TREE%\features\win32\brisavars.prf
if exist %CONFIG_LOG% move %CONFIG_LOG% %CONFIG_LOG%.bak >NUL 2>&1
if exist %QMAKE_CACHE% move %QMAKE_CACHE% %QMAKE_CACHE%.bak >NUL 2>&1
if exist %BRISA_VARS% move %BRISA_VARS% %BRISA_VARS%.bak 2>&1 >NUL 2>&1

@rem -- defaults
echo CONFIG += silent > %QMAKE_CACHE%
echo BRISA_MODULES = %BRISA_MODULES% >> %QMAKE_CACHE%
echo BRISA_MODULES = %BRISA_MODULES% > %BRISA_VARS%

shift
:top
if "%0" == ""                   goto finish
if "%0" == "-qmake-bin"         goto setqmake
if "%0" == "-make-bin"          goto setmake
if "%0" == "-I"                 goto addinclude 
if "%0" == "-L"                 goto addlibpath
if "%0" == "-l"                 goto addlib
if "%0" == "-nomake"            goto nomake
if "%0" == "-prefix"            goto prefix
if "%0" == "-libdir"            goto libdir 
if "%0" == "-docdir"            goto docdir
if "%0" == "-headerdir"         goto headerdir
if "%0" == "-bindir"            goto bindir
if "%0" == "-featuredir"        goto featuredir
if "%0" == "-static"            goto static
if "%0" == "-debug"             goto debug
if "%0" == "-release"           goto release
if "%0" == "-debug_and_release" goto debug_and_release
if "%0" == "-no-db"             goto nodb
if "%0" == "-msvc"              goto msvc
if "%0" == "/help"              goto help
if "%0" == "-help"              goto help
if "%0" == "--help"             goto help
if "%0" == "/?"                 goto help

echo Unrecognized configure option: %0
del %QMAKE_CACHE%
del %BRISA_VARS%
goto end

:setqmake
set QMAKE_BIN=%1
goto bottom2

:setmake
set MAKE_BIN=%1
goto bottom2

:addinclude
set BRISA_INCPATH=%1
set BRISA_INCPATH=%BRISA_INCPATH:\=/%
echo INCLUDEPATH += %BRISA_INCPATH% >> %QMAKE_CACHE%
goto bottom2

:addlibpath
set BRISA_LIBPATH=%1
set BRISA_LIBPATH=%BRISA_LIBPATH:\=/%
echo LIBS += -L%BRISA_LIBPATH% >> %QMAKE_CACHE%
goto bottom2

:addlib
echo LIBS += -l%1 >> %QMAKE_CACHE%
goto bottom2

:nomake
echo BRISA_MODULES -= %1 >> %QMAKE_CACHE%
echo BRISA_MODULES -= %1 >> %BRISA_VARS%
goto bottom2

:prefix
echo hmm
set BRISA_INSTALL_PREFIX=%1
goto bottom2

:libdir
set BRISA_INSTALL_LIBS=%1
goto bottom2

:docdir
set BRISA_INSTALL_DOCS=%1
goto bottom2

:headerdir
set BRISA_INSTALL_HEADERS=%1
goto bottom2

:bindir
set BRISA_INSTALL_BINS=%1
goto bottom2

:featuredir
set BRISA_INSTALL_FEATURES=%1
goto bottom2

:static
set STATIC=1
echo CONFIG += static staticlib >> %QMAKE_CACHE%
echo DEFINES += BRISA_STATIC >> %BRISA_VARS%
goto bottom    

:debug
set DEBUG_OR_RELEASE=1
echo CONFIG += debug >> %QMAKE_CACHE%
goto bottom

:release
set DEBUG_OR_RELEASE=1
echo CONFIG += release >> %QMAKE_CACHE%
goto bottom

:debug_and_release
set DEBUG_OR_RELEASE=1
echo CONFIG += debug_and_release build_all >> %QMAKE_CACHE%
goto bottom

:msvc
set MSVCMODE=-tp vc
goto bottom

:bottom2
    shift
:bottom
    shift
goto top
    
:help
    echo Usage: configure [-prefix (dir)] [-libdir (dir)] [-docdir (dir)]
    echo        [-bindir (dir)] [-headerdir (dir)] [-qmake-bin (path)]
    echo        [-make-bin (path)] [-nomake (module)] [-debug] [-release]
    echo        [-static]
    echo.
    echo Installation options:
    echo.
    echo -prefix (dir) ....... This will install everything relative to (dir)
    echo                       default: C:\brisa
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
    echo -make-bin (path) .... Specifies the path to the make executable
    echo                       default: search the system path
    echo -L (path)............ Specifies the a additional library search path
    echo -I (path)............ Specifies the a additional include search path
    echo -l (path)............ Add a custom library
    echo -static ............. Compile BRisa as a static library
    echo -debug .............. Build BRisa with debugging symbols
    echo -release ............ Build BRisa without debugging support
    echo -debug_and_release .. Build BRisa with and without debugging support
    echo -no-db .............. Do not link to Berkeley DB
    echo -nomake (module) .... Do not compile the specified module
    echo                       options: berkeley designer gui network sql web zeroconf

    del %QMAKE_CACHE%
    goto end

:finish
echo    Testing for qmake...
%QMAKE_BIN% -v >> %CONFIG_LOG% 2>&1
if errorlevel 1 goto qmakeERR
goto qmakeOK
:qmakeERR
echo    You don't seem to have 'qmake' in your PATH.
echo    Cannot proceed.
goto end

:qmakeOK
if not "%MAKE_BIN%" == "" goto detectTools_end_test_make
if "%QMAKESPEC%" == "win32-msvc"     goto testnmake
if "%QMAKESPEC%" == "win32-msvc.net" goto testnmake
if "%QMAKESPEC%" == "win32-msvc2005" goto testnmake
if "%QMAKESPEC%" == "win32-msvc2008" goto testnmake

:testmingw
echo    Testing for mingw32-make...
call mingw32-make -v >> %CONFIG_LOG% 2>&1
if errorlevel 1 goto testnmake
echo        Using mingw32-make. 
SET MAKE_BIN=mingw32-make
GOTO detectTools_end_test_make     

:testnmake
if "%QMAKESPEC%" == "win32-g++"     goto testgmake
echo    Testing for nmake...
nmake /? >> %CONFIG_LOG% 2>&1
if errorlevel 1 goto testgmake
echo        Using nmake.
SET MAKE_BIN=nmake
GOTO detectTools_end_test_make

:testgmake
echo    Testing for GNU make...
call make -v >> %CONFIG_LOG% 2>&1
if errorlevel 1 goto missingmake
echo        Using GNU make.
SET MAKE_BIN=make
GOTO detectTools_end_test_make
 
:missingmake
echo    You don't seem to have 'mingw32-make', 'nmake' or 'make' in your PATH. 
echo    Cannot proceed.
goto end

:detectTools_end_test_make
if not "%BRISA_INSTALL_PREFIX%" == "" goto skipdefaultprefix
    set BRISA_INSTALL_PREFIX=C:\BRisa
:skipdefaultprefix
if not "%BRISA_INSTALL_LIBS%" == "" goto skipdefaultlibs
    set BRISA_INSTALL_LIBS=%BRISA_INSTALL_PREFIX%\lib
:skipdefaultlibs
if not "%BRISA_INSTALL_DOCS%" == "" goto skipdefaultdocs
    set BRISA_INSTALL_DOCS=%BRISA_INSTALL_PREFIX%\doc
:skipdefaultdocs
if not "%BRISA_INSTALL_HEADERS%" == "" goto skipdefaultheaders
    set BRISA_INSTALL_HEADERS=%BRISA_INSTALL_PREFIX%\include
:skipdefaultheaders
if not "%BRISA_INSTALL_BINS%" == "" goto skipdefaultbins
    set BRISA_INSTALL_BINS=%BRISA_INSTALL_PREFIX%\bin
:skipdefaultbins
if not "%BRISA_INSTALL_FEATURES%" == "" goto skipdefaultfeatures
    %QMAKE_BIN% -query QMAKE_MKSPECS > %BRISA_BUILD_TREE%\mkspecs.tmp
    set /p BRISA_INSTALL_FEATURES=<%BRISA_BUILD_TREE%\mkspecs.tmp
    set BRISA_INSTALL_FEATURES=%BRISA_INSTALL_FEATURES%\features\win32
    del %BRISA_BUILD_TREE%\mkspecs.tmp
:skipdefaultfeatures

echo BRISA_INSTALL_PREFIX = %BRISA_INSTALL_PREFIX:\=/% >> %QMAKE_CACHE%
echo BRISA_INSTALL_PREFIX = %BRISA_INSTALL_PREFIX:\=/% >> %BRISA_VARS%
echo BRISA_INSTALL_LIBS = %BRISA_INSTALL_LIBS:\=/% >> %QMAKE_CACHE%
echo BRISA_INSTALL_LIBS = %BRISA_INSTALL_LIBS:\=/% >> %BRISA_VARS%
echo BRISA_INSTALL_BINS = %BRISA_INSTALL_BINS:\=/% >> %QMAKE_CACHE%
echo BRISA_INSTALL_BINS = %BRISA_INSTALL_BINS:\=/% >> %BRISA_VARS%
echo BRISA_INSTALL_HEADERS = %BRISA_INSTALL_HEADERS:\=/% >> %QMAKE_CACHE%
echo BRISA_INSTALL_HEADERS = %BRISA_INSTALL_HEADERS:\=/% >> %BRISA_VARS%
echo BRISA_INSTALL_FEATURES = %BRISA_INSTALL_FEATURES:\=/% >> %QMAKE_CACHE%
echo BRISA_INSTALL_FEATURES = %BRISA_INSTALL_FEATURES:\=/% >> %BRISA_VARS%
echo BRISA_INSTALL_DOCS = %BRISA_INSTALL_DOCS:\=/% >> %QMAKE_CACHE%
echo BRISA_INSTALL_DOCS = %BRISA_INSTALL_DOCS:\=/% >> %BRISA_VARS%
echo BRISA_SOURCE_TREE = %BRISA_SOURCE_TREE:\=/% >> %QMAKE_CACHE%
echo BRISA_BUILD_TREE = %BRISA_BUILD_TREE:\=/% >> %QMAKE_CACHE%



echo	Installing QtSoap 2.7.1...

cd deps\qtsoap-2.7_1-opensource
echo CONFIG += release >> %QMAKE_CACHE%
:skiprelease
if not "%MSVCMODE%" == "" goto skipmakeannounce
%MAKE%
echo    QtSoap 2.7.1 installed. 

cd ../..




echo    Testing for optional external libraries.
echo    If tests fail, some features will not be available.

goto alltestsok

:alltestsok
if "%DEBUG_OR_RELEASE%"=="1" goto skiprelease
echo CONFIG += release >> %QMAKE_CACHE%
:skiprelease

echo    Configuration successful.
echo    Generating makefiles...
cd %BRISA_BUILD_TREE%
%QMAKE_BIN% %MSVCMODE% -recursive %BRISA_SOURCE_TREE%\brisa.pro
if errorlevel 1 goto mainqmakeERR

if not "%MSVCMODE%" == "" goto skipmakeannounce
echo    Makefiles generated. Run %MAKE% mingw32-make now. 
goto end
:skipmakeannounce
echo    Visual Studio solution generated. Open brisa.sln in Visual Studio.
goto end

:mainqmakeERR
echo    Error running qmake. Cannot proceed.
goto end

:end 
