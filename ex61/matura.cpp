#include "matura.h"

#include <fstream>
#include <sstream>

#include <cmath>

using vec_vec_i = std::vector<std::vector<int>>;

vec_vec_i read_file(const std::string &file_name) {
	std::ifstream ifs(file_name);

	if (ifs) {
		vec_vec_i input;
		std::string size, progression;
		bool end = false;

		while (!end) {
			std::getline(ifs, size);
			std::getline(ifs, progression);

			std::vector<int> prog;
			std::istringstream istr(progression);

			for (int val = 0; istr >> val;) {
				prog.push_back(val);
			}

			input.push_back(prog);

			if (!ifs) {
				end = true;
			}
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

// 1
bool is_arithmetic(const std::vector<int> &prog) {
	// we know that is reality the size will be at least 5 so
	// we don't have to perform various checks
	int diff = prog[1] - prog[0];

	for (decltype(prog.size()) i = 2; i != prog.size(); ++i) {
		if (prog[i] - prog[i - 1] != diff) {
			return false;
		}
	}

	return true;
}

// 2
bool is_int_cube(int n) {
	double croot = std::cbrt(n);
	int i_part = static_cast<int>(croot);

	return croot - i_part == 0;
}

void solve_one(const std::vector<std::string> &args) {
	auto progs(read_file(args[1]));

	unsigned satisfied_ctr = 0;
	int greatest_diff = 0;
	bool first = true;

	for (const auto &x : progs) {
		if (is_arithmetic(x)) {
			++satisfied_ctr;

			if (first) {
				greatest_diff = x[1] - x[0];
				first = false;
			}
			else {
				if (x[1] - x[0] > greatest_diff) {
					greatest_diff = x[1] - x[0];
				}
			}
		}
	}

	const std::string out = "61.1\nliczba ciagow arytmetycznych: " +
		std::to_string(satisfied_ctr) + "\nnajwieksza roznica: " +
		std::to_string(greatest_diff) + "\n\n";

	write_file(args[2], out);
}

void solve_two(const std::vector<std::string> &args) {
	auto progs(read_file(args[1]));
	std::ostringstream ostr;
	unsigned ctr = 1;

	for (const auto &x : progs) {

		int greatest_cube = 0;
		bool first = true;

		for (const auto &v : x) {
			if (is_int_cube(v)) {
				if (first) {
					greatest_cube = v;
					first = false;
				}
				else {
					if (v > greatest_cube) {
						greatest_cube = v;
					}
				}
			}
		}

		ostr << "Ciag " << ctr << ": ";

		if (first) {
			ostr << "nie zostal znaleziony\n";
		}
		else {
			ostr << greatest_cube << "\n";
		}

		++ctr;
	}

	write_file(args[2], "61.2\n" + ostr.str() + "\n\n");
}

// use file bledne.txt
void solve_three(const std::vector<std::string> &args) {
	auto progs(read_file(args[1]));
	std::ostringstream ostr;
	unsigned ctr = 1;

	for (const auto &x : progs) {
		if (x[1] - x[0] != x[2] - x[1] && x[2] - x[1] == x[3] - x[2]) {
			ostr << "ciag " << ctr << ": " << x[0] << '\n';
		}
		else if (x[1] - x[0] != x[3] - x[2] &&
			x[2] - x[1] != x[3] - x[2] &&
			x[3] - x[2] == x[4] - x[3]) {

			ostr << "ciag " << ctr << ": " << x[1] << '\n';
		}
		else {
			int diff = x[1] - x[0];

			for (decltype(x.size()) i = 2; i != x.size(); ++i) {
				if (x[i] - x[i - 1] != diff) {
					ostr << "ciag " << ctr << ": " << x[i] << '\n';
					break;
				}
			}
		}

		++ctr;
	}

	write_file(args[2], "61.3\n\n" + ostr.str() + "\n\n");
}