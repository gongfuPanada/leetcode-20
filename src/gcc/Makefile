CC			= gcc
CXX     	= g++
CFLAGS		= -g -pedantic -Wall -Wunused -std=gnu99
CXXFLAGS 	= -g -Wall -Werror -fdelete-null-pointer-checks -std=c++14
CPATH		=
CXXPATH		=
LIBPATH		=
LIBS		=

all: switch sonald-switch uninit-struct testcase

switch:
	$(CC) -o switch.o -c $(CFLAGS) $(CPATH) switch.c
	$(CC) -o switch switch.o $(LIBPATH) $(LIBS)

sonald-switch:                                                                            
	$(CC) -o sonald-switch.o -c $(CFLAGS) $(CPATH) sonald-switch.c
	$(CC) -o sonald-switch sonald-switch.o $(LIBPATH) $(LIBS)

uninit-struct:
	$(CXX) -o uninit-struct.o -c $(CXXFLAGS) $(CXXPATH) uninit-struct.cpp
	$(CXX) -o uninit-struct uninit-struct.o $(LIBPATH) $(LIBS)

testcase:
	$(CXX) -o testcase.o -c $(CXXFLAGS) $(CXXPATH) testcase.cpp
	$(CXX) -o testcase testcase.o $(LIBPATH) $(LIBS)

clean: 
	rm -rf *.o switch sonald-switch uninit-struct testcase
