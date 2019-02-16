#-------------------------------------------------
#
# Project created by QtCreator 2018-06-16T00:15:32
#
#-------------------------------------------------

QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

include(./log4qt/log4qt.pri)

CONFIG += no_batch

TARGET = qvs
TEMPLATE = app
DEFINES += QT_DEPRECATED_WARNINGS

ARCHITECTURE_64_BIT = true

VER_MAJ = 1
VERSION = $$VER_MAJ
QMAKE_TARGET_PRODUCT = 'Qvs'
QMAKE_TARGET_DESCRIPTION = 'Qvs'
QMAKE_TARGET_COMPANY = 'ema'
QMAKE_TARGET_COPYRIGHT = $$QMAKE_TARGET_COMPANY

MOC_DIR = $$PWD/generated/moc
UI_DIR = $$PWD/generated/ui
RCC_DIR = $$PWD/generated/rcc

RC_ICONS = $$PWD/res/icons/qvs.ico

CONFIG(debug, debug|release) {
    contains(QMAKE_COMPILER, gcc) {
        if($$ARCHITECTURE_64_BIT) {
            DESTDIR = $$PWD/build/debug-64bit-gcc
            OBJECTS_DIR = $$PWD/generated/obj-debug-64bit-gcc
        } else {
            DESTDIR = $$PWD/build/debug-32bit-gcc
            OBJECTS_DIR = $$PWD/generated/obj-debug-32bit-gcc
        }

        QMAKE_CXXFLAGS += -O0
        QMAKE_CXXFLAGS += -g
        QMAKE_CXXFLAGS += -ggdb3
    }

    contains(QMAKE_COMPILER, msvc) {
        if($$ARCHITECTURE_64_BIT) {
            DESTDIR = $$PWD/build/debug-64bit-msvc
            TARGET = qvs-debug-64bit-msvc
            OBJECTS_DIR = $$PWD/generated/obj-debug-64bit-msvc
        } else {
            DESTDIR = $$PWD/build/debug-32bit-msvc
            TARGET = qvs-debug-32bit-msvc
            OBJECTS_DIR = $$PWD/generated/obj-debug-32bit-msvc
        }
    }
    #LIBS += -L$$PWD/opencv/lib -lopencv_world343d
    LIBS += -L$$PWD/qtav/lib   -lQtAVd1
    LIBS += -L$$PWD/qtav/lib   -lQtAVWidgetsd1

} else {
    contains(QMAKE_COMPILER, gcc) {
        if($$ARCHITECTURE_64_BIT) {
            DESTDIR = $$PWD/build/release-64bit-gcc
            OBJECTS_DIR = $$PWD/generated/obj-release-64bit-gcc
        } else {
            DESTDIR = $$PWD/build/release-32bit-gcc
            OBJECTS_DIR = $$PWD/generated/obj-release-32bit-gcc
        }

        QMAKE_CXXFLAGS += -O2
        QMAKE_CXXFLAGS += -fexpensive-optimizations
        QMAKE_CXXFLAGS += -funit-at-a-time
    }

    contains(QMAKE_COMPILER, msvc) {
        if($$ARCHITECTURE_64_BIT) {
            DESTDIR = $$PWD/build/release-64bit-msvc
            OBJECTS_DIR = $$PWD/generated/obj-release-64bit-msvc
        } else {
            DESTDIR = $$PWD/build/release-32bit-msvc
            OBJECTS_DIR = $$PWD/generated/obj-release-32bit-msvc
        }
    }
    #LIBS += -L$$PWD/opencv/lib -lopencv_world343
    LIBS += -L$$PWD/qtav/lib   -lQtAV1
    LIBS += -L$$PWD/qtav/lib   -lQtAVWidgets1
}

#INCLUDEPATH += $$PWD/opencv/include
#INCLUDEPATH += $$PWD/opencv/include/opencv
#INCLUDEPATH += $$PWD/opencv/include/opencv2
INCLUDEPATH += $$PWD/ffmpeg/include
#INCLUDEPATH += $$PWD/sdl/include
INCLUDEPATH += $$PWD/qtav/include
INCLUDEPATH += $$PWD/qtav/include/QtAV
INCLUDEPATH += $$PWD/qtav/include/QtAVWidgets

LIBS += -L$$PWD/ffmpeg/lib -lavcodec
LIBS += -L$$PWD/ffmpeg/lib -lavdevice
LIBS += -L$$PWD/ffmpeg/lib -lavfilter
LIBS += -L$$PWD/ffmpeg/lib -lavformat
LIBS += -L$$PWD/ffmpeg/lib -lavutil
LIBS += -L$$PWD/ffmpeg/lib -lpostproc
LIBS += -L$$PWD/ffmpeg/lib -lswresample
LIBS += -L$$PWD/ffmpeg/lib -lswscale
LIBS += -L$$PWD/ffmpeg/lib -lavcodec
#LIBS += -L$$PWD/sdl/lib    -lSDL2
#LIBS += -L$$PWD/sdl/lib    -lSDL2main


S = $${DIR_SEPARATOR}

D = $$DESTDIR
D = $$replace(D, $$escape_expand(\\), $$S)
D = $$replace(D, /, $$S)

E = $$escape_expand(\n\t)

