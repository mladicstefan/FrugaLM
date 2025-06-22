#include "tokenizer.hpp"
#include <stdexcept>
#include <iostream>
#include <fstream>
#include <ios>
#include <future>
#include <chrono>

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

std::string Tokenizer::readFile(const std::string& file_path) const{
  std::ifstream file(file_path, std::ios::binary);
  if (!file.is_open()){
    throw std::runtime_error("Cannot open file" + file_path);
  }
  
  file.seekg(0, std::ios::end);
  std::streamsize size = file.tellg();
  file.seekg(0, std::ios::beg);

  std::string buffer(size, '\0');
  file.read(&buffer[0], size);
  return buffer;
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
  auto start = std::chrono::high_resolution_clock::now();
  std::string text = tokenizer.readFile("../data/txt1.txt");
  std::vector<int> ids = tokenizer.encode(text);
  std::cout << "Encoded: ";
  int count = 0;
  for(int id : ids){
    //std::cout << id << " ";
    ++count;
  }
  std::cout << std::endl;

  auto end = std::chrono::high_resolution_clock::now();
  auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
  std::cout << "Encoded: " << count << " tokens" << std::endl;
  std::cout << elapsed << " ms" << std::endl;
  return 0;

} 
