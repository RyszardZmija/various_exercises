#ifndef MATURA_H
#define MATURA_H

#include <string>
#include <sstream>
#include <fstream>
#include <utility>
#include <vector>
#include <iostream>

#include <stdexcept>
#include <algorithm>

using weather_rec = std::pair<unsigned, int>;

std::string dec_to_bin(long long val);

int convert_to_base(const std::string &num, int base);

std::vector<weather_rec> read_file(const std::string &file_name, int base);

void solve_one(const std::vector<std::string> &args);

void solve_two(const std::vector<std::string> &args);

void solve_three(const std::vector<std::string> &args);

void solve_four(const std::vector<std::string> &args);
#endif