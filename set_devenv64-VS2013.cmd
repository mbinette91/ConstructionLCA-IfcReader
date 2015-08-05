set OSG_DIR=E:\Libs\OpenSceneGraph-3.2
set OSG_LIBRARY_PATH=%OSG_DIR%\bin
set OSG_PLUGINS_LIB=%OSG_DIR%\lib\osgPlugins-3.2.1
set OSG_FILE_PATH=D:\lib\OSG\OpenSceneGraph-Data;D:\lib\OSG\OpenSceneGraph-Data\Images;D:\lib\OSG\OpenSceneGraph-Data\fonts;

set BOOST_DIR=E:\Libs\boost_1_58_0
set CGAL_DIR=D:\lib\CSG\CGAL\CGAL-4.3-install\auxiliary\gmp\lib\

set QMAKESPEC=win32-msvc2013
set QMAKE_TARGET.arch=x86_64
set QTDIR=E:\Libs\Qt\5.4\msvc2013_64

PATH=%OSG_DIR%\bin;%PATH%
PATH=%OSG_PLUGINS_LIB%;%PATH%
PATH=%QTDIR%\bin;%PATH%
PATH=%CGAL_DIR%\bin;%PATH%
PATH=C:\Program Files (x86)\WiX Toolset v3.8\bin;%PATH%

call "C:\Program Files (x86)\Microsoft Visual Studio 12.0\VC\vcvarsall.bat" x86_amd64

devenv

