CXX = g++
CXXFLAGS = -g -Wall -std=c++11
OBJDIR = obj
CPP_FILES := $(wildcard src/*.cpp)
OBJ_FILES = $(addprefix obj/,$(notdir $(CPP_FILES:.cpp=.o)))

all: $(OBJDIR) checkers deleteDSYM

$(OBJDIR):
	mkdir $(OBJDIR)

checkers: Checkers.cpp $(OBJ_FILES)
	$(CXX) $(CXXFLAGS) Checkers.cpp $(OBJ_FILES) -o Checkers

obj/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<
	
deleteDSYM:
	rm -rf Checkers.dSYM

clean: deleteDSYM
	rm -rf $(OBJDIR)
	rm -f Checkers
