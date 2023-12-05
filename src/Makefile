#############################################################################
# Makefile for building cli-utility
#     Project: basealt
#############################################################################

####### Environment variables used for installation process
DESTDIR = 
INSTALLROOT = usr/local
INSTALLDIR = $(DESTDIR)/$(INSTALLROOT)
#######

####### Compiler, tools and options

CC	=	g++
CXX	=	g++
CFLAGS	=	-O2 -static -g
CXXFLAGS=	-O2 -static -g
INCPATH	=	-I./ -I../lib
LINK	=	g++
LFLAGS	=	-O2
LIBS	=	-lm -lrt -lpthread \
			-ljson-c \
			-L../lib/lib -laltclient

TAR	=	tar -cf
GZIP	=	gzip -9f

DIST 	=	basealt_mgr

####### IVA files

HEADERS =	arch.h \
			repo.h
		
SOURCES =	arch.c \
			main.c \
			repo.c

BUILD_DIR	=	build
OBJECT_DIR	=	$(BUILD_DIR)/obj
TARGET_DIR	=	bin

OBJECTS =	$(OBJECT_DIR)/arch.o \
			$(OBJECT_DIR)/main.o \
			$(OBJECT_DIR)/repo.o

TARGET	=	basealt_mgr

############################

####### Build rules

all: makedir $(TARGET)

makedir:
	@test -d  $(BUILD_DIR) || mkdir -p $(BUILD_DIR)
	@test -d  $(OBJECT_DIR) || mkdir -p $(OBJECT_DIR)
	@test -d  $(TARGET_DIR) || mkdir -p $(TARGET_DIR)

$(TARGET): $(OBJECTS) 
	$(LINK) $(LFLAGS) -o $(TARGET_DIR)/$(TARGET) $(OBJECTS) $(LIBS)
	
dist:
	$(TAR) $(DIST).tar $(SOURCES) $(HEADERS) $(INTERFACES)
	$(GZIP) $(DIST).tar

clean:
	-rm -Rf $(BUILD_DIR)
	-rm -Rf $(TARGET_DIR)
	-rm -f *~ core *.core

doc:
	doxygen Doxyfile

install:
	install -d $(INSTALLDIR)/bin
	install -s -m 0755 $(TARGET_DIR)/$(TARGET) $(INSTALLDIR)/bin

uninstall:
	rm -f $(INSTALLDIR)/bin/$(TARGET)	
	
####### Compile
$(OBJECT_DIR)/main.o: main.c repo.h
$(OBJECT_DIR)/repo.o: repo.c repo.h arch.h
$(OBJECT_DIR)/arch.o: arch.c arch.h

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
