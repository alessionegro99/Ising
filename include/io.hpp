#pragma once

#include <string>

void fatal_error(const std::string &message, const std::string &function_name);
bool is_file_empty(const std::string &file_name);