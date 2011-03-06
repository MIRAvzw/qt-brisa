#############
## basic FindBrisa.cmake
## This is an *EXTREMELY BASIC* cmake find/config file for
## those times you have a cmake project and wish to use
## libBrisa.
##
## It should be noted that at the time of writing, that
## I (mschnee) have an extremely limited understanding of the
## way Find*.cmake files work, but I have attempted to
## emulate what FindQt4.cmake and a few others do.
##
##  To enable a specific component, set your BRISA_USE_${modname}:
##  SET(BRISA_USE_BRISACORE TRUE)
##  SET(BRISA_USE_BRISAGUI FALSE)
##  Currently available components:
##  BrisaCore, BrisaGui, BrisaNetwork, BrisaWeb, BrisaSql
##  Auto-including directories are enabled with INCLUDE_DIRECTORIES(), but
##  can be accessed if necessary via ${BRISA_INCLUDE_DIRS}
##
## To add the libraries to your build, TARGET_LINK_LIBRARIES(), such as...
##  TARGET_LINK_LIBRARIES(YourTargetNameHere ${BRISA_LIBRARIES})
## ...or..
##  TARGET_LINK_LIBRARIES(YourTargetNameHere ${QT_LIBRARIES} ${BRISA_LIBRARIES})
################### TODO:
##      The purpose of this cmake file is to find what components
##  exist, regardless of how libBrisa was build or configured, thus
##  it should search/find all possible options.  As I am not aware
##  that any module requires anything special to be used, adding all
##  modules to ${BRISA_MODULES} below should be sufficient.
##      Eventually, there should be version numbers, but
##  I am still too unfamiliar with cmake to determine how to do
##  version checks and comparisons.
##      At the moment, this cmake returns a failure if you
##  try to use a component that doesn't exist.  I don't know how to
##  set up warnings.
##      It would be nice having a FindBrisa.cmake and a UseBrisa.cmake
##  file like done for Qt - one to check for everything in advance

##############

###### setup
SET(BRISA_MODULES BrisaCore BrisaUpnp BrisaUtils)
SET(BRISA_FOUND_MODULES)
FOREACH(mod ${BRISA_MODULES})
    STRING(TOUPPER ${mod} U_MOD)
    SET(BRISA_${U_MOD}_INCLUDE_DIR NOTFOUND)
    SET(BRISA_${U_MOD}_LIB_DEBUG NOTFOUND)
    SET(BRISA_${U_MOD}_LIB_RELEASE NOTFOUND)
    SET(BRISA_FOUND_${U_MOD} FALSE)
ENDFOREACH(mod)
SET(BRISA_BRISAUPNP_DEPENDSON BrisaCore BrisaUtils)

FOREACH(mod ${BRISA_MODULES})
    STRING(TOUPPER ${mod} U_MOD)
    FIND_PATH(BRISA_${U_MOD}_INCLUDE_DIR ${mod}
        PATH_SUFFIXES ${mod} include/${mod} Brisa/include/${mod} include/Brisa/${mod}
        PATHS
        ~/Library/Frameworks/
        /Library/Frameworks/
        /sw/
        /usr/local/
        /usr
        /opt/local/
        /opt/csw
        /opt
        "C:\\"
        "C:\\Program Files\\"
        "C:\\Program Files(x86)\\"
        NO_DEFAULT_PATH
    )
    FIND_LIBRARY(BRISA_${U_MOD}_LIB_RELEASE NAME ${mod}
        PATH_SUFFIXES Brisa/lib64 Brisa/lib lib64 lib
        PATHS
        /sw
        /usr/local
        /usr
        /opt/local
        /opt/csw
        /opt
        "C:\\"
        "C:\\Program Files"
        "C:\\Program Files(x86)"
        NO_DEFAULT_PATH
    )
    FIND_LIBRARY(BRISA_${U_MOD}_LIB_DEBUG NAME ${mod}d
        PATH_SUFFIXES Brisa/lib64 Brisa/lib lib64 lib
        PATHS
        /sw
        /usr/local
        /usr
        /opt/local
        /opt/csw
        /opt
        "C:\\"
        "C:\\Program Files"
        "C:\\Program Files(x86)"
        NO_DEFAULT_PATH
    )
    IF (BRISA_${U_MOD}_LIB_RELEASE)
        SET(BRISA_FOUND_MODULES "${BRISA_FOUND_MODULES} ${mod}")
    ENDIF (BRISA_${U_MOD}_LIB_RELEASE)

    IF (BRISA_${U_MOD}_LIB_DEBUG)
        SET(BRISA_FOUND_MODULES "${BRISA_FOUND_MODULES} ${mod}")
    ENDIF (BRISA_${U_MOD}_LIB_DEBUG)
ENDFOREACH(mod)

FOREACH(mod ${BRISA_MODULES})
    STRING(TOUPPER ${mod} U_MOD)
    IF(BRISA_${U_MOD}_INCLUDE_DIR AND BRISA_${U_MOD}_LIB_RELEASE)
        SET(BRISA_FOUND_${U_MOD} TRUE)
    ENDIF(BRISA_${U_MOD}_INCLUDE_DIR AND BRISA_${U_MOD}_LIB_RELEASE)
ENDFOREACH(mod)

##### find and include
# To use a Brisa Library...
#   SET(BRISA_FIND_COMPONENTS BrisaCore, BrisaUpnp, BrisaUtils)
# ...and this will do the rest
IF( BRISA_FIND_COMPONENTS )
    FOREACH( component ${BRISA_FIND_COMPONENTS} )
        STRING( TOUPPER ${component} _COMPONENT )
        SET(BRISA_USE_${_COMPONENT}_COMPONENT TRUE)
    ENDFOREACH( component )
ENDIF( BRISA_FIND_COMPONENTS )

SET(BRISA_LIBRARIES "")
SET(BRISA_INCLUDE_DIRS "")

# like FindQt4.cmake, in order of dependence
FOREACH( module ${BRISA_MODULES} )
    STRING(TOUPPER ${module} U_MOD)
    IF(BRISA_USE_${U_MOD} OR BRISA_DEPENDS_${U_MOD})
        IF(BRISA_FOUND_${U_MOD})
            STRING(REPLACE "BRISA" "" qxt_module_def "${U_MOD}")
            ADD_DEFINITIONS(-DBRISA_${qxt_module_def}_LIB)
            SET(BRISA_INCLUDE_DIRS ${BRISA_INCLUDE_DIRS} ${BRISA_${U_MOD}_INCLUDE_DIR})
            INCLUDE_DIRECTORIES(${BRISA_${U_MOD}_INCLUDE_DIR})
            SET(BRISA_LIBRARIES ${BRISA_LIBRARIES} ${BRISA_${U_MOD}_LIB_RELEASE})
        ELSE(BRISA_FOUND_${U_MOD})
            MESSAGE("Could not find Brisa Module ${module}")
            RETURN()
        ENDIF(BRISA_FOUND_${U_MOD})
        FOREACH(dep BRISA_${U_MOD}_DEPENDSON)
            SET(BRISA_DEPENDS_${dep} TRUE)
        ENDFOREACH(dep)
    ENDIF(BRISA_USE_${U_MOD} OR BRISA_DEPENDS_${U_MOD})
ENDFOREACH(module)
MESSAGE(STATUS "Found Brisa Libraries:${BRISA_FOUND_MODULES}")
