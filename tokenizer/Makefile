# Makefile for SentencePiece Training
CXX = g++
CXXFLAGS = -std=c++17 -O2 -Wall -Wextra
INCLUDES = -I../dependencies/sentencepiece/src -I../dependencies/sentencepiece/third_party/protobuf-lite
LIBDIR = -L../dependencies/sentencepiece/build
LIBS = -lsentencepiece -lsentencepiece_train -pthread

# Target executable
TARGET = trainer.exe
SOURCE = train.cpp
TOKENIZER_SOURCE = tokenizer.cpp
TOKENIZER_TARGET = tokenizer.exe


# Default target
all: $(TARGET)

# Compile the training program
$(TARGET): $(SOURCE)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $(TARGET) $(SOURCE) $(LIBDIR) $(LIBS)

# Compile the tokenizer program
$(TOKENIZER_TARGET): $(TOKENIZER_SOURCE) tokenizer.hpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $(TOKENIZER_TARGET) $(TOKENIZER_SOURCE) $(LIBDIR) $(LIBS) 

# Run the training to generate model files
train: $(TARGET)
	./$(TARGET)
	@echo "Model files generated: m.model and m.vocab"

tokenizer: $(TOKENIZER_TARGET)
	./$(TOKENIZER_TARGET)
	@echo "Input Tokenized"

# Clean build artifacts
clean:
	rm -f $(TARGET) m.model m.vocab $(TOKENIZER_TARGET)

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
	@echo "  make clean    # Remove generated files"

.PHONY: all train-model clean info 
