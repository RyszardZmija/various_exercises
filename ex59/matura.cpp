#include "matura.h"

#include <vector>
#include <string>
#include <set>

#include <stdexcept>

#include <fstream>
#include <sstream>

// general
std::vector<int> read_file(const std::string &file_name) {
	std::ifstream ifs(file_name);

	if (ifs) {
		std::vector<int> input;

		for (int val = 0; ifs >> val;) {
			input.push_back(val);
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
		throw std::runtime_error("could not open the given file " + file_name);
	}
}

void start(const std::vector<std::string> &args) {
	if (args.size() != 3) {
		throw std::runtime_error("wrong number of cmd line args");
	}

	solve_three(args);
}

// 1
std::vector<int> factorize(int n) {
	std::vector<int> factors;

	for (int i = 2; i * i <= n; ++i) {
		while (n % i == 0) {
			factors.push_back(i);
			n /= i;
		}
	}

	if (n > 1) {
		factors.push_back(n);
	}

	return factors;
}

// 2
bool is_palindrome(const std::string &str) {
	if (!str.empty()) {
		std::string reversed(str);
		std::reverse(reversed.begin(), reversed.end());

		return reversed == str;
	}

	return false;
}

int gen_num_backwards(int n) {
	std::string str(std::to_string(n));
	
	std::reverse(str.begin(), str.end());

	return std::stoi(str);
}

// 3
std::vector<int> get_digits(int n) {
	std::vector<int> digits;

	while (n > 0) {
		digits.push_back(n % 10);
		n /= 10;
	}

	std::reverse(digits.begin(), digits.end());

	return digits;
}

int digit_product(const std::vector<int> &digts) {
	int product = 1;

	for (const auto &x : digts) {
		product *= x;
	}

	return product;
}

int calc_power(int n) {
	int power = 1;

	std::vector<int> digits(get_digits(n));
	n = digit_product(digits);
	
	digits = get_digits(n);

	while (digits.size() > 1) {
		n = digit_product(digits);
		++power;
		digits = get_digits(n);
	}

	return power;
}

void solve_one(const std::vector<std::string> &args) {
	auto nums(read_file(args[1]));

	unsigned satisfied_ctr = 0;

	for (const auto &x : nums) {
		auto factors(factorize(x));

		std::set<int> unique_factors(factors.cbegin(), factors.cend());

		if (unique_factors.find(2) == unique_factors.end() &&
			unique_factors.size() == 3) {
			
			++satisfied_ctr;
		}
	}

	write_file(args[2], "59.1\n" + std::to_string(satisfied_ctr) + "\n\n");
}

void solve_two(const std::vector<std::string> &args) {
	auto nums(read_file(args[1]));

	unsigned satisfied_ctr = 0;

	for (const auto &x : nums) {
		int sum = x + gen_num_backwards(x);

		if (is_palindrome(std::to_string(sum))) {
			++satisfied_ctr;
		}
	}

	write_file(args[2], "59.2\n" + std::to_string(satisfied_ctr) + "\n\n");
}

void solve_three(const std::vector<std::string> &args) {
	auto nums(read_file(args[1]));

	std::vector<unsigned> power_ctr(8);
	int min_pow_one = 0, max_pow_one = 0;
	bool first = true;

	for (const auto &x : nums) {
		int pow = calc_power(x);

		if (pow < 9) {
			++power_ctr[pow - 1];

			if (pow == 1) {
				if (first) {
					min_pow_one = x;
					max_pow_one = x;
					first = false;
				}
				else {
					if (x < min_pow_one) {
						min_pow_one = x;
					}
					if (x > max_pow_one) {
						max_pow_one = x;
					}
				}
			}
		}
	}

	std::ostringstream ostr;

	for (decltype(power_ctr.size()) i = 0; i != power_ctr.size(); ++i) {
		ostr << "liczba liczb z moca " << i + 1 << ": " << power_ctr[i] << '\n';
	}

	const std::string output = "59.3\nmax z moca 1: " + std::to_string(max_pow_one) +
		"\nmin z moca 1: " + std::to_string(min_pow_one) + "\n\n" +
		ostr.str() + "\n\n";

	write_file(args[2], output);
}