CXX=em++
CXXFLAGS= -std=c++20 -O2 -I./include  
LDFLAGS= --bind -s WASM=1 -s MODULARIZE=1 -s EXPORT_NAME="ATS"
SOURCES = $(wildcard *.cpp)
OBJECTS = $(SOURCES:.cpp=.o)
TARGET = ats.js

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f *.o *.wasm *.data *.js

.PHONY: all clean
