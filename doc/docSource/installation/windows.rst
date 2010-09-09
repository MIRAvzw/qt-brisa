:mod:`windows` --- Compiling/Installing on Windows
==========================================

.. module: windows
    :synopsis: Compiling/Installing on Windows

The compilation and installation process in Windows is very simple and don't take much time.

Compiling Qt BRisa on Windows
----------------------------------------

The first thing you need to do is to install libqxt in your system. Qt BRisa repository has it own version of libqxt with some changes made to it in order to make things work fine in Brisa.  You can download Qt BRisa folder `tree <https://garage.maemo.org/frs/download.php/8365/libbrisa_0.1.1.tar.gz>`_ and after that go to the libqxt directory (Qt BRisa/deps/libqxt/) using a command line terminal and type
::

    $ configure.bat
    $ mingw32-make
    $ mingw32-make install

This will install libqxt in your computer. Now you need to compile Qt BRisa project, by going to the main directory (Qt BRisa) inside Qt BRisa folder `tree <https://garage.maemo.org/frs/download.php/8365/libbrisa_0.1.1.tar.gz>`_ and typing
::
    $ configure.bat
    $ mingw32-make

And Qt BRisa will be successfully compiled.

Installing Qt BRisa on Windows
--------------------

After compiling Qt BRisa you just need to type the following command in order to install it
::
    $ mingw32-make install

And Qt BRisa is finally installed in your computer.
