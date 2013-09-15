#############################################################################
# Makefile for building: uPnP
# Generated by qmake (2.01a) (Qt 4.8.4) on: ?? ??? 15 13:34:30 2013
# Project:  uPnP.pro
# Template: app
# Command: /usr/bin/qmake -o Makefile uPnP.pro
#############################################################################

####### Compiler, tools and options

CC            = gcc
CXX           = g++
DEFINES       = -DQT_GUI_LIB -DQT_CORE_LIB -DQT_SHARED
CFLAGS        = -pipe -g -pthread -D_REENTRANT -Wall -W $(DEFINES)
CXXFLAGS      = -pipe -std=c++0x -g -DDEBUG -Iinclude -g -pthread -D_REENTRANT -Wall -W $(DEFINES)
INCPATH       = -I/usr/share/qt4/mkspecs/linux-g++ -I. -I/usr/include/qt4/QtCore -I/usr/include/qt4/QtGui -I/usr/include/qt4 -I/usr/include/upnp -I. -I.
LINK          = g++
LFLAGS        = 
LIBS          = $(SUBLIBS)  -L/usr/lib64/qt4 -pthread -lupnp -lthreadutil -lixml -lQtGui -L/usr/lib64 -L/usr/lib64/qt4 -L/usr/X11R6/lib -lQtCore -lgthread-2.0 -lrt -lglib-2.0 -lpthread 
AR            = ar cqs
RANLIB        = 
QMAKE         = /usr/bin/qmake
TAR           = tar -cf
COMPRESS      = gzip -9f
COPY          = cp -f
SED           = sed
COPY_FILE     = $(COPY)
COPY_DIR      = $(COPY) -r
STRIP         = strip
INSTALL_FILE  = install -m 644 -p
INSTALL_DIR   = $(COPY_DIR)
INSTALL_PROGRAM = install -m 755 -p
DEL_FILE      = rm -f
SYMLINK       = ln -f -s
DEL_DIR       = rmdir
MOVE          = mv -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p

####### Output directory

OBJECTS_DIR   = ./

####### Files

SOURCES       = src/Config.cpp \
		src/Container.cpp \
		src/Device.cpp \
		src/DeviceList.cpp \
		src/Icon.cpp \
		src/Item.cpp \
		src/main.cpp \
		src/mainwindow.cpp \
		src/Service.cpp \
		src/TcpClient.cpp \
		src/Thread.cpp \
		src/UPnP_CP.cpp \
		src/UPnP_MediaServer.cpp \
		src/UPnP_MediaRenderer.cpp \
		src/xmltools.cpp \
		src/HttpClient.cpp \
		src/Log.cpp \
		src/UPnP.cpp moc_mainwindow.cpp \
		qrc_resorces.cpp
OBJECTS       = Config.o \
		Container.o \
		Device.o \
		DeviceList.o \
		Icon.o \
		Item.o \
		main.o \
		mainwindow.o \
		Service.o \
		TcpClient.o \
		Thread.o \
		UPnP_CP.o \
		UPnP_MediaServer.o \
		UPnP_MediaRenderer.o \
		xmltools.o \
		HttpClient.o \
		Log.o \
		UPnP.o \
		moc_mainwindow.o \
		qrc_resorces.o
DIST          = /usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/common/gcc-base.conf \
		/usr/share/qt4/mkspecs/common/gcc-base-unix.conf \
		/usr/share/qt4/mkspecs/common/g++-base.conf \
		/usr/share/qt4/mkspecs/common/g++-unix.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/modules/qt_phonon.pri \
		/usr/share/qt4/mkspecs/modules/qt_webkit_version.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		/usr/share/qt4/mkspecs/features/debug.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
		/usr/share/qt4/mkspecs/features/link_pkgconfig.prf \
		/usr/share/qt4/mkspecs/features/qt.prf \
		/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/usr/share/qt4/mkspecs/features/moc.prf \
		/usr/share/qt4/mkspecs/features/warn_on.prf \
		/usr/share/qt4/mkspecs/features/unix/gdb_dwarf_index.prf \
		/usr/share/qt4/mkspecs/features/resources.prf \
		/usr/share/qt4/mkspecs/features/uic.prf \
		/usr/share/qt4/mkspecs/features/yacc.prf \
		/usr/share/qt4/mkspecs/features/lex.prf \
		/usr/share/qt4/mkspecs/features/include_source_dir.prf \
		uPnP.pro
