/*      Description:

// This program stores all the information about products that belong to
// different stores from an input file.
// It also provides some useful functions such as listing the chains, the
// stores belongs to those chains, the products and their prices or whether
// they are out of stock and find the stores selling cheapest product.

//  Students:
// 1. Name: The Anh Nguyen
//     Student number: 292126
//     UserID:cxanng
//     E-mail: anh.t.nguyen@tuni.fi

// 2. Name: Phuong Nhi Thuy Tran
//     Student number: 291937
//     UsedID:mpthtr
//     E-mail: thuyphuongnhi.tran@tuni.fi
* */

// Set the price of the products which are not available in the store to -1
const double OUT_OF_STOCK = -1;


#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <iomanip>

// Initialized a data structure to store product's information
struct Product {
    std::string product_name;
    double price;
};


// This function checks if the item is already in the item list
// If not, it will add the item into the list. This is mainly used in
// "products" command.
void checked_list(std::vector<std::string>& list, std::string item) {
    std::vector<std::string>::iterator iter = std::find(list.begin(),
                                                        list.end(), item);
    if ( iter == list.end())
    {
        list.push_back(item);
    }
}


// This function updates item's information in the main data structure
void add_product(std::vector<Product>& list, Product new_item) {
    std::vector<Product>::iterator iter;
    bool is_in = false;   
    for (iter = list.begin(); iter != list.end(); iter++)
    {
        if (iter->product_name == new_item.product_name)
        {
            iter->price = new_item.price;
            is_in = true;
        }
    }

    if (! is_in)
    {
        list.push_back(new_item);
    }
}


// This function splits a string to parts with the separator given as a
// parameter and returns a vector include substrings
std::vector<std::string> split(const std::string& s, const char delimiter,
                               bool ignore_empty = false){
    std::vector<std::string> result;
    std::string tmp = s;

    while(tmp.find(delimiter) != std::string::npos)
    {
        std::string new_part = tmp.substr(0, tmp.find(delimiter));
        tmp = tmp.substr(tmp.find(delimiter)+1, tmp.size());
        if(not (ignore_empty and new_part.empty()))
        {
            result.push_back(new_part);
        }
    }

    if(not (ignore_empty and tmp.empty()))
    {
        result.push_back(tmp);
    }
    return result;
}


// This function compares name of two products, it is mainly used for
// ordering a vector contains products in "selection" command
bool compare_products(Product pro1, Product pro2) {
    return pro1.product_name < pro2.product_name;
}


// This function carries out the "selection" function
void select_store(std::map<std::string, std::map <std::string,
                  std::vector<Product>>> chain_system, std::string chain,
                  std::string location) {
    // First, check if the chain name is correct
    auto finding_iter_1 = chain_system.find(chain);
    if (finding_iter_1 == chain_system.end())
    {
        std::cout << "Error: unknown chain name" << std::endl;
    }
    else {
        // Then check if the store name is correct
        auto finding_iter_2 = chain_system[chain].find(location);
        if (finding_iter_2 == chain_system[chain].end())
        {
            std::cout << "Error: unknown store" << std::endl;
        }
        else {
            std::vector<Product>::iterator iter;

            // Sort the vector corresponding to the store by the name of the
            //products
            std::sort(chain_system[chain][location].begin(),
                      chain_system[chain][location].end(), compare_products);

            // Prints out the product's information
            for ( iter = chain_system[chain][location].begin();
                  iter != chain_system[chain][location].end(); iter++)
            {
                if (iter->price == OUT_OF_STOCK)
                {
                    std::cout << iter->product_name << " " << "out of stock"
                              << std::endl;
                }
                else {
                    // Here we used a method of rounding a decimal number
                    // called std::setprecision in library <iomanip>
                    std::cout << iter->product_name << " " << std::fixed
                              << std::setprecision(2) << iter->price << std::endl;
                }
            }
        }
    }
}


// This function carries out the "cheapest" function
void find_cheapest(std::map<std::string, std::map <std::string,
                   std::vector<Product>>> chain_system, std::string product) {
    // Initial a min value, a list contain the chain and store which sell
    // them and a variable to check if the products are available in the system
    double min_price = 0;
    std::vector<std::string> min_list;
    bool available = false;

    // Scan the data structure to find the cheapest value
    for ( auto chain_iter : chain_system)
    {
        std::string chain = chain_iter.first;
        for (auto location_iter : chain_system[chain])
        {
            std::string location = location_iter.first;
            for (auto element : chain_system[chain][location])
            {
                if (element.product_name == product && element.price > 0)
                {
                    // The min value will take the first price of the product
                    // found in the system
                    if (!available)
                    {
                        available = true;
                        min_price = element.price;
                        min_list.push_back(chain + " " + location);
                    }

                    // If a cheaper price is found, it will be set as the min
                    // vallue
                    else if (element.price < min_price)
                    {
                        min_price = element.price;
                        min_list = {chain + " " + location};
                    }

                    // Add location and chain information which sell the same
                    // price as the min value
                    else if (element.price == min_price) {
                        min_list.push_back(chain + " " + location);
                    }
                }
            }
        }
    }

    if (!available)
    {
        // If the product is out of stock everywhere, it will inform the user.
        std::cout << "The product is temporarily out of stock everywhere"
                  << std::endl;
    }
    else {
        // Here we use the same rounding method as the above function
        std::cout << std::fixed <<std::setprecision(2) << min_price << " euros"
                  << std::endl;
        for (auto place : min_list)
        {
            std::cout << place << std::endl;
        }
    }
}


