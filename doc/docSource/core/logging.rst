:mod:`log` --- Logging facilities
==================================

.. module: log
    :synopsis: Provides logging facility with a colored logging feature.
.. index:: logger

Qt BRisa provides logging functions with a colored
logging feature.

By using the log function, it's possible to create debug, warning, critical or fatal messages. The use is very simple and will be exemplified next

Global Logger
-------------

This module provides a global (or root) logger. It's simple to use, as you can see the the following example
::
    #include <BrisaLog>

    brisaLogInitialize()    

    qDebug() << "My debug message";
    qWarning() << "My warning message";
    qCritical() << "My critical message";
    qFatal() << "My fatal message";