QMAKE_TARGET  = uPnP
DESTDIR       = 
TARGET        = uPnP

first: all
####### Implicit rules

.SUFFIXES: .o .c .cpp .cc .cxx .C

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cc.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.C.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.c.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o "$@" "$<"

####### Build rules

all: Makefile $(TARGET)

$(TARGET): ui_mainwindow.h $(OBJECTS)  
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJCOMP) $(LIBS)
	{ test -n "$(DESTDIR)" && DESTDIR="$(DESTDIR)" || DESTDIR=.; } && test $$(gdb --version | sed -e 's,[^0-9]\+\([0-9]\)\.\([0-9]\).*,\1\2,;q') -gt 72 && gdb --nx --batch --quiet -ex 'set confirm off' -ex "save gdb-index $$DESTDIR" -ex quit '$(TARGET)' && test -f $(TARGET).gdb-index && objcopy --add-section '.gdb_index=$(TARGET).gdb-index' --set-section-flags '.gdb_index=readonly' '$(TARGET)' '$(TARGET)' && rm -f $(TARGET).gdb-index || true

Makefile: uPnP.pro  /usr/share/qt4/mkspecs/linux-g++/qmake.conf /usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/common/gcc-base.conf \
		/usr/share/qt4/mkspecs/common/gcc-base-unix.conf \
		/usr/share/qt4/mkspecs/common/g++-base.conf \
		/usr/share/qt4/mkspecs/common/g++-unix.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/modules/qt_phonon.pri \
		/usr/share/qt4/mkspecs/modules/qt_webkit_version.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		/usr/share/qt4/mkspecs/features/debug.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
		/usr/share/qt4/mkspecs/features/link_pkgconfig.prf \
		/usr/share/qt4/mkspecs/features/qt.prf \
		/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/usr/share/qt4/mkspecs/features/moc.prf \
		/usr/share/qt4/mkspecs/features/warn_on.prf \
		/usr/share/qt4/mkspecs/features/unix/gdb_dwarf_index.prf \
		/usr/share/qt4/mkspecs/features/resources.prf \
		/usr/share/qt4/mkspecs/features/uic.prf \
		/usr/share/qt4/mkspecs/features/yacc.prf \
		/usr/share/qt4/mkspecs/features/lex.prf \
		/usr/share/qt4/mkspecs/features/include_source_dir.prf \
		/usr/lib64/qt4/libQtGui.prl \
		/usr/lib64/qt4/libQtCore.prl
	$(QMAKE) -o Makefile uPnP.pro
