CXX			= g++
CXXFLAGS	= --std=c++17
SOURCES		= $(wildcard *.cpp)
ifeq ($(OS),Windows_NT)
EXE			= $(SOURCES:%.cpp=%.exe)
else
EXE			= $(SOURCES:%.cpp=%)
endif
OTHER		= kcore.txt clique.txt

.PHONY: all clean

all: $(EXE)

ifeq ($(OS),Windows_NT)
$(EXE): %.exe : %.cpp
	$(CXX) -Wall -Wextra $(CXXFLAGS) -o $@ $<
else
$(EXE): % : %.cpp
	$(CXX) -Wall -Wextra $(CXXFLAGS) -o $@ $<
endif

clean:
ifeq ($(OS),Windows_NT)
	del /f $(EXE) $(OTHER)
else
	rm -f $(EXE) $(OTHER)
endif
