#-------------------------------------------------
#
# Project created by QtCreator 2013-04-06T06:47:59
#
#-------------------------------------------------

QT          += core gui widgets
TARGET      = qt_app_000_fft_audio
TEMPLATE    = app

#------------------------------------------------------------
# RtAudio library settings
RTAUDIO_PATH        = /home/franto/builds/libs/rtaudio/rtaudio-4.1.1
RTAUDIO_PATH_INC    = $${RTAUDIO_PATH}
RTAUDIO_PATH_INC2   = $${RTAUDIO_PATH}/include

DEFINES     += __LINUX_PULSE__
INCLUDEPATH += $${RTAUDIO_PATH_INC}
LIBS        += -lpulse-simple -lpulse

#DEFINES     += __UNIX_JACK__
#INCLUDEPATH += $${RTAUDIO_PATH_INC}
#LIBS        += -lasound -ljack

#DEFINES     += __LINUX_ALSA__
#INCLUDEPATH += $${RTAUDIO_PATH_INC}
#LIBS        += -lasound

#------------------------------------------------------------
# Qwt library settings
QWT_PATH        = /home/franto/builds/libs/qwt/qwt_620_trunk140414
QWT_PATH_INC    = $${QWT_PATH}/src
QWT_PATH_LIB    = $${QWT_PATH}/lib

win32:CONFIG(release, debug|release):    LIBS += -L$$PWD/../../builds/libs/qwt/qwt_620_trunk140414/lib/release/ -lqwt
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../builds/libs/qwt/qwt_620_trunk140414/lib/debug/ -lqwt
else:unix: LIBS += -L$${QWT_PATH_LIB} -lqwt

INCLUDEPATH += $${QWT_PATH_INC}
DEPENDPATH  += $${QWT_PATH_INC}

#------------------------------------------------------------
# FFTW library settings
# There is conflict(?) where the lib is installed when built from source code
# and when installed via apt-get. This was the issue when guilding some other
# program - Ardour or some audio pulgins? Anyway, library installed from source
# had to be uninstalled and used one provided via apt-get. Folders are :
# source built :    /usr/local/lib/
# apt-get install : /usr/lib/x86_64-linux-gnu/
FFTW_BUILT_INSTALL_DIR_LIB = /usr/local/lib
FFTW_BUILT_INSTALL_DIR_INC = /usr/local/include

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../usr/local/lib/release/ -lfftw3
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../usr/local/lib/debug/ -lfftw3
#else:unix: LIBS += -L$${FFTW_BUILT_INSTALL_DIR} -lfftw3
else:unix: LIBS += -lfftw3

INCLUDEPATH += $${FFTW_BUILT_INSTALL_DIR_INC}
DEPENDPATH  += $${FFTW_BUILT_INSTALL_DIR_INC}

#------------------------------------------------------------
# STK library settings
STK_PATH        = /home/franto/builds/libs/stk/stk-4.5.0
STK_PATH_INC    = $${STK_PATH}/include
STK_PATH_SRC    = $${STK_PATH}/src
STK_PATH_SRC_INC = $${STK_PATH}/src/include
STK_PATH_LIB    = $${STK_PATH}/src

#------------------------------------------------------------
# Compiler settings
QMAKE_CXXFLAGS  += -P   # keep temporary files e.g. preprocessor output .i
DEFINES         += _CRT_SECURE_NO_WARNINGS  # disable compiler warning: C4996: 'strcpy': This function or variable may be unsafe
QMAKE_CXXFLAGS  += -std=c++11

#------------------------------------------------------------
# Source files
SOURCES +=      \
    main.cpp    \
    mainWin.cpp \
    sliders.cpp \
    datafft.cpp \
    audiosource.cpp \
    $${RTAUDIO_PATH}/RtAudio.cpp

HEADERS +=      \
    mainWin.h \
    sliders.h \
    datafft.h \
    audiosource.h \
    parameters.h

#------------------------------------------------------------
# Other files
OTHER_FILES += \
    LICENSE.md \
    README.md \
    .gitignore \
    qt_app_000_fft_audio.pro.win
