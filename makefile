CXX = g++
INCLUDE_DIR = include
CXXFLAGS = -std=c++11 -I$(INCLUDE_DIR)
LDFLAGS =
EXECUTABLE = begcar
SOURCES_DIR = src
OBJECTS_DIR = bin
#gives all files in src ending with .cpp
SOURCES = $(shell ls $(SOURCES_DIR)/*.cpp)
#changes "src/" for "bin/" and ".cpp" for ".o"
OBJECTS = $(subst $(SOURCES_DIR)/,$(OBJECTS_DIR)/,$(SOURCES:.cpp=.o))
 
$(EXECUTABLE): $(OBJECTS)
	echo objects: $(OBJECTS)
	$(CXX) -o $@ $^ $(LDFLAGS)
 
$(OBJECTS_DIR)/%.o: $(SOURCES_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $^
 
#.PHONY means this recipe will never be a file, '-' at the beginning means it will execute no matter what
.PHONY : clean
clean:
	-rm -f begcar $(OBJECTS)