/usr/share/qt4/mkspecs/common/unix.conf:
/usr/share/qt4/mkspecs/common/linux.conf:
/usr/share/qt4/mkspecs/common/gcc-base.conf:
/usr/share/qt4/mkspecs/common/gcc-base-unix.conf:
/usr/share/qt4/mkspecs/common/g++-base.conf:
/usr/share/qt4/mkspecs/common/g++-unix.conf:
/usr/share/qt4/mkspecs/qconfig.pri:
/usr/share/qt4/mkspecs/modules/qt_phonon.pri:
/usr/share/qt4/mkspecs/modules/qt_webkit_version.pri:
/usr/share/qt4/mkspecs/features/qt_functions.prf:
/usr/share/qt4/mkspecs/features/qt_config.prf:
/usr/share/qt4/mkspecs/features/exclusive_builds.prf:
/usr/share/qt4/mkspecs/features/default_pre.prf:
/usr/share/qt4/mkspecs/features/debug.prf:
/usr/share/qt4/mkspecs/features/default_post.prf:
/usr/share/qt4/mkspecs/features/link_pkgconfig.prf:
/usr/share/qt4/mkspecs/features/qt.prf:
/usr/share/qt4/mkspecs/features/unix/thread.prf:
/usr/share/qt4/mkspecs/features/moc.prf:
/usr/share/qt4/mkspecs/features/warn_on.prf:
/usr/share/qt4/mkspecs/features/unix/gdb_dwarf_index.prf:
/usr/share/qt4/mkspecs/features/resources.prf:
/usr/share/qt4/mkspecs/features/uic.prf:
/usr/share/qt4/mkspecs/features/yacc.prf:
/usr/share/qt4/mkspecs/features/lex.prf:
/usr/share/qt4/mkspecs/features/include_source_dir.prf:
/usr/lib64/qt4/libQtGui.prl:
/usr/lib64/qt4/libQtCore.prl:
qmake:  FORCE
	@$(QMAKE) -o Makefile uPnP.pro

dist: 
	@$(CHK_DIR_EXISTS) .tmp/uPnP1.0.0 || $(MKDIR) .tmp/uPnP1.0.0 
	$(COPY_FILE) --parents $(SOURCES) $(DIST) .tmp/uPnP1.0.0/ && $(COPY_FILE) --parents include/mainwindow.h include/Device.h include/xmltools.h include/Service.h include/Uri.h include/Container.h include/Item.h include/Config.h include/UPnP_MediaServer.h include/UPnP_MediaRenderer.h include/UPnP_CP.h include/Device.h include/DeviceList.h include/HttpClient.h include/Icon.h include/TcpClient.h include/Thread.h include/UPnP.h include/Log.h .tmp/uPnP1.0.0/ && $(COPY_FILE) --parents resorces.qrc .tmp/uPnP1.0.0/ && $(COPY_FILE) --parents src/Config.cpp src/Container.cpp src/Device.cpp src/DeviceList.cpp src/Icon.cpp src/Item.cpp src/main.cpp src/mainwindow.cpp src/Service.cpp src/TcpClient.cpp src/Thread.cpp src/UPnP_CP.cpp src/UPnP_MediaServer.cpp src/UPnP_MediaRenderer.cpp src/xmltools.cpp src/HttpClient.cpp src/Log.cpp src/UPnP.cpp .tmp/uPnP1.0.0/ && $(COPY_FILE) --parents forms/mainwindow.ui .tmp/uPnP1.0.0/ && (cd `dirname .tmp/uPnP1.0.0` && $(TAR) uPnP1.0.0.tar uPnP1.0.0 && $(COMPRESS) uPnP1.0.0.tar) && $(MOVE) `dirname .tmp/uPnP1.0.0`/uPnP1.0.0.tar.gz . && $(DEL_FILE) -r .tmp/uPnP1.0.0


clean:compiler_clean 
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) *~ core *.core


####### Sub-libraries

distclean: clean
	-$(DEL_FILE) $(TARGET) 
	-$(DEL_FILE) Makefile


check: first

mocclean: compiler_moc_header_clean compiler_moc_source_clean

mocables: compiler_moc_header_make_all compiler_moc_source_make_all

compiler_moc_header_make_all: moc_mainwindow.cpp
compiler_moc_header_clean:
	-$(DEL_FILE) moc_mainwindow.cpp
moc_mainwindow.cpp: include/UPnP_CP.h \
		include/UPnP.h \
		include/DeviceList.h \
		include/Device.h \
		include/Service.h \
		include/Icon.h \
		include/Uri.h \
		include/Container.h \
		include/Item.h \
		include/Config.h \
		include/Thread.h \
		include/UPnP_MediaRenderer.h \
		include/Timer.h \
		include/UPnP_MediaServer.h \
		include/mainwindow.h
	/usr/bin/moc $(DEFINES) $(INCPATH) include/mainwindow.h -o moc_mainwindow.cpp

