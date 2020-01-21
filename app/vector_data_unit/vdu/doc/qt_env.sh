#!/bin/sh


##qt5.9.1-arm


QT_ROOT=/opt/qt5.9.1-arm
PATH=$QTDIR/bin:$PATH

LD_LIBRARY_PATH=/lib:/usr/lib:/usr/local/lib:$QT_ROOT/lib
QT_QPA_PLATFORM_PLUGIN_PATH=$QT_ROOT/plugins
QT_QPA_PLATFORM=linuxfb:tty=/dev/fb0
QT_QPA_FONTDIR=$QT_ROOT/lib/fonts
QML2_IMPORT_PATH=$QT_ROOT/qml
QT_QPA_PLATFORM=eglfs
QT_QPA_EGLFS_PHYSICAL_WIDTH=3840					#根据你的显示器设置宽度，单位mm
QT_QPA_EGLFS_PHYSICAL_HEIGHT=2160					#根据你的显示器设置高度，单位mm
