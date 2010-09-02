:mod:`windows` --- Compiling/Installing on Windows
==========================================

.. module: windows
    :synopsis: Compiling/Installing on Windows

The compilation and installation process in Windows is very simple and don't take much time.

Compiling qt-BRisa on Windows
----------------------------------------

The first thing you need to do is to install libqxt in your system. Qt-Brisa repository has it own version of libqxt with some changes made to it in order to make things work fine in Brisa.  You can download qt-BRisa folder `tree <https://garage.maemo.org/frs/download.php/8365/libbrisa_0.1.1.tar.gz>`_ and after that go to the libqxt directory (qt-brisa/deps/libqxt/) using a command line terminal and type
::

    $ configure.bat
    $ mingw32-make
    $ mingw32-make install

This will install libqxt in your computer. Now you need to compile qt-BRisa project, by going to the main directory (qt-brisa) inside qt-BRisa folder `tree <https://garage.maemo.org/frs/download.php/8365/libbrisa_0.1.1.tar.gz>`_ and typing
::
    $ configure.bat
    $ mingw32-make

And Brisa Qt will be successfully compiled.

Installing qt-BRisa on Windows
--------------------

After compiling qt-BRisa you just need to type the following command in order to install it
::
    $ mingw32-make install

And qt-BRisa is finally installed in your computer.
