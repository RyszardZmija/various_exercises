#include "matura.h"

#include <stdexcept>
#include <cmath>
#include <algorithm>
#include <sstream>
#include <iostream>
#include <fstream>

int oct_to_dec(const std::string &octal) {
	int p = 0;
	int result = 0;

	for (auto it = octal.crbegin(); it != octal.crend(); ++it) {
		int digit = std::stoi(std::string(1, *it));
		result += digit * std::pow(8, p);

		++p;
	}

	return result;
}

std::string dec_to_oct(int decimal) {
	std::ostringstream result;

	while (decimal > 0) {
		int rem = decimal % 8;
		result << std::to_string(rem);
		decimal /= 8;
	}

	std::string result_str(result.str());

	std::reverse(result_str.begin(), result_str.end());

	return result_str;
}

std::vector<int> get_digits(int val) {
	std::vector<int> digits;

	while (val > 0) {
		digits.push_back(val % 10);
		val /= 10;
	}

	std::reverse(digits.begin(), digits.end());

	return digits;
}

std::vector<int> read_file(const std::string &file_name, bool oct = true) {
	std::ifstream ifs(file_name);

	if (ifs) {
		std::vector<int> input;

		if (oct) {
			for (std::string line; std::getline(ifs, line);) {
				input.push_back(oct_to_dec(line));
			}
		}
		else {
			for (int val = 0; ifs >> val;) {
				input.push_back(val);
			}
		}

		return input;
	}
	else {
		throw std::runtime_error("could not open " + file_name);
	}
}

void write_file(const std::string &file_name, const std::string &contents) {
	std::ofstream ofs(file_name, std::ofstream::app);

	if (ofs) {
		ofs << contents;
	}
	else {
		throw std::runtime_error("could not open " + file_name);
	}
}

void start(const std::vector<std::string> &args) {
	if (args.size() != 3) {
		throw std::runtime_error("wrong number of cmd line args");
	}

	solve_four(args);
}

void solve_one(const std::vector<std::string> &args) {
	auto input(read_file(args[1]));

	auto max_it = std::max_element(input.cbegin(), input.cend());
	auto min_it = std::min_element(input.cbegin(), input.cend());

	const std::string out = "62.1\nmax: " + dec_to_oct(*max_it) + "\nmin: " + dec_to_oct(*min_it) + "\n\n";

	write_file(args[2], out);
}

void solve_two(const std::vector<std::string> &args) {
	auto input(read_file(args[1], false));

	int first_elem = input.front(), elem = input.front(), size = 1;
	int max_first_elem = 0, max_size = 0;

	for (int i = 1; i != input.size(); ++i) {
		if (input[i] >= elem) {
			elem = input[i];
			++size;
		}
		else {
			if (size > max_size) {
				max_size = size;
				max_first_elem = first_elem;
			}

			first_elem = input[i];
			elem = input[i];
			size = 1;
		}
	}

	if (size > max_size) {
		max_size = size;
		max_first_elem = first_elem;
	}

	write_file(args[2], "62.2\npierwszy element: " +
		std::to_string(max_first_elem) + "\tdlugosc: " + std::to_string(max_size) + "\n\n");
}

void solve_three(const std::vector<std::string> &args) {
	auto input1(read_file(args[1]));
	auto input2(read_file(args[2], false));

	unsigned same_val_ctr = 0, greater_val_ctr = 0;

	// the vectors will have the same size so we don't have to worry
	// about stepping out of bounds and undefined behaviour
	for (int i = 0; i != input1.size(); ++i) {
		if (input1[i] == input2[i]) {
			++same_val_ctr;
		}
		else if (input1[i] > input2[i]) {
			++greater_val_ctr;
		}
	}

	const std::string out = "62.3\nliczby maja ta sama wartosc: " + std::to_string(same_val_ctr)
		+ "\nliczby z liczby1 maja wieksza wartosc: " + std::to_string(greater_val_ctr) + "\n\n";

	write_file(args[3], out);
}

void solve_four(const std::vector<std::string> &args) {
	auto input(read_file(args[1], false));
	std::vector<std::string> octal_rep;
	constexpr int num = 6;

	for (const auto &x : input) {
		octal_rep.push_back(dec_to_oct(x));
	}

	unsigned dec_six_ctr = 0, oct_six_ctr = 0;

	for (const auto &x : input) {
		auto digits(get_digits(x));

		dec_six_ctr += std::count_if(digits.cbegin(), digits.cend(), [num](int val) { return val == num; });
	}

	for (const auto &x : octal_rep) {
		for (const auto &c : x) {
			if (c == '6') {
				++oct_six_ctr;
			}
		}
	}

	write_file(args[2], "62.4\ndziesietny licznik: " + std::to_string(dec_six_ctr) + "\nosemkowy licznik: " +
		std::to_string(oct_six_ctr) + "\n\n");
}