win32 {
    QT += winextras

    DEPLOY_COMMAND = windeployqt
    DEPLOY_TARGET = $$shell_quote($$shell_path($${D}/$${TARGET}.exe))
#    QMAKE_POST_LINK += $${DEPLOY_COMMAND} --no-translations $${DEPLOY_TARGET} $${E}

    if($$ARCHITECTURE_64_BIT) {
        message("x86_64 build")
    } else {
        message("x86 build")
        contains(QMAKE_COMPILER, gcc) {
                QMAKE_LFLAGS += -Wl,--large-address-aware
        }
        contains(QMAKE_COMPILER, msvc) {
                QMAKE_LFLAGS += /LARGEADDRESSAWARE
        }
    }
}

SOURCES += main.cpp
SOURCES += mainwindow.cpp
SOURCES += com/common.cpp
SOURCES += com/preferences.cpp
SOURCES += com/timer.cpp
SOURCES += com/mail_box.cpp
SOURCES += com/config.cpp
SOURCES += com/app_instance_file_guard.cpp
SOURCES += com/style_sheet.cpp
SOURCES += com/logging.cpp
SOURCES += com/line_parser.cpp
SOURCES += job/job_creator.cpp
SOURCES += job/job_creator_help.cpp
SOURCES += job/job_chef.cpp
SOURCES += job/job_view_cmd.cpp
SOURCES += tools/muxer.cpp
SOURCES += tools/std_watcher.cpp
SOURCES += tools/std_manager.cpp
SOURCES += tools/demuxer.cpp
SOURCES += tools/audio_enc.cpp
SOURCES += tools/installer_dialog.cpp
SOURCES += tools/audio_config.cpp
SOURCES += tools/merge.cpp
SOURCES += tools/splitter.cpp
SOURCES += tools/splitter_config.cpp
SOURCES += preview/preview_dialog.cpp
SOURCES += preview/preview_area.cpp
SOURCES += preview/scroll_navigator.cpp
SOURCES += preview/statistics_view.cpp
SOURCES += preview/preview_timeline_slider.cpp
#SOURCES += preview/video_preview.cpp
SOURCES += mediainfo/mediainfo_prober.cpp 
SOURCES += mediainfo/mediainfo_dialog.cpp
SOURCES += mediainfo/mediainfo_loader.cpp
SOURCES += mediainfo/mediainfo_list.cpp
SOURCES += script/script_player.cpp
SOURCES += script/script_editor.cpp
SOURCES += script/syntax_highlighter.cpp
SOURCES += script/script_creator.cpp
SOURCES += script/number_matcher.cpp

HEADERS += mainwindow.h
HEADERS += com/common.h
HEADERS += com/preferences.h
HEADERS += com/mail_box.h
HEADERS += com/timer.h
HEADERS += com/config.h
HEADERS += com/app_instance_file_guard.h
HEADERS += com/style_sheet.h
HEADERS += com/version.h
HEADERS += com/logging.h
HEADERS += com/line_parser.h
HEADERS += job/job_creator.h
HEADERS += job/job_creator_help.h
HEADERS += job/job_chef.h
HEADERS += job/job_view_cmd.h
HEADERS += job/job_cmdlist.h
HEADERS += job/job_item.h
HEADERS += tools/muxer.h
HEADERS += tools/std_watcher.h
HEADERS += tools/std_manager.h
HEADERS += tools/demuxer.h
HEADERS += tools/audio_enc.h
HEADERS += tools/installer_dialog.h
HEADERS += tools/audio_config.h
HEADERS += tools/merge.h
HEADERS += tools/splitter.h
HEADERS += tools/splitter_config.h
HEADERS += preview/preview_dialog.h
HEADERS += preview/preview_area.h
HEADERS += preview/scroll_navigator.h
HEADERS += preview/statistics_view.h
HEADERS += preview/preview_timeline_slider.h
HEADERS += preview/video_info.hpp
#HEADERS += preview/video_preview.h
HEADERS += mediainfo/mediainfo_define.h
HEADERS += mediainfo/mediainfo_dialog.h
HEADERS += mediainfo/mediainfo_loader.h
HEADERS += mediainfo/mediainfo_list.h
HEADERS += mediainfo/mediainfo_enum.h
HEADERS += mediainfo/mediainfo_prober.h 
HEADERS += mediainfo/mediainfo_pixfmt.hpp 
HEADERS += script/script_player.h
HEADERS += script/script_editor.h
HEADERS += script/syntax_highlighter.h
HEADERS += script/script_creator.h
HEADERS += script/number_matcher.h

FORMS += mainwindow.ui
FORMS += com/preferences.ui
FORMS += job/job_creator.ui
FORMS += job/job_creator_help.ui
FORMS += job/job_view_cmd.ui
FORMS += mediainfo/mediainfo_dialog.ui
FORMS += script/script_player.ui
FORMS += script/script_creator.ui
FORMS += tools/installer_dialog.ui
FORMS += tools/muxer.ui
FORMS += tools/std_watcher.ui
FORMS += tools/demuxer.ui
FORMS += tools/audio_enc.ui
FORMS += tools/audio_config.ui
FORMS += tools/merge.ui
FORMS += tools/splitter.ui
FORMS += tools/splitter_config.ui
FORMS += preview/preview_dialog.ui

RESOURCES += res/resources.qrc
