#############################################################################
# Makefile for building lib
#     Project: basealt
#############################################################################

####### Environment variables used for installation process
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
TARGET_DIR	=	../build


HEADERS =	altclient_qzm_global.h \
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
	-rm -f $(TARGET_DIR)/$(TARGET)
	-rm -f *~ core *.core

doc:
	doxygen Doxyfile

#install: $(TARGET)
#	install -d $(INSTALLDIR)/bin
#	install -s -m 0755 $(TARGET) $(INSTALLDIR)/bin
#	install -d $(INSTALLDIR)/etc
#	install -m 0644 $(CONFIG) $(INSTALLDIR)/etc

install_targets: $(TARGET) $(CONFIG)
	install -d $(INSTALLDIR)/bin
	install -s -m 0755 $(TARGET_DIR)/$(TARGET) $(INSTALLDIR)/bin
	install -d $(INSTALLDIR)/etc
	install -m 0644 $(CONFIG) $(INSTALLDIR)/etc
	
install_configs:

#install_configs: $(CONFIGS) $(TARGET).md5sum
#	install -d $(INSTALLDIR)/etc
#	install -m 0644 $(CONFIGS) $(INSTALLDIR)/etc
#	for cfg in $(CONFIGS); do sed -i "/md5/c\md5 `cat $(TARGET).md5sum`" $(INSTALLDIR)/etc/$$cfg; done

install: install_targets install_configs
	install -m 0755 $(SCRIPTS) /etc/init.d

uninstall:
	rm -f $(INSTALLDIR)/bin/$(TARGET)
	rm -f $(INSTALLDIR)/etc/$(CONFIG)
	rm -f /etc/init.d/$(SCRIPTS)
	
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