// Main loop of the function, it receives commands and executes them
int main_loop(std::map <std::string, std::map <std::string,
              std::vector<Product>>> chain_system,
              std::vector<std::string> product_list) {
    while (true)
    {
        // Ask for command and split them into parts for processing
        std::string line;
        std::string command;
        std::cout << "> " ;
        getline(std::cin, line);
        std::vector<std::string> parts = split(line, ' ');
        command = parts[0];

        // Command "quit" terminates the program
        if (command == "quit")
        {
            return EXIT_SUCCESS;
        }

        // Command "chains" listes all store chains in alphabetical order
        else if (command == "chains")
        {
            // Check if the command is in correct syntax. If not,
            // it will print out the error message and ask the command again
            // This will be done for all below commands.
            if (parts.size() != 1)
            {
                std::cout << "Error: error in command chains" << std::endl;
                continue;
            }

            std::map<std::string, std::map <std::string,
                    std::vector<Product>>>::iterator iter;
            for (iter = chain_system.begin();  iter != chain_system.end();
                            iter ++)
            {
                std::cout << iter->first << std::endl;
            }
        }

        // Command "stores" prints out the location of stores of a chain
        // in alphabetical order.
        else if (command == "stores")
        {
            // Check if the command is in correct syntax. If not,
            // it will print out the error message and ask the command again
            if (parts.size() != 2)
            {
                std::cout << "Error: error in command stores" << std::endl;
                continue;
            }

            // Check if the chain name is typed correctly. If not, print out
            // error message.
            std::string chain = parts[1];
            auto iter_1 = chain_system.find(chain);
            if (iter_1 == chain_system.end())
            {
                std::cout << "Error: unknown chain name" << std::endl;
                continue;
            }

            // If everything is correct, print out the locations
            std::map<std::string, std::vector<Product>>::iterator iter;
            for ( iter = chain_system[chain].begin();
                  iter != chain_system[chain].end(); iter++)
            {
                std::cout << iter->first << std::endl;
            }
        }

        // Command "selection" prints out the information of all products
        // in selected store. The process is done above in "select_store"
        // function.
        else if (command == "selection")
        {
            // Check if the command is in correct syntax. If not,
            // it will print out the error message and ask the command again
            if (parts.size() != 3) {
                std::cout << "Error: error in command selection" << std::endl;
                continue;
            }

            std::string chain = parts[1];
            std::string location = parts[2];
            select_store(chain_system, chain, location);
        }

        // Command "cheapest" prints out the cheapest price can be found
        // of a product and also the stores where it is sold.
        else if (command == "cheapest")
        {
            if (parts.size() != 2)
            {
                std::cout << "Error: error in command cheapest" << std::endl;
                continue;
            }

            // After checking the syntax of the command, the program checks
            // if the product is in the product list or not. If not, it prints
            // the error message and ask for the command again. The process is
            // done in "find_cheapest" function above.
            std::string product = parts[1];
            auto finding_iter = std::find(product_list.begin(),
                                          product_list.end(), product);
            if (finding_iter == product_list.end())
            {
                std::cout << "The product is not part of product selection"
                          << std::endl;
                continue;
            }
            find_cheapest(chain_system, product);
        }

        // Command "products" prints out all the products 's names
        // in alphabetical order.
        else if (command == "products")
        {
            if (parts.size() != 1)
            {
                std::cout << "Error: error in command products" << std::endl;
                continue;
            }

            std::sort(product_list.begin(), product_list.end());
            for (auto product : product_list)
            {
                std::cout << product << std::endl;
            }
        }

        // And lastly, print out the error message if the command is unknown
        else {
            std::cout << "Error: unknown command: " << command <<std::endl;
        }
    }
}


int main()
{
    // The program asks for input file name, store the information and
    // also deal with reading errors
    std::cout << "Input file: ";
    std::string in_file = "";
    getline(std::cin, in_file);
    std::ifstream file_object(in_file);

    // Terminates the program if reading error is found
    if (! file_object)
    {
        std::cout << "Error: the input file cannot be opened" <<std::endl;
        return EXIT_FAILURE;
    }

    std::map <std::string, std::map <std::string,
            std::vector<Product>>> chain_system;
    std::vector <std::string> product_list;
    std::string line;

    while (getline(file_object, line))
    {
        std::vector <std::string> line_content = split(line, ';');
        // All of the categories must be filled
        if (line_content.size() !=4 || find(line_content.begin(),
                               line_content.end(), "") != line_content.end())
        {
            std::cout << "Error: the input file has an erroneous line"
                      <<std::endl;
            return EXIT_FAILURE;
        }

        // Store the information into the data structure
        Product item;
        if (line_content[3] == "out-of-stock")
        {
            item = {line_content[2], OUT_OF_STOCK};
        }
        else {
            item = {line_content[2], stod(line_content[3])};
        }
        add_product(chain_system[line_content[0]][line_content[1]],item);
        // Add the product name into the product list
        checked_list(product_list, line_content[2]);
    }
    return main_loop(chain_system, product_list);
}

