TARGET = chess # Can run directly as ./chess

CXX = g++
CXXFLAGS = -std=c++17 -Wall -g -Isrc

SRC = $(wildcard src/*.cpp) $(wildcard src/pieces/*.cpp)
SRC := $(filter-out src/BackendBridge.cpp src/main.cpp, $(SRC))

MAIN = src/main.cpp

OBJ = $(SRC:.cpp=.o)

all: $(TARGET)

$(TARGET): $(MAIN) $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(MAIN) $(SRC)

clean:
	rm -f $(TARGET) $(OBJ)