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

all:
	@echo "🔨 Building $(TARGET)..."             
	$(CXX) $(CXXFLAGS) -shared -o $(TARGET) $(SRC)   
	@echo "✅ Build complete: $(TARGET)"         

clean:
	rm -f $(TARGET)                            
	@echo "🧹 Cleaned: $(TARGET)"                
