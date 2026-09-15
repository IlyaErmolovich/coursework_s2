#pragma once
#include <fstream>
#include "stack.h"

bool file_exist(const std::string& file_path);

std::ofstream new_db(const std::string& file_path);
bool remove_db(const std::string& file_path);
void clear(stack& st);
bool save_db(const std::string& file_path, stack& st);
bool load_db(const std::string& file_path, stack& st);