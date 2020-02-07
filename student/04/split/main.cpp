#include <iostream>
#include <string>
#include <vector>


// TODO: Implement split function here
// Do not change main function
std::vector <std::string> split(std::string line, char separator, bool sign = false)
{
    std::string::size_type EndIndex, StartIndex, line_size;
    line_size = line.size();
    StartIndex = 0;
    EndIndex = line.find(separator, StartIndex);
    std::vector <std::string> line_splitted;

    while (EndIndex < line_size) {
        std::string part = line.substr(StartIndex, EndIndex - StartIndex);
        if (part != "" && sign){
            line_splitted.push_back(part);
        } else if (not sign) {
            line_splitted.push_back(part);
        }
        StartIndex = EndIndex + 1;
        EndIndex = line.find(separator, StartIndex);
    }

    if (StartIndex < line_size){
        std::string part = line.substr(StartIndex);
        if (part != "" && sign){
            line_splitted.push_back(part);
        } else if (not sign) {
            line_splitted.push_back(part);
        }
    }

    if (line.at(line_size -1) == separator) {
        line_splitted.push_back("");
    }
    return line_splitted;
}

int main()
{
    std::string line = "";
    std::cout << "Enter a string: ";
    getline(std::cin, line);
    std::cout << "Enter the separator character: ";
    char separator = getchar();

    std::vector< std::string > parts  = split(line, separator);
    std::cout << "Splitted string including empty parts: " << std::endl;
    for( auto part : parts ) {
        std::cout << part << std::endl;
    }

    std::vector< std::string > parts_no_empty  = split(line, separator, true);
    std::cout << "Splitted string ignoring empty parts: " << std::endl;
    for( auto part : parts_no_empty ) {
        std::cout << part << std::endl;
    }
}
