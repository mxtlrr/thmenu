#include "cfg/readcfg.hpp"

int hex2int(const std::string& hexString) {
  return std::stoi(hexString, nullptr, 16);
}

std::vector<unsigned int> retrieve_keys(std::string fileName){
  std::ifstream ifs(fileName);
  std::string content((std::istreambuf_iterator<char>(ifs)),(std::istreambuf_iterator<char>()));
  
  std::vector<unsigned int> keys;

  std::stringstream ss(content); 
  std::string token;
  while (getline(ss, token, ',')) {
    // Convert token to hex and then push to vector
    int hex = hex2int(token);
    keys.push_back(hex);
  }

  return keys;
}