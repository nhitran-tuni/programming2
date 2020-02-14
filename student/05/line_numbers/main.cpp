#include <iostream>
#include <fstream>
#include <string>

int main()
{
    std::string input_filename, output_filename;
    std::cout << "Input file: ";
    getline(std::cin, input_filename);
    std::cout << "Output file: ";
    getline(std::cin, output_filename);

//    char separator = '.';
//    std::string output_filename = "";
//    std::string::size_type EndIndex;
//    EndIndex = input_filename.find(separator, 0);
//    output_filename = input_filename.substr(0, EndIndex) + ".output";
//    std::cout << "Output file: " << output_filename << std::endl;

    std::ifstream file_object(input_filename);
    if (not file_object)
    {
        std::cout << "Error! The file not_a_file.input cannot be opened." << std::endl;
        return EXIT_FAILURE;
    }
    else
    {
        unsigned int number = 1;
        std::string line;

        std::ofstream outfile(output_filename);
//        outfile.open(output_filename);

        while ( getline(file_object, line) )
        {
            std::string num_str = std::to_string(number);
            std::string new_line = num_str + " " + line;
            outfile << new_line << std::endl;
            number += 1;
        }
        file_object.close();
        outfile.close();
    }

    return 0;
}
