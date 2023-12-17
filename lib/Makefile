#############################################################################
# Makefile for building lib
#     Project: basealt
#############################################################################

####### Environment variables used for installation process
PRONAME = altclient
DESTDIR = 
INSTALLROOT = usr/local
INSTALLDIR = $(DESTDIR)/$(INSTALLROOT)
#######

####### Compiler, tools and options

DEFINES       = -DDEBUG -DALTCLIENT_LIBRARY

CC	=	gcc
CXX	=	gcc
CFLAGS	=	-O2 -fpic -g
CXXFLAGS=	-O2 -spic -g
INCPATH	=	-I./
LINK	=	gcc
LFLAGS	=	-O2 -shared
LIBS	=	-lpthread -lrt -lm -lcurl
LIBDIR	=	

AR	=	ar cqs

TAR	=	tar -cf
GZIP	=	gzip -9f

DIST 	=	lib

####### IVA files

BUILD_DIR	=	build
OBJECT_DIR	=	$(BUILD_DIR)/obj
TARGET_DIR	=	lib


HEADERS =	altclient_global.h \
		altclient.h
		
SOURCES =	altclient.c

OBJECTS =	$(OBJECT_DIR)/altclient.o 

TARGET	=	libaltclient.so

############################

####### Build rules

all: makedir $(TARGET)

makedir:
	@test -d  $(BUILD_DIR) || mkdir -p $(BUILD_DIR)
	@test -d  $(OBJECT_DIR) || mkdir -p $(OBJECT_DIR)
	@test -d  $(TARGET_DIR) || mkdir -p $(TARGET_DIR)
	
$(TARGET): $(OBJECTS) 
	$(LINK) $(LFLAGS) -o $(TARGET_DIR)/$(TARGET) $(OBJECTS) $(LIBS) $(OBJCOMP)

dist:
	$(TAR) $(DIST).tar $(SOURCES) $(HEADERS) $(INTERFACES)
	$(GZIP) $(DIST).tar

clean:
	-rm -Rf $(BUILD_DIR)
	-rm -Rf $(TARGET_DIR)
	-rm -f *~ core *.core

doc:
	doxygen Doxyfile


install_target: $(TARGET)
	install -d $(INSTALLDIR)/lib
	install -s -m 0755 $(TARGET_DIR)/$(TARGET) $(INSTALLDIR)/lib
	install -d $(INSTALLDIR)/include/$(PRONAME)
	install -m 0644 $(HEADERS) $(INSTALLDIR)/include/$(PRONAME)
	
install_config: 
	install -d /etc/ld.so.conf.d
	install -m 0644 /conf/local.conf /etc/ld.so.conf.d
	
install: install_target install_config
	-ldconfig

uninstall:
	rm -f $(INSTALLDIR)/lib/$(TARGET)
	rm -Rf $(INSTALLDIR)/include/$(PRONAME)
	
####### Compile
$(OBJECT_DIR)/altclient.o: altclient.c altclient.h altclient_global.h

####### Implicit rules
$(OBJECT_DIR)/%.o: %.cpp
	$(CXX) -c $(CXXFLAGS) $(INCPATH) $<
$(OBJECT_DIR)/%.o: %.cxx
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $@ $<
$(OBJECT_DIR)/%.o: %.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $@ $<
$(OBJECT_DIR)/%.o: %.C
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $@ $<
$(OBJECT_DIR)/%.o: %.c
	$(CC) -c $(CFLAGS) $(INCPATH) -o $@ $<
