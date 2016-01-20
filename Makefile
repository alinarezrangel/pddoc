CXX=g++
CFLAGS=-std=c++11
LIBS=

pddoc: Main.cpp
	$(CXX) $(CFLAGS) $(CLIBS) Main.cpp -o pddoc

