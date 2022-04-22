#include "matura.h"

#include <fstream>
#include <sstream>
#include <cmath>
#include <algorithm>

std::vector<std::string> read_file(const std::string &file_name) {
	std::ifstream ifs(file_name);

	if (ifs) {
		std::vector<std::string> input;

		for (std::string line; std::getline(ifs, line);) {
			input.push_back(line);
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

std::vector<int> factorize(int val) {
	std::vector<int> factors;

	for (int d = 2; d * d <= val; ++d) {
		while (val % d == 0) {
			factors.push_back(d);
			val /= d;
		}
	}

	if (val > 1) {
		factors.push_back(val);
	}

	return factors;
}

int bin_to_dec(const std::string &bin) {
	int exp = 0;
	int result = 0;

	for (auto it = bin.crbegin(); it != bin.crend(); ++it) {
		int digit = std::stoi(std::string(1, *it));
		result += digit * std::pow(2, exp);

		++exp;
	}

	return result;
}

void start(const std::vector<std::string> &args) {
	if (args.size() != 3) {
		throw std::runtime_error("wrong number of cmd line args");
	}

	solve_three(args);
}

void solve_one(const std::vector<std::string> &args) {
	auto input(read_file(args[1]));
	std::ostringstream ostr;

	for (const auto &x : input) {
		if (x.size() % 2 == 0) {
			auto sub1(x.substr(0, x.size() / 2));
			auto sub2(x.substr(x.size() / 2, x.size() / 2));

			if (sub1 == sub2) {
				ostr << x << '\n';
			}
		}
	}

	write_file(args[2], "63.1\n" + ostr.str() + "\n\n");
}

void solve_two(const std::vector<std::string> &args) {
	auto input(read_file(args[1]));

	unsigned satisfied_ctr = 0;

	for (const auto &x : input) {
		bool correct = true;

		for (decltype(x.size()) i = 0; i != x.size() - 1; ++i) {
			if (x[i] == '1' && x[i + 1] == '1') {
				correct = false;
				break;
			}
		}

		if (correct) {
			++satisfied_ctr;
		}
	}

	write_file(args[2], "63.2\nliczba ciagow spelniajacych wymagania: " + std::to_string(satisfied_ctr) + "\n\n");
}

void solve_three(const std::vector<std::string> &args) {
	auto input(read_file(args[1]));
	std::vector<int> half_prime;

	for (const auto &x : input) {
		int num = std::stoi(x, nullptr, 2);
		auto pfac(factorize(num));

		if (pfac.size() == 2) {
			half_prime.push_back(num);
		}
	}

	auto max_it = std::max_element(half_prime.cbegin(), half_prime.cend());
	auto min_it = std::min_element(half_prime.cbegin(), half_prime.cend());

	const std::string out = "63.3\nilosc ciagow ktore sa polpierwsze: " + std::to_string(half_prime.size())
		+ "\nnajwieksza polpierwsza: " + std::to_string(*max_it) + "\nnajmniejsza polpierwsza: " + std::to_string(*min_it) + "\n\n";

	write_file(args[2], out);
}