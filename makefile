# Project name
PROJECT_NAME = SPLand_simulation

# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -pedantic -Wno-ignored-qualifiers -g 

# Include directories
INCLUDES = -I./include

# Source and header directories
SRC_DIR = src
INCLUDE_DIR = include

# Object files directory
BUILD_DIR = build

# Source files
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)

# Header files
HEADERS = $(wildcard $(INCLUDE_DIR)/*.h)

# Object files
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SOURCES))

# Dependency files
DEPENDS = $(OBJECTS:.o=.d)

# Executable output
EXECUTABLE = bin/$(PROJECT_NAME)

.PHONY: all clean

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Include dependency files
-include $(DEPENDS)

# Generate dependency files
$(BUILD_DIR)/%.d: $(SRC_DIR)/%.cpp
	@set -e; rm -f $@; \
	$(CXX) $(CXXFLAGS) $(INCLUDES) -MM $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

clean:
	rm -f $(EXECUTABLE) $(OBJECTS) $(DEPENDS)