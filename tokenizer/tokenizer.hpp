#pragma once

#include <sentencepiece_processor.h>
#include <vector>
#include <string>
#include <future>

class Tokenizer {
private:
    sentencepiece::SentencePieceProcessor processor_;    
public:
    explicit Tokenizer(const std::string& model_path);
    std::vector<int> encode(const std::string& text) const;
    std::string decode(const std::vector<int>& ids) const;
    
    std::string readFile(const std::string& file_path)const;

    std::future<std::vector<int>> encode_future(const std::string& text) const;
    std::future<std::string> decode_future(const std::vector<int>& ids) const;

    ~Tokenizer() = default;
};

