QT       += core gui charts \
    widgets

#greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++14

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
#INCLUDEPATH += stellarium_math/

INCLUDEPATH += $$PWD/../libStellarium/stellarium_src/
INCLUDEPATH += $$PWD/../libStellarium/stellarium_src/core

#INCLUDEPATH += /home/qwerty/qt/qtcharts-6.4/src/charts/xychart/
#INCLUDEPATH += /home/qwerty/qt/qtcharts-6.4/src/charts/scatterchart/

SOURCES += \
    chartview.cpp \
    main.cpp \
    mainwindow.cpp \

HEADERS += \
    chartview.h \
    mainwindow.h \

FORMS +=

# Default rules for deployment.
#qnx: target.path = /tmp/$${TARGET}/bin
#else: unix:!android: target.path = /opt/$${TARGET}/bin
#!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc

LIBS += -L$$OUT_PWD/../libStellarium/ -llibStellarium
