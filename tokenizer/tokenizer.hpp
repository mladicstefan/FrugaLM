#pragma once

#include <sentencepiece_processor.h>
#include <vector>
#include <string>
#include <mutex>

class Tokenizer {
private:
    sentencepiece::SentencePieceProcessor processor_;
public:
    explicit Tokenizer(const std::string& model_path);
    std::vector<int> encode(const std::string& text) const;
    std::string decode(const std::vector<int>& ids) const;
    ~Tokenizer() = default;
};