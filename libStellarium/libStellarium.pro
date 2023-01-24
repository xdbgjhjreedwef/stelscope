QT       += core network concurrent
QT       -= gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += lib c++14

TEMPLATE = lib

DEFINES += STELLARIUM_LIBRARY

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
INCLUDEPATH += stellarium_src
INCLUDEPATH += stellarium_src/core
INCLUDEPATH += stellarium_src/core/modules
INCLUDEPATH += stellarium_src/core/planetsephems

SOURCES += \
    stellarium_src/StelLogger.cpp \
    stellarium_src/core/GeomMath.cpp \
    stellarium_src/core/OctahedronPolygon.cpp \
    stellarium_src/core/RefractionExtinction.cpp \
    stellarium_src/core/StelApp.cpp \
    stellarium_src/core/StelCore.cpp \
    stellarium_src/core/StelFileMgr.cpp \
    stellarium_src/core/StelGeodesicGrid.cpp \
    stellarium_src/core/StelHips.cpp \
    stellarium_src/core/StelIniParser.cpp \
    stellarium_src/core/StelJsonParser.cpp \
    stellarium_src/core/StelLocation.cpp \
    stellarium_src/core/StelLocationMgr.cpp \
    stellarium_src/core/StelModule.cpp \
    stellarium_src/core/StelModuleMgr.cpp \
    stellarium_src/core/StelOBJ.cpp \
    stellarium_src/core/StelObject.cpp \
    stellarium_src/core/StelObjectMgr.cpp \
    stellarium_src/core/StelObjectModule.cpp \
    stellarium_src/core/StelObserver.cpp \
    stellarium_src/core/StelProjector.cpp \
    stellarium_src/core/StelProjectorClasses.cpp \
    stellarium_src/core/StelPropertyMgr.cpp \
    stellarium_src/core/StelSphereGeometry.cpp \
    stellarium_src/core/StelUtils.cpp \
    stellarium_src/core/StelVertexArray.cpp \
    stellarium_src/core/VecMath.cpp \
    stellarium_src/core/healpix.c \
    stellarium_src/core/modules/Atmosphere.cpp \
    stellarium_src/core/modules/Comet.cpp \
    stellarium_src/core/modules/HipsMgr.cpp \
    stellarium_src/core/modules/Landscape.cpp \
    stellarium_src/core/modules/LandscapeMgr.cpp \
    stellarium_src/core/modules/MilkyWay.cpp \
    stellarium_src/core/modules/MinorPlanet.cpp \
    stellarium_src/core/modules/Nebula.cpp \
    stellarium_src/core/modules/NebulaMgr.cpp \
    stellarium_src/core/modules/NomenclatureItem.cpp \
    stellarium_src/core/modules/NomenclatureMgr.cpp \
    stellarium_src/core/modules/Orbit.cpp \
    stellarium_src/core/modules/Planet.cpp \
    stellarium_src/core/modules/RotationElements.cpp \
    stellarium_src/core/modules/SolarSystem.cpp \
    stellarium_src/core/modules/Star.cpp \
    stellarium_src/core/modules/StarMgr.cpp \
    stellarium_src/core/modules/StarWrapper.cpp \
    stellarium_src/core/modules/ZoneArray.cpp \
    stellarium_src/core/planetsephems/EphemWrapper.cpp \
    stellarium_src/core/planetsephems/calc_interpolated_elements.c \
    stellarium_src/core/planetsephems/de430.cpp \
    stellarium_src/core/planetsephems/de431.cpp \
    stellarium_src/core/planetsephems/de440.cpp \
    stellarium_src/core/planetsephems/de441.cpp \
    stellarium_src/core/planetsephems/elliptic_to_rectangular.c \
    stellarium_src/core/planetsephems/elp82b.c \
    stellarium_src/core/planetsephems/gust86.c \
    stellarium_src/core/planetsephems/htc20b.cpp \
    stellarium_src/core/planetsephems/jpleph.cpp \
    stellarium_src/core/planetsephems/l12.c \
    stellarium_src/core/planetsephems/marssat.c \
    stellarium_src/core/planetsephems/pluto.c \
    stellarium_src/core/planetsephems/precession.c \
    stellarium_src/core/planetsephems/sidereal_time.c \
    stellarium_src/core/planetsephems/tass17.c \
    stellarium_src/core/planetsephems/vsop87.c


