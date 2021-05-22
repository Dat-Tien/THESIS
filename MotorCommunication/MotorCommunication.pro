QT       += core gui network serialport sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

#TARGET = SerialPort

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    capture.cpp \
    dialogfile.cpp \
    main.cpp \
    mainwindow.cpp \
    udp.cpp

HEADERS += \
    capture.h \
    dialogfile.h \
    mainwindow.h \
    udp.h

FORMS += \
    dialogfile.ui \
    mainwindow.ui

#add librealsense
LIBS += -L'C:/Program Files (x86)/Intel RealSense SDK 2.0/lib/x64/' -lrealsense2

INCLUDEPATH += 'C:/Program Files (x86)/Intel RealSense SDK 2.0/include'
DEPENDPATH += 'C:/Program Files (x86)/Intel RealSense SDK 2.0/include'

#add opencv
LIBS += C:\openCV\opencv\release\bin\libopencv_core451.dll
LIBS += C:\openCV\opencv\release\bin\libopencv_highgui451.dll
LIBS += C:\openCV\opencv\release\bin\libopencv_imgcodecs451.dll
LIBS += C:\openCV\opencv\release\bin\libopencv_imgproc451.dll
LIBS += C:\openCV\opencv\release\bin\libopencv_calib3d451.dll
LIBS += C:\openCV\opencv\release\bin\libopencv_videoio451.dll

INCLUDEPATH += C:/OpenCV/opencv/build/include
DEPENDPATH += C:/OpenCV/opencv/build/include


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target






QMAKE_CXXFLAGS += -std=gnu++14
