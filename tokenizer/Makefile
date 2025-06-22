# Makefile for SentencePiece Training
CXX = g++
CXXFLAGS = -std=c++17 -O2 -Wall -Wextra
INCLUDES = -I$(CONDA_PREFIX)/include -I../extern/pybind11/include $(shell python3 -m pybind11 --includes)
LIBDIR = -L$(CONDA_PREFIX)/lib
LIBS = -lsentencepiece -lsentencepiece_train -pthread

# Python bindings flags (following pybind11 docs) - with static libstdc++ linking
PYBIND_CXXFLAGS = -O3 -Wall -shared -std=c++17 -fPIC -static-libgcc -static-libstdc++
PYBIND_LIBS = -lsentencepiece -lsentencepiece_train -pthread

# Target executable
TARGET = trainer.exe
SOURCE = train.cpp
TOKENIZER_SOURCE = tokenizer.cpp
TOKENIZER_TARGET = tokenizer.exe

# Python bindings
TOKENIZER_BINDINGS_SOURCE = py_bindings.cpp
TOKENIZER_BINDINGS_TARGET = tokenizer$(shell python3-config --extension-suffix)

# Default target
all: $(TARGET)

# Compile the training program
$(TARGET): $(SOURCE)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $(TARGET) $(SOURCE) $(LIBDIR) $(LIBS)

# Compile the tokenizer program
$(TOKENIZER_TARGET): $(TOKENIZER_SOURCE) tokenizer.hpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $(TOKENIZER_TARGET) $(TOKENIZER_SOURCE) $(LIBDIR) $(LIBS) 

# Compile Python bindings (following pybind11 manual build recommendations)
$(TOKENIZER_BINDINGS_TARGET): $(TOKENIZER_BINDINGS_SOURCE) tokenizer.hpp tokenizer.cpp
	$(CXX) $(PYBIND_CXXFLAGS) $(shell python3 -m pybind11 --includes) -I$(CONDA_PREFIX)/include -o $(TOKENIZER_BINDINGS_TARGET) $(TOKENIZER_BINDINGS_SOURCE) tokenizer.cpp $(LIBDIR) $(PYBIND_LIBS)

bindings: $(TOKENIZER_BINDINGS_TARGET)
	@echo "Python bindings created: $(TOKENIZER_BINDINGS_TARGET)"

# Run the training to generate model files
train: $(TARGET)
	./$(TARGET)
	@echo "Model files generated: m.model and m.vocab"

tokenizer: $(TOKENIZER_TARGET)
	./$(TOKENIZER_TARGET)
	@echo "Input Tokenized"

# Clean build artifacts
clean:
	rm -f $(TARGET) m.model m.vocab $(TOKENIZER_TARGET) $(TOKENIZER_BINDINGS_TARGET)

# Show what files will be generated
info:
	@echo "This will generate:"
	@echo "  - m.model (the SentencePiece model file)"
	@echo "  - m.vocab (the vocabulary file)"
	@echo ""
	@echo "Usage:"
	@echo "  make          # Compile the training program"
	@echo "  make train # Compile and run training"
	@echo "  make tokenizer # Compile and run tokenizer"
	@echo "  make bindings # Compile Python bindings"
	@echo "  make clean    # Remove generated files"

.PHONY: all train tokenizer bindings clean info
