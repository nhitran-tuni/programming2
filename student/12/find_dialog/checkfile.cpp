#include "checkfile.hh"
#include <fstream>
#include <algorithm>
#include <cctype>

std::string findword(std::string filename, std::string keyword, bool sign)
{
    std::ifstream readfile(filename);

    if ( !readfile ){
        return F_N_FOUND;
    }

    if ( !sign ){
        std::transform(keyword.begin(), keyword.end(), keyword.begin(),
                       [](unsigned char c) -> std::size_t { return std::toupper(c); });
    }

    std::string line = "";
    while ( getline(readfile,line) ){
        if ( !sign ){
            std::transform(line.begin(), line.end(), line.begin(),
                           [](unsigned char c) -> std::size_t { return std::toupper(c); });
        }

        std::size_t index = line.find(keyword);
        if ( index != std::string::npos ){
            return W_FOUND;
        }
    }

    return W_N_FOUND;
}

