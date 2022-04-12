#include "matura.h"

#include <stdexcept>
#include <fstream>
#include <sstream>

#include <algorithm>

// Quite unusually this exercise doesn't require from us to read some input
// from a file and perform numerous operations that in the end yield a
// satisfying result. Here we are tested if we can implement the fibonacci
// sequence algorithm efficiently and if we understand how fibonacci
// fractal is made.

void start(const std::vector<std::string> &args) {
	if (args.size() != 2) {
		throw std::runtime_error("wrong number of cmd args");
	}

	solve_four(args);
}

// 1
// 
// this will be the iterative version since it's much faster on
// big inputs
long long fib(long long n) {
	// we do not consider the negative case, this must
	// be handled by the caller
	if (n < 2) {
		return n;
	}
	else {
		long long val0 = 0, val1 = 1;

		for (int i = 0; i < n - 1; ++i) {
			long long tmp = val1;
			val1 += val0;
			val0 = tmp;
		}

		return val1;
	}
}

// 2

// test for primality using trial division, it doens't make much sense to
// implement more sophisticated algorithms
bool is_prime(long long n) {
	if (n < 2) {
		return false;
	}
	else {
		for (long long i = 2; i * i <= n; ++i) {
			if (n % i == 0) {
				return false;
			}
		}

		return true;
	}
}


// 3

// convert a number to its representation in binary as a string
std::string convert_to_bin(long long n) {
	std::string output;

	while (n > 0) {
		switch (n % 2) {
		case 0:
			output.push_back('0');
			break;
		case 1:
			output.push_back('1');
			break;
		default:
			break;
		}

		n /= 2;
	}

	// least significant will be the first one so the result
	// is reversed, we reverse it again to get the proper rep
	std::reverse(output.begin(), output.end());

	return output;
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

void solve_one(const std::vector<std::string> &args) {
	std::ostringstream ostr;

	ostr << "fib(10) = " << fib(10) << '\n';
	ostr << "fib(20) = " << fib(20) << '\n';
	ostr << "fib(30) = " << fib(30) << '\n';
	ostr << "fib(40) = " << fib(40) << '\n';

	write_file(args[1], "67.1\n" + ostr.str() + "\n\n");
}

void solve_two(const std::vector<std::string> &args) {
	std::ostringstream ostr;

	for (int i = 1; i <= 40; ++i) {
		long long num = fib(i);

		if (is_prime(num)) {
			ostr << "fib(" << i << ") = " << num << " jest liczba pierwsza\n";
		}
	}

	write_file(args[1], "67.2\n" + ostr.str() + "\n\n");
}

// the resulting data should somehow be used to create
// the fractal as a rectangular matrix where 1 stands for
// black cell and 0 for white one
void solve_three(const std::vector<std::string> &args) {
	std::vector<std::string> reps;
	std::ostringstream ostr;

	for (int i = 1; i <= 40; ++i) {
		long long val = fib(i);
		reps.push_back(convert_to_bin(val));
	}

	std::vector<std::string>::size_type last_size = (reps.end() - 1)->size();

	for (auto &x : reps) {
		int diff = last_size - x.size();
		
		x = std::string(diff, '0') + x;
	}

	for (const auto &x : reps) {
		ostr << x << '\n';
	}

	write_file(args[1], ostr.str());
}

void solve_four(const std::vector<std::string> &args) {
	std::ostringstream ostr;
	constexpr unsigned one_count = 6;

	for (int i = 1; i <= 40; ++i) {
		auto val = fib(i);
		auto bin_rep(convert_to_bin(val));

		if (std::count(bin_rep.cbegin(), bin_rep.cend(), '1') == one_count) {
			ostr << "fib(" << i << ") = " << bin_rep << '\n';
		}
	}

	write_file(args[1], "67.4\n" + ostr.str() + "\n\n");
}