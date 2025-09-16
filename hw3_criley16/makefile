CXX = g++

CXXFLAGS = -Wall -std=c++17 -g

SRC = casino_simulator.cpp forward.cpp
EXE = casino_simulator forward

all: $(EXE)

casino_simulator: casino_simulator.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

clean:
	rm -f $(EXE)