TARGET = test_runner # can run directly as ./test_runner

CXX = g++
CXXFLAGS = -std=c++17 -Wall -g -Isrc \
  -I../src \
  -I"$(JAVA_HOME)/include" \
  -I"$(JAVA_HOME)/include/darwin"

TEST_SRC = $(wildcard *.cpp)

ENGINE_SRC = $(filter-out ../src/main.cpp, $(wildcard ../src/*.cpp) ../src/pieces/*.cpp)

all: $(TARGET)

$(TARGET): $(TEST_SRC) $(ENGINE_SRC)
	$(CXX) $(CXXFLAGS) $^ -o $@

clean:
	rm -f $(TARGET)