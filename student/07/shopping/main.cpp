#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <iomanip>

struct Product {
    std::string product_name;
    double price;
};

void same_product(std::vector<Product>& list, Product new_item) {
    bool check = false;
    for (auto item : list) {
        if(item.product_name == new_item.product_name) {
            check = true;
            item.price = new_item.price;
        }
    }
    if (! check) {
        list.push_back(new_item);
    }
}

std::vector<std::string> split(const std::string& s, const char delimiter, bool ignore_empty = false){
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

bool check_list (std::vector<std::string> &vec, std::string name){
    std::vector<std::string>::iterator iter = std::find(vec.begin(), vec.end(), name);
    if (iter == vec.end())
        return true;
    return false;
}

int main()
{
    // Ask for input file name and store the information, also deal with reading errors
    std::cout << "Input file: ";
    std::string in_file = "";
    getline(std::cin, in_file);
    std::ifstream file_object(in_file);
    if (! file_object) {
        std::cout << "Error: the input file cannot be opened" <<std::endl;
        return EXIT_FAILURE;
    }
    std::map <std::string, std::vector<std::string>> chain_list;
    std::map <std::pair<std::string, std::string>, std::vector<Product>> store_product;
    std::vector <std::string> product_list;
    std::string line;

    while (getline(file_object, line)) {
        if (split(line, ';').size() !=4 ) {
            std::cout << "Error: the input file has an erroneous line" <<std::endl;
            return EXIT_FAILURE;
        }

        std::vector <std::string> line_content = split(line, ';');
        Product item;

        if (check_list(chain_list[line_content[0]], line_content[1])){
            chain_list[line_content[0]].push_back(line_content[1]);
        }

        if (check_list(product_list, line_content[2])){
            product_list.push_back(line_content[2]);
        }

        if (line_content[3] == "out-of-stock") {
            item = {line_content[2], -1};
        }
        else {
            item = {line_content[2], stod(line_content[3])};
        }

        std::pair<std::string, std::string> pair_chain_store = make_pair(line_content[0], line_content[1]);
        same_product(store_product[pair_chain_store],item);

    }

    file_object.close();

    while (true) {
        std::string command;
        std::cout << "> " ;
        getline(std::cin, line);
        std::vector<std::string> part = split(line, ' ');
        command = part[0];

        if (command == "quit") {
            return EXIT_FAILURE;
        }

        else if (command == "chains"){
            for (auto chain : chain_list){
                std::cout << chain.first << std::endl;
            }
        }

        else if (command == "stores") {
            if (part.size() != 2) {
                std::cout << "Error: error in command stores" << std::endl;
            }

            else {
                //  stores function
                std::sort(chain_list[part[1]].begin(), chain_list[part[1]].end());
                for (auto store : chain_list[part[1]]) {
                    std::cout << store << std::endl;
                }
            }
        }

        else if (command == "selection") {
            if (part.size() != 3) {
                std::cout << "Error: error in command selection" << std::endl;
            }

            else if (chain_list.find(part[1]) == chain_list.end()){
                std::cout << "Error: unknown chain name" << std::endl;
            }

            else if (check_list(chain_list[part[1]], part[2])){
                std::cout << "Error: unknown store" << std::endl;
            }

            else{
                for (auto item : store_product[make_pair(part[1], part[2])]) {
                    std::cout << item.product_name << " "
                               << item.price << std::endl;
                }
            }
        }

        else if (command == "cheapest") {
            if (part.size() != 2) {
                std::cout << "Error: error in command cheapest" << std::endl;
            }

            else if (check_list(product_list, part[1])) {
                std::cout << "The product is not part of product selection" << std::endl;
            } else {
                std::vector<std::string> min_list;
                double min_value = 0;
                std::map<std::pair<std::string, std::string>, std::vector<Product>>::iterator iter;
                for(iter = store_product.begin(); iter != store_product.end(); iter ++){
                    for (auto item : iter->second){
                        if(item.product_name == part[1]){
                            std::string location_name = iter->first.first + " " + iter->first.second;
                            if(min_list.empty() && item.price >= 0){
                                min_list.push_back(location_name);
                                min_value = item.price;
                            } else if (item.price == min_value) {
                                min_list.push_back(location_name);
                            } else if (item.price < min_value && item.price >= 0){
                                min_list.clear();
                                min_list.push_back(location_name);
                                min_value = item.price;
                            }
                        }
                    }
                }
                if (min_list.empty()){
                    std::cout << "The product is temporarily out of stock everywhere" << std::endl;
                } else {
                    std::cout <<std::fixed << std::setprecision(2) << min_value << " euros" << std::endl;
                    std::sort(min_list.begin(), min_list.end());
                    for (auto location : min_list){
                        std::cout << location << std::endl;
                    }
                }
            }
        }

        else if (command == "products") {
            if (part.size() != 1) {
                std::cout << "Error: error in command products" << std::endl;
            }
            else {
                // products function
                std::sort(product_list.begin(), product_list.end());
                for (auto product : product_list){
                    std::cout << product << std::endl;
                }
            }
        }

        else {
            std::cout << "Error: unknown command: " << command <<std::endl;
            continue;
        }
    }
}
