#ifndef CHECKFILE_HH
#define CHECKFILE_HH
#include <string>
#include <iostream>

const std::string F_N_FOUND = "File not found",
                  F_FOUND   = "File found",
                  W_N_FOUND = "Word not found",
                  W_FOUND   = "Word found",
                  EMPTY     = "";

std::string findword(std::string filename, std::string keyword, bool sign);

#endif // CHECKFILE_HH
