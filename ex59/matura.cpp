#include "matura.h"

#include <fstream>
#include <iostream>
#include <stdexcept>
#include <set>
#include <string>
#include <algorithm>
#include <map>

template <typename T>
inline void swap(T &lhs, T &rhs) {
	T temp = lhs;
	lhs = rhs;
	rhs = temp;
}

std::vector<long long> read_file(const std::string &file_name) {
	std::ifstream ifs(file_name);

	if (ifs) {
		std::vector<long long> input_data;

		for (long long val = 0; ifs >> val;) {
			input_data.push_back(val);
		}

		return input_data;
	}
	else {
		throw std::runtime_error("could not open file " + file_name);
	}
}

std::vector<long long> factorize(long long n) {
	std::vector<long long> factors;

	for (long long i = 2; i * i <= n; ++i) {
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

long long reverse(long long val) {
	std::string str(std::to_string(val));

	// we could call std::reverse but for exercise let's
	// type it by hand
	for (std::string::size_type i = 0; i != str.size() / 2; ++i) {
		swap(str[i], str[str.size() - 1 - i]);
	}

	return std::stoll(str);
}

bool is_palindrome(const std::string &str) {
	for (std::string::size_type i = 0; i != str.size() / 2; ++i) {
		if (str[i] != str[str.size() - 1 - i]) {
			return false;
		}
	}

	return true;
}

std::vector<int> get_digits(long long n) {
	std::vector<int> digits;

	while (n) {
		digits.push_back(n % 10);
		n /= 10;
	}

	std::reverse(digits.begin(), digits.end());

	return digits;
}

long long product(long long val) {
	long long prod = 1;
	for (const auto &x : get_digits(val)) {
		prod *= x;
	}

	return prod;
}

long long power(long long val) {
	long long p = 1;
	long long prod = product(val);

	while (get_digits(prod).size() != 1) {
		prod = product(prod);
		++p;
	}

	return p;
}

void solve_one(const std::vector<std::string> &args) {
	if (args.size() != 2) {
		throw std::runtime_error("wrong number of cmd args");
	}

	auto numbers = read_file(args[1]);

	unsigned satisfied_ctr = 0;

	for (const auto &x : numbers) {
		auto factors = factorize(x);
		std::set<long long> unique_factors(factors.cbegin(), factors.cend());

		if (unique_factors.size() == 3) {
			bool satisfies = true;

			for (const auto &x : unique_factors) {
				if (x % 2 == 0) {
					satisfies = false;
				}
			}

			if (satisfies) {
				++satisfied_ctr;
			}
		}
	}

	std::cout << "count of numbers satisfying the condition: " <<
		satisfied_ctr << '\n';
}

void solve_two(const std::vector<std::string> &args) {
	if (args.size() != 2) {
		throw std::runtime_error("wrong number of cmd args");
	}

	auto numbers = read_file(args[1]);
	unsigned satisfied_ctr = 0;

	for (const auto &x : numbers) {
		auto sum = x + reverse(x);
		if (is_palindrome(std::to_string(sum))) {
			++satisfied_ctr;
		}
	}

	std::cout << "number of special sums that are palindromes: "
		<< satisfied_ctr << '\n';
}

void solve_three(const std::vector<std::string> &args) {
	if (args.size() != 2) {
		throw std::runtime_error("wrong number of cmd args");
	}

	auto numbers = read_file(args[1]);
	long long max_number_power_one = 0;
	long long min_number_power_one = 0;
	std::map<unsigned, unsigned> power_count;
	bool first = true;

	for (const auto &x : numbers) {
		auto pow = power(x);

		if (pow <= 8) {
			++power_count[pow];
		}

		if (pow == 1) {
			if (first) {
				min_number_power_one = x;
				max_number_power_one = x;
				first = false;
			}
			else {
				if (x < min_number_power_one) {
					min_number_power_one = x;
				}
				if (x > max_number_power_one) {
					max_number_power_one = x;
				}
			}
		}
	}

	for (const auto &x : power_count) {
		std::cout << "count of numbers with power "
			<< x.first << ": " << x.second << '\n';
	}

	std::cout << "\n\n";

	std::cout << "greatest number with power 1: "
		<< max_number_power_one << '\n';
	std::cout << "smallest number with power 1: "
		<< min_number_power_one << '\n';
}