HEADERS += \
    stellarium_src/StelLogger.hpp \
    stellarium_src/core/GeomMath.hpp \
    stellarium_src/core/OctahedronPolygon.hpp \
    stellarium_src/core/RefractionExtinction.hpp \
    stellarium_src/core/StelApp.hpp \
    stellarium_src/core/StelCore.hpp \
    stellarium_src/core/StelFader.hpp \
    stellarium_src/core/StelFileMgr.hpp \
    stellarium_src/core/StelGeodesicGrid.hpp \
    stellarium_src/core/StelHips.hpp \
    stellarium_src/core/StelIniParser.hpp \
    stellarium_src/core/StelJsonParser.hpp \
    stellarium_src/core/StelLocation.hpp \
    stellarium_src/core/StelLocationMgr.hpp \
    stellarium_src/core/StelLocationMgr_p.hpp \
    stellarium_src/core/StelModule.hpp \
    stellarium_src/core/StelModuleMgr.hpp \
    stellarium_src/core/StelOBJ.hpp \
    stellarium_src/core/StelObject.hpp \
    stellarium_src/core/StelObjectMgr.hpp \
    stellarium_src/core/StelObjectModule.hpp \
    stellarium_src/core/StelObjectType.hpp \
    stellarium_src/core/StelObserver.hpp \
    stellarium_src/core/StelPluginInterface.hpp \
    stellarium_src/core/StelProjector.hpp \
    stellarium_src/core/StelProjectorClasses.hpp \
    stellarium_src/core/StelProjectorType.hpp \
    stellarium_src/core/StelPropertyMgr.hpp \
    stellarium_src/core/StelRegionObject.hpp \
    stellarium_src/core/StelSphereGeometry.hpp \
    stellarium_src/core/StelUtils.hpp \
    stellarium_src/core/StelVertexArray.hpp \
    stellarium_src/core/VecMath.hpp \
    stellarium_src/core/modules/Atmosphere.hpp \
    stellarium_src/core/modules/Comet.hpp \
    stellarium_src/core/modules/HipsMgr.hpp \
    stellarium_src/core/modules/Landscape.hpp \
    stellarium_src/core/modules/LandscapeMgr.hpp \
    stellarium_src/core/modules/MilkyWay.hpp \
    stellarium_src/core/modules/MinorPlanet.hpp \
    stellarium_src/core/modules/Nebula.hpp \
    stellarium_src/core/modules/NebulaList.hpp \
    stellarium_src/core/modules/NebulaMgr.hpp \
    stellarium_src/core/modules/NomenclatureItem.hpp \
    stellarium_src/core/modules/NomenclatureMgr.hpp \
    stellarium_src/core/modules/Orbit.hpp \
    stellarium_src/core/modules/Planet.hpp \
    stellarium_src/core/modules/RotationElements.hpp \
    stellarium_src/core/modules/SolarSystem.hpp \
    stellarium_src/core/modules/Solve.hpp \
    stellarium_src/core/modules/Star.hpp \
    stellarium_src/core/modules/StarMgr.hpp \
    stellarium_src/core/modules/StarWrapper.hpp \
    stellarium_src/core/modules/ZoneArray.hpp \
    stellarium_src/core/modules/ZoneData.hpp \
    stellarium_src/core/planetsephems/EphemWrapper.hpp \
    stellarium_src/core/planetsephems/calc_interpolated_elements.h \
    stellarium_src/core/planetsephems/de430.hpp \
    stellarium_src/core/planetsephems/de431.hpp \
    stellarium_src/core/planetsephems/de440.hpp \
    stellarium_src/core/planetsephems/de441.hpp \
    stellarium_src/core/planetsephems/elliptic_to_rectangular.h \
    stellarium_src/core/planetsephems/elp82b.h \
    stellarium_src/core/planetsephems/gust86.h \
    stellarium_src/core/planetsephems/htc20b.hpp \
    stellarium_src/core/planetsephems/jpl_int.h \
    stellarium_src/core/planetsephems/jpleph.h \
    stellarium_src/core/planetsephems/l12.h \
    stellarium_src/core/planetsephems/marssat.h \
    stellarium_src/core/planetsephems/pluto.h \
    stellarium_src/core/planetsephems/precession.h \
    stellarium_src/core/planetsephems/sidereal_time.h \
    stellarium_src/core/planetsephems/tass17.h \
    stellarium_src/core/planetsephems/vsop87.h \
    stellarium_src/libstellarium-global.h

STELLARIUM_SOURCE_DIR="./"
INSTALL_DATADIR="/home/qwerty/qt/StelScope/libStellarium/stel_data/"
STELLARIUM_VERSION="0"
GIT_REVISION="0"
PACKAGE_VERSION="0"
GIT_BRANCH="gutted"
GUTTED_FILEPATH="/qt/"
DEFINES += "INSTALL_DATADIR=\\\"$$INSTALL_DATADIR\\\""
DEFINES += "STELLARIUM_SOURCE_DIR=\\\"$$STELLARIUM_SOURCE_DIR\\\""
DEFINES += "STELLARIUM_VERSION=\\\"$$STELLARIUM_VERSION\\\""
DEFINES += "GIT_REVISION=\\\"$$GIT_REVISION\\\""
DEFINES += "PACKAGE_VERSION=\\\"$$PACKAGE_VERSION\\\""
DEFINES += "GIT_BRANCH=\\\"$$GIT_BRANCH\\\""

GUTTED_FILEPATH = "/qt/StelScope/libStellarium/stel_data/"
DEFINES += "GUTTED_FILEPATH=\\\"$$GUTTED_FILEPATH\\\""
#STELLARIUM_DATA_ROOT="/home/qwerty/qt/Stellarium_gutted/stel_data/"

FORMS +=

LIBS += -lz

# Default rules for deployment.
#qnx: target.path = /tmp/$${TARGET}/bin
#else: unix:!android: target.path = /opt/$${TARGET}/bin
#!isEmpty(target.path): INSTALLS += target
