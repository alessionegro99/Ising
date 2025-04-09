#include "../include/io.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <stdexcept>

void fatal_error(const std::string &message, const std::string &function_name)
{
    std::cerr << "Fatal error in function \"" << function_name << "\": " << message << std::endl;
    std::exit(1);
}

bool is_file_empty(const std::string &file_name)
{
    std::ifstream file(file_name, std::ios::ate);
    if (!file)
    {
        std::cerr << "Error: could not open the file \"" << file_name << "\"." << std::endl;
        fatal_error("something went wrong", __func__);
    }

    return file.tellg() == 0;
}