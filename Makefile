CXX = g++

CXXFLAGS = -std=c++17 -fPIC \
  -I"$(JAVA_HOME)/include" \
  -I"$(JAVA_HOME)/include/darwin" \
  -Icpp_backend/src

SRC = cpp_backend/src/BackendBridge.cpp \
      cpp_backend/src/board.cpp \
      cpp_backend/src/movegen.cpp \
      cpp_backend/src/search.cpp \
      cpp_backend/src/evaluate.cpp \
      $(wildcard cpp_backend/src/pieces/*.cpp)

TARGET = libChessEngine.dylib

JAVA_SRC = $(wildcard java_swing_frontend/src/ui/*.java java_swing_frontend/src/model/*.java java_swing_frontend/src/engine/*.java)
JAVA_BIN = java_swing_frontend/bin

.PHONY: all java test clean

all: $(TARGET) java test

$(TARGET):
	@echo "🔨 Building $(TARGET)..."
	$(CXX) $(CXXFLAGS) -shared -o $(TARGET) $(SRC)
	@echo "Build complete: $(TARGET)"

java:
	@echo "🔨 Compiling Java sources..."
	mkdir -p $(JAVA_BIN)
	javac -d $(JAVA_BIN) $(JAVA_SRC)
	@echo "Java build complete."

test:
	$(MAKE) -C cpp_backend/test

clean:
	rm -f $(TARGET)
	@echo "🧹 Cleaned: $(TARGET)"
	$(MAKE) -C cpp_backend/test clean
	rm -rf $(JAVA_BIN)/*
	@echo "🧹 Cleaned: Java bin folder"
