#ifndef MATURA_H
#define MATURA_H

#include <string>
#include <vector>

std::vector<long long> factorize(long long val);

std::vector<long long> read_file(const std::string &file_name);

void solve_one(const std::vector<std::string> &args);

void solve_two(const std::vector<std::string> &args);

void solve_three(const std::vector<std::string> &args);
#endif