compiler_rcc_make_all: qrc_resorces.cpp
compiler_rcc_clean:
	-$(DEL_FILE) qrc_resorces.cpp
qrc_resorces.cpp: resorces.qrc \
		resources/home.svg \
		resources/stop.svg \
		resources/file-selected.svg \
		resources/file.svg \
		resources/music.svg \
		resources/folder.svg \
		resources/video.svg \
		resources/media/audio-volume.svg \
		resources/media/seek-forward.svg \
		resources/media/playback-start.svg \
		resources/media/skip-forward.svg \
		resources/media/vol+.svg \
		resources/media/seek-backward.svg \
		resources/media/stop.svg \
		resources/media/vol-.svg \
		resources/media/skip-backward.svg \
		resources/media/playback-pause.svg
	/usr/bin/rcc -name resorces resorces.qrc -o qrc_resorces.cpp

compiler_image_collection_make_all: qmake_image_collection.cpp
compiler_image_collection_clean:
	-$(DEL_FILE) qmake_image_collection.cpp
compiler_moc_source_make_all:
compiler_moc_source_clean:
compiler_uic_make_all: ui_mainwindow.h
compiler_uic_clean:
	-$(DEL_FILE) ui_mainwindow.h
ui_mainwindow.h: forms/mainwindow.ui
	/usr/bin/uic forms/mainwindow.ui -o ui_mainwindow.h

compiler_yacc_decl_make_all:
compiler_yacc_decl_clean:
compiler_yacc_impl_make_all:
compiler_yacc_impl_clean:
compiler_lex_make_all:
compiler_lex_clean:
compiler_clean: compiler_moc_header_clean compiler_rcc_clean compiler_uic_clean 

####### Compile

Config.o: src/Config.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o Config.o src/Config.cpp

Container.o: src/Container.cpp include/Container.h \
		include/Item.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o Container.o src/Container.cpp

Device.o: src/Device.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o Device.o src/Device.cpp

DeviceList.o: src/DeviceList.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o DeviceList.o src/DeviceList.cpp

Icon.o: src/Icon.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o Icon.o src/Icon.cpp

Item.o: src/Item.cpp include/Uri.h \
		include/Item.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o Item.o src/Item.cpp

main.o: src/main.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o main.o src/main.cpp

mainwindow.o: src/mainwindow.cpp ui_mainwindow.h \
		forms/player.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o mainwindow.o src/mainwindow.cpp

Service.o: src/Service.cpp include/Service.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o Service.o src/Service.cpp

TcpClient.o: src/TcpClient.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o TcpClient.o src/TcpClient.cpp

Thread.o: src/Thread.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o Thread.o src/Thread.cpp

UPnP_CP.o: src/UPnP_CP.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o UPnP_CP.o src/UPnP_CP.cpp

UPnP_MediaServer.o: src/UPnP_MediaServer.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o UPnP_MediaServer.o src/UPnP_MediaServer.cpp

UPnP_MediaRenderer.o: src/UPnP_MediaRenderer.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o UPnP_MediaRenderer.o src/UPnP_MediaRenderer.cpp

xmltools.o: src/xmltools.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o xmltools.o src/xmltools.cpp

HttpClient.o: src/HttpClient.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o HttpClient.o src/HttpClient.cpp

Log.o: src/Log.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o Log.o src/Log.cpp

UPnP.o: src/UPnP.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o UPnP.o src/UPnP.cpp

moc_mainwindow.o: moc_mainwindow.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_mainwindow.o moc_mainwindow.cpp

qrc_resorces.o: qrc_resorces.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o qrc_resorces.o qrc_resorces.cpp

####### Install

install:   FORCE

uninstall:   FORCE

FORCE:

