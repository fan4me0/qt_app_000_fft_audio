#-------------------------------------------------
#
# Project created by QtCreator 2013-04-06T06:47:59
#
#-------------------------------------------------

QT          += core gui widgets
TARGET      = qt_app_000_fft_audio
TEMPLATE    = app

QMAKE_CXXFLAGS += -std=c++11

#------------------------------------------------------------
# Qwt library settings

QWT_PATH = /home/franto/builds/libs/qwt/qwt_620_trunk140414
QWT_PATH_INC = $${QWT_PATH}/src
QWT_PATH_LIB = $${QWT_PATH}/lib

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../builds/libs/qwt/qwt_620_trunk140414/lib/release/ -lqwt
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../builds/libs/qwt/qwt_620_trunk140414/lib/debug/ -lqwt
else:unix: LIBS += -L$${QWT_PATH_LIB} -lqwt

INCLUDEPATH += $${QWT_PATH_INC}
DEPENDPATH += $${QWT_PATH_INC}


#------------------------------------------------------------
# FFTW library settings
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../usr/local/lib/release/ -lfftw3
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../usr/local/lib/debug/ -lfftw3
#else:unix: LIBS += -L$$PWD/../../../../usr/local/lib/ -lfftw3
else:unix: LIBS += -lfftw3

INCLUDEPATH += $$PWD/../../../../usr/local/include
DEPENDPATH += $$PWD/../../../../usr/local/include

#win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../../../usr/local/lib/release/libfftw3.a
#else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../../../usr/local/lib/debug/libfftw3.a
#else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../../../usr/local/lib/release/fftw3.lib
#else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../../../usr/local/lib/debug/fftw3.lib
#else:unix: PRE_TARGETDEPS += $$PWD/../../../../usr/local/lib/libfftw3.a


#------------------------------------------------------------
# STK library settings
STK_PATH = /home/franto/builds/libs/stk/stk-4.5.0
STK_PATH_INC = /home/franto/builds/libs/stk/stk-4.5.0/include
STK_PATH_SRC = /home/franto/builds/libs/stk/stk-4.5.0/src
STK_PATH_SRC_INC = /home/franto/builds/libs/stk/stk-4.5.0/src/include
STK_PATH_LIB = /home/franto/builds/libs/stk/stk-4.5.0/src

#DEFINES     += __LINUX_ALSA__
DEFINES     += __LINUX_PULSE__
INCLUDEPATH += $${STK_PATH_INC}
LIBS += -lpulse-simple -lpulse
#LIBS += -L$${STK_PATH_LIB} -lstk_dbg

#------------------------------------------------------------
QMAKE_CXXFLAGS += -P   # keep temporary files e.g. preprocessor output .i
DEFINES     += _CRT_SECURE_NO_WARNINGS  # disable compiler warning: C4996: 'strcpy': This function or variable may be unsafe

SOURCES +=      \
    main.cpp    \
    mainWin.cpp \
    sliders.cpp \
    datafft.cpp \
    audiosource.cpp \
    $${STK_PATH_SRC}/RtAudio.cpp

FORMS    +=

HEADERS +=      \
    mainWin.h \
    sliders.h \
    datafft.h \
    audiosource.h \
    parameters.h

OTHER_FILES += \
    LICENSE.md \
    README.md \
    .gitignore \
    qt_app_000_fft_audio.pro.win
