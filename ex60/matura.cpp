#include "matura.h"

#include <vector>
#include <string>
#include <fstream>
#include <stdexcept>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <set>

std::vector<int> read_file(const std::string &file_name) {
	std::ifstream ifs(file_name);

	if (ifs) {
		std::vector<int> ivec;

		for (int val = 0; ifs >> val;) {
			ivec.push_back(val);
		}

		return ivec;
	}
	else {
		throw std::runtime_error("cannot find file " + file_name);
	}
}

std::vector<int> get_divisors(int val) {
	std::vector<int> divisors{ 1, val };

	for (int d = 2; d <= val / 2; ++d) {
		if (val % d == 0) {
			divisors.push_back(d);
		}
	}

	std::sort(divisors.begin(), divisors.end());

	return divisors;
}

std::vector <std::pair<int, std::vector<int>>>
	build_div_vec(const std::vector<int> &vec) {

	std::vector<std::pair<int, std::vector<int>>> d_vec;

	for (const auto &x : vec) {
		d_vec.emplace_back(x, get_divisors(x));
	}

	return d_vec;
}

void solve_one(const std::vector<std::string> &args) {
	if (args.size() != 2) {
		throw std::runtime_error("wrong number of cmd args");
	}

	auto input = read_file(args[1]);
	std::vector<int> correct_nums;

	std::copy_if(input.cbegin(), input.cend(),
		std::back_inserter(correct_nums),
		[](int x) { return x < 1000; });

	std::cout << "count of numbers less than 1000: "
		<< correct_nums.size() << '\n';
	std::cout << "two last numbers less than 1000: "
		<< correct_nums[correct_nums.size() - 2] << " "
		<< correct_nums.back() << '\n';
}

void solve_one_2(const std::vector<std::string> &args) {
	if (args.size() != 2) {
		throw std::runtime_error("wrong number of cmd args");
	}
	
	auto input = read_file(args[1]);

	unsigned satisfied_ctr = 0;
	int one = 0, two = 0;
	bool is_first = true;

	for (const auto &x : input) {
		if (x < 1000) {
			++satisfied_ctr;
			if (is_first) {
				one = x;
				is_first = false;
			}
			else {
				two = x;
				is_first = true;
			}
		}
	}

	std::cout << "count of number less than 1000: " <<
		satisfied_ctr << '\n';
	std::cout << "last two numbers that are less than 1000: "
		<< one << " " << two << '\n';
}

void solve_two(const std::vector<std::string> &args) {
	if (args.size() != 2) {
		throw std::runtime_error("wrong number of cmd args");
	}

	auto input = read_file(args[1]);

	for (const auto &x : input) {
		auto divisors = get_divisors(x);

		if (divisors.size() == 18) {
			std::cout << x << ": ";
			for (const auto &z : divisors) {
				std::cout << z << " ";
			}
			std::cout << '\n';
		}
	}
}

void solve_three(const std::vector<std::string> &args) {
	if (args.size() != 2) {
		throw std::runtime_error("wrong number of cmd args");
	}

	auto input = read_file(args[1]);
	auto div_vec = build_div_vec(input);
	std::vector<int> satisfied_nums;

	for (std::size_t i = 0; i != div_vec.size(); ++i) {
		std::set<int> divisors_other;
		for (std::size_t j = 0; j != div_vec.size(); ++j) {
			if (j != i) {
				for (const auto &x : div_vec[j].second) {
					divisors_other.insert(x);
				}
			}
		}

		bool is_unique = true;

		for (const auto &x : div_vec[i].second) {
			if (divisors_other.contains(x) && x != 1) {
				is_unique = false;
				break;
			}
		}

		if (is_unique) {
			satisfied_nums.push_back(div_vec[i].first);
		}
	}

	std::sort(satisfied_nums.begin(), satisfied_nums.end());

	std::cout << satisfied_nums.back() << '\n';
}