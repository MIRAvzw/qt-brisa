:mod:`maemo4` --- Compiling/Installing on Maemo 4
==========================================

.. module: maemo4
    :synopsis: Compiling/Installing on Maemo 4

The compilation process for maemo is done using Scratchbox, because of hardware limitation that can disrupt the process, the installation is done by .deb packages.

Compiling Qt BRisa in Maemo 4 (Via Scratchbox)
----------------------------------------------

The first thing you need to do is to install libqxt in your system. You can do that by direct installing the .deb `file <https://garage.maemo.org/frs/download.php/8111/libqxt-dev_0.5.0maemo_all.deb>`_ typing the following command inside the folder you downloaded the file
::
    $ dpkg -i libqxt-dev_0.5.0maemo_all.deb

Or by compiling in Scratchbox and then installing it
::
    $ sudo  apt-get install cdbs             (Done in device and Scratchbox)
    $ sudo  apt-get install libqt4-dev       (Done in device and Scratchbox)
    $ cd /brisa-cpp/trunk/dependencies/libqxt
    $ dpkg-buildpackage
    $ cd ..
    $ dpkg -i libqxt-dev_0.5.0maemo_all.deb  (Done in device and Scratchbox)
    
And after that you need to compile Qt BRisa (via Scratchbox) typing
::
    $ cd /brisa-cpp/trunk/brisa-cpp
    $ dpkg-buildpackage
 
Now you are ready to install Qt BRisa

Installing Qt BRisa on Maemo 4
--------------------

To install Qt BRisa in Maemo 4 you just need to download the `libbrisa-dev_0.4.0maemo_all.deb <https://garage.maemo.org/plugins/scmsvn/viewcvs.php/qt/packages-installation/maemo4_diablo/?root=brisa>`_ file and type the following command inside the folder you put it
::
    $ sudo dpkg -i libbrisa-dev_0.4.0maemo_all.deb

Remember that you need to have libqxt installed (look the Compiling Qt BRisa in Maemo 4 (Via Scratchbox) session).
