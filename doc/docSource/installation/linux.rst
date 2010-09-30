:mod:`linux` --- Compiling/Installing on Linux
==========================================

.. module: linux
    :synopsis: Compiling/Installing on Linux

.. index::  libqxt

The compilation and installation proccess on Linux is very simple, and doesn't take much time.

Installing libqxt on linux
----------------------------------------

Download latest libqxt version from http://www.libqxt.org/ and follow install instructions found at http://dev.libqxt.org/libqxt/wiki/user_guide

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

