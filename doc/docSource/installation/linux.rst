:mod:`linux` --- Compiling/Installing on Linux
==========================================

.. module: linux
    :synopsis: Compiling/Installing on Linux

.. index::  libqxt

The compilation and installation proccess on Linux is very simple, and don't take much time.

Installing libqxt on linux
----------------------------------------

The first thing you need to do is to install libqxt in your system, in case you already have libqxt installed in your system you can jump to "Installing Qt BRisa on Linux" section. 

Qt BRisa repository has it own version of libqxt with some changes made to it in order to make things work fine in Brisa.  You can download Qt BRisa folder `tree <https://garage.maemo.org/frs/download.php/8365/libbrisa_0.1.1.tar.gz>`_ and after that go to the libqxt directory (qt-brisa/deps/libqxt/) using a command line terminal and type
::

    $ ./configure
    $ make
    $ sudo make install


You can also choose to install libqxt using .deb `file <https://garage.maemo.org/frs/download.php/8111/libqxt-dev_0.5.0maemo_all.deb>`_, going to the folder you downloaded it and typing the following command
::
    $ sudo dpkg -i libqxt-dev_0.5.0maemo_all.deb



This will install libqxt in your computer.

Installing Qt BRisa on Linux
--------------------

With libqxt installed in your system you just need to compile BRisa project, by going to the main directory (qt-brisa) inside Qt BRisa folder `tree <https://garage.maemo.org/frs/download.php/8365/libbrisa_0.1.1.tar.gz>`_ and typing
::
    $ ./configure
    $ make


And installing it typing
::
    $ sudo make install

You can also install Qt BRisa using the .deb `file <https://garage.maemo.org/frs/download.php/8364/libbrisa-dev_0.1.1linux.deb>`_
running the following command inside the folder you downloaded it
::
    $ sudo dpkg -i libbrisa-dev_0.4.0maemo_all.deb

