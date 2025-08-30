CXX = g++

CXXFLAGS = -Wall -std=c++17 -g

SRC = globalign.cpp localign.cpp
EXE = globalign localign

all: $(EXE)

globalign: globalign.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

localign: localign.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

clean:
	rm -f $(EXE)