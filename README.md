# basealt

This file describes the assembly and installation for the Basealt test software

STEP 1: Download
================

git clone git@github.com:kuzinAlexey/basealt.git

This will load a directory with the following subdirectories:

lib/    contains the shared library - altclient.so
src/    contains the source code of the program

STEP 2: BUILDING A PROJECT
==========================

To build a project, go to the project directory:

cd basealt

And execute make

List of dependencies:
- libcurl-dev (libcurl4-gnutls-dev)
- libjson-c-dev


STEP 3: INSTALL
===============

To install, run:

sudo make install

The library file will be installed at the path '/usr/local/lib'
The executable file will be installed at the path '/usr/local/bin'


STEP 4: PROGRAM EXECUTION
=========================

To run the program, run:

basealt_mgr [arg1] [arg2]

where arg1 and arg2 are repository names


