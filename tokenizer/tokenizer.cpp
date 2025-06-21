#include "tokenizer.hpp"
#include <stdexcept>
#include <iostream>
#include <unistd.h>


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

std::future<std::vector<int>> Tokenizer::encode_future(const std::string& text) const{
  return std::async(std::launch::async, [this, text](){
    return this->encode(text);
  });
}

std::future<std::string> Tokenizer::decode_future(const std::vector<int>& ids) const{
  return std::async(std::launch::async, [this, ids](){
    return this->decode(ids);
  });
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

  //TODO: implement batch encoding and decoding
  // std::vector<std::future<std::vector<int>>> e_futures;
  // for(const auto& file_path : file_paths){
  //   e_futures.push_back(tokenizer.encode_future(file_path));
  // }

  // std::vector<std::future<std::string>> d_futures;
  // for(const auto& future : e_futures){
  //   d_futures.push_back(tokenizer.decode_future(future.get()));
  // }
} 