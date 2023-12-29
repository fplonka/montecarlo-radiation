# Define the C++ compiler to use
CXX = g++

# Define any compile-time flags
CXXFLAGS = $(shell geant4-config --cflags) -Iinclude -fsanitize=address

# Define any directories containing header files other than /usr/include
#
INCLUDES =

# Define library paths in addition to /usr/lib
LFLAGS = $(shell geant4-config --libs) -Wl,-rpath,/Users/filip/Code/cpp/physproject/install/lib

# Define any libraries to link into executable:
LIBS =

# Define the C++ source files
SOURCES = $(wildcard src/*.cpp)

# Define the C++ object files
#
# This uses Suffix Replacement within a macro:
#   $(name:string1=string2)
# For each word in 'name' replace 'string1' with 'string2'
#
OBJECTS = $(SOURCES:src/%.cpp=build/%.o)

# Define the executable file
MAIN = bin/mygeant4app

#
# The following part of the makefile is generic; it can be used to
# build any executable just by changing the definitions above and by
# deleting dependencies appended to the file from 'make depend'
#

.PHONY: depend clean

all:    $(MAIN)
	@echo  Simple GEANT4 app has been compiled

$(MAIN): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $(MAIN) $(OBJECTS) $(LFLAGS) $(LIBS)

build/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $<  -o $@

clean:
	$(RM) build/*.o *~ $(MAIN)

depend: $(SOURCES)
	makedepend $(INCLUDES) $^


# DO NOT DELETE THIS LINE -- make depend needs it

