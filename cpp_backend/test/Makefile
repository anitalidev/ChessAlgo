TARGET = test_runner # ./test_runner

CXX = g++
CXXFLAGS = -std=c++17 -Wall -g -Isrc

TEST_SRC = $(wildcard *.cpp)

ENGINE_SRC = $(filter-out ../src/main.cpp, $(wildcard ../src/*.cpp) ../src/pieces/*.cpp)

all: $(TARGET)

$(TARGET): $(TEST_SRC) $(ENGINE_SRC)
	$(CXX) $(CXXFLAGS) $^ -o $@

clean:
	rm -f $(TARGET)