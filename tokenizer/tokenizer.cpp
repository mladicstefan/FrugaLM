#include "tokenizer.hpp"
#include <stdexcept>
#include <iostream>

Tokenizer::Tokenizer(const std::string& model_path){
  const auto status = processor_.Load(model_path);
  if(!status.ok()){
    throw std::runtime_error("Failed to load tokenizer model: " + model_path + 
                               " Error: " + status.ToString());
  }
}

std::vector<int> Tokenizer::encode(const std::string& text) const{
  std::vector<int> ids;
  processor_.Encode(text,&ids);
  return ids;
}

std::string Tokenizer::decode(const std::vector<int>& ids) const{
  std::string result;
  processor_.Decode(ids, &result);
  return result;
}

int main() {
  Tokenizer tokenizer("m.model");
  std::vector<int> ids = tokenizer.encode("Hello, world!");
  std::cout << "Encoded: ";
  for(int id : ids){
    std::cout << id << " ";
  }
  std::cout << std::endl;
  std::string text = tokenizer.decode(ids);
  std::cout << text << std::endl;
  return 0;
} 