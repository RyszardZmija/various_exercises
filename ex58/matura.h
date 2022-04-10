#ifndef MATURA_H
#define MATURA_H

#include <vector>
#include <string>

#include <cmath>

using temp_rec = std::pair<int, int>;

void start(const std::vector<std::string> &vec);

void solve_one(const std::vector<std::string> &);
void solve_two(const std::vector<std::string> &);
void solve_three(const std::vector<std::string> &);
void solve_four(const std::vector<std::string> &);

std::string convert_to_bin(int);
std::vector<temp_rec> read_file(const std::string &file_name, int base);
temp_rec find_smallest_temp(const std::vector<temp_rec> &vec);

inline int calc_temp_jmp(int first_val, int first_index,
	int second_val, int second_index) {

	double square = std::pow(first_val - second_val, 2);
	double result = square / std::abs(first_index - second_index);

	return std::ceil(result);
}
#endif