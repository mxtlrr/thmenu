#pragma once

#define QUIT     26
#define NOCLIP  100
#define XPOS_FR 200
#define NO_ROTA 300
#define INSTACM 400

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

// Converts a string, i.e. "0x49" to the integer repr, 0x49.
int hex2int(const std::string& hexString);

std::vector<unsigned int> retrieve_keys(std::string fileName);