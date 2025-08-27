CXX = g++

CXXFLAGS = -Wall -std=c++17 -g

SRC = globalign.cpp
EXE = globalign

all: $(EXE)

globalign: globalign.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

clean:
	rm -f $(EXE)