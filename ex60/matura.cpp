#include "matura.h"

#include <fstream>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <utility>

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
		throw std::runtime_error("could not open the file " + file_name);
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
		throw std::runtime_error("wrong number of cmd args");
	}

	solve_three(args);
}

// 2
std::vector<int> get_divisors(int val) {
	std::vector<int> divs;

	for (int i = 1; i <= val; ++i) {
		if (val % i == 0) {
			divs.push_back(i);
		}
	}

	return divs;
}

// 3
bool relat_prime_test(const std::vector<int> &fn, const std::vector<int> &sn) {

	for (const auto &x : fn) {
		if (std::find(sn.cbegin(), sn.cend(), x) != sn.cend()) {
			return false;
		}
	}

	return true;
}

void solve_one(const std::vector<std::string> &args) {
	auto nums(read_file(args[1]));

	auto cnt = std::count_if(nums.cbegin(), nums.cend(),
		[](int val) -> bool { return val < 1000; });

	std::vector<int> sifted;
	
	std::copy_if(nums.cbegin(), nums.cend(), std::back_inserter(sifted),
		[](int val) -> bool { return val < 1000; });

	write_file(args[2], "60.1\nMniejszych od 1000 jest " + std::to_string(cnt) + "\n"
	"ostatnie dwa: " + std::to_string(sifted.back()) + " " +
		std::to_string(sifted[sifted.size() - 2]) + "\n\n");
}

void solve_two(const std::vector<std::string> &args) {
	auto nums(read_file(args[1]));
	std::ostringstream ostr;

	for (const auto &x : nums) {
		auto divs(get_divisors(x));

		if (divs.size() == 18) {
			std::sort(divs.begin(), divs.end());

			ostr << x << ": ";

			for (const auto &d : divs) {
				ostr << d << " ";
			}

			ostr << '\n';
		}
	}

	write_file(args[2], "60.2\n" + ostr.str() + "\n\n");
}

void solve_three(const std::vector<std::string> &args) {
	auto nums(read_file(args[1]));
	std::vector<std::pair<int, std::vector<int>>> nums_div;
	std::vector<int> relat_prime;

	for (const auto &x : nums) {
		auto divs(get_divisors(x));
		divs.erase(divs.begin());

		nums_div.emplace_back(x, divs);
	}

	for (int i = 0; i != nums_div.size(); ++i) {
		bool insert = true;

		for (int j = 0; j < i; ++j) {
			if (!relat_prime_test(nums_div[i].second, nums_div[j].second)) {
				insert = false;
				break;
			}
		}

		if (insert) {
			for (int j = i + 1; j != nums_div.size(); ++j) {
				if (!relat_prime_test(nums_div[i].second, nums_div[j].second)) {
					insert = false;
					break;
				}
			}
		}

		if (insert) {
			relat_prime.push_back(nums_div[i].first);
		}
	}

	auto largest_element =
		std::max_element(relat_prime.cbegin(), relat_prime.cend());

	write_file(args[2], "60.3\n" + std::to_string(*largest_element) + "\n\n");
}