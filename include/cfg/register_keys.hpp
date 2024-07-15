/* Some stuff for registering keys. This will check if q is in there,
 * If it is, then it will not register that one, and stop registering them */
#pragma once

#include <Windows.h>
#include <iostream>
#include <vector>

// Library of keys
extern char keys_code[];
extern int ids[];

// Returns true if succeeded.
bool registerAllKeys(std::vector<unsigned int> k);

void deregister_keys();