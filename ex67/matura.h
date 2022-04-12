#ifndef MATURA_H
#define MATURA_H

#include <vector>
#include <string>

void start(const std::vector<std::string> &args);

void solve_one(const std::vector<std::string> &args);
void solve_two(const std::vector<std::string> &args);
void solve_three(const std::vector<std::string> &args);
void solve_four(const std::vector<std::string> &args);

long long fib(long long n);
std::string convert_to_bin(long long n);
#endif