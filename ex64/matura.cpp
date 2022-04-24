#include "matura.h"

#include <fstream>
#include <sstream>
#include <set>

using matrix = std::vector<std::string>;

std::vector<matrix> read_file(const std::string &file_name) {
	std::ifstream ifs(file_name);

	if (ifs) {
		std::vector<matrix> input;
		matrix image;

		for (std::string line; std::getline(ifs, line);) {
			if (!line.empty()) {
				image.push_back(line);
			}
			else {
				input.push_back(image);
				image.clear();
			}
		}

		input.push_back(image);

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
		throw std::runtime_error("wrong number of the cmd line args");
	}

	solve_four(args);
}

void solve_one(const std::vector<std::string> &args) {
	auto input(read_file(args[1]));

	unsigned satisfied_ctr = 0, max_black_pixels = 0;

	for (const auto &x : input) {
		unsigned black_ctr = 0, white_ctr = 0;

		for (int i = 0; i != x.size() - 1; ++i) {
			for (int j = 0; j != x[i].size() - 1; ++j) {
				if (x[i][j] == '0') {
					++white_ctr;
				}
				else if (x[i][j] == '1') {
					++black_ctr;
				}
			}
		}

		if (black_ctr > max_black_pixels) {
			max_black_pixels = black_ctr;
		}

		if (black_ctr > white_ctr) {
			++satisfied_ctr;
		}
	}

	const std::string out = "1.\nliczba obrazkow bedacych rewersami: " + std::to_string(satisfied_ctr) +
		"\nnajwieksza liczba czarnych pikseli w obrazku: " + std::to_string(max_black_pixels) + "\n\n";

	write_file(args[2], out);
}

void solve_two(const std::vector<std::string> &args) {
	auto input(read_file(args[1]));

	matrix first_recursive;
	bool first = true;
	unsigned satisfied_ctr = 0;

	for (const auto &x : input) {
		std::vector<std::string> parts(4);

		for (int i = 0; i != 10; ++i) {
			for (int j = 0; j != 10; ++j) {
				parts[0].push_back(x[i][j]);
			}

			for (int j = 10; j != 20; ++j) {
				parts[1].push_back(x[i][j]);
			}
		}

		for (int i = 10; i != 20; ++i) {
			for (int j = 0; j != 10; ++j) {
				parts[2].push_back(x[i][j]);
			}

			for (int j = 10; j != 20; ++j) {
				parts[3].push_back(x[i][j]);
			}
		}

		if (parts[0] == parts[1] && parts[1] == parts[2] && parts[2] == parts[3]) {
			if (first) {
				first_recursive = x;
				first = false;
			}

			++satisfied_ctr;
		}
	}

	std::ostringstream ostr;

	for (int i = 0; i != first_recursive.size() - 1; ++i) {
		for (int j = 0; j != first_recursive[i].size() - 1; ++j) {
			ostr << first_recursive[i][j] << " ";
		}
		ostr << '\n';
	}

	const std::string out = "2.\nliczba obrazkow rekurencyjnych: " + std::to_string(satisfied_ctr) +
		"\npierwszy obrazek rekurencyjny:\n" + ostr.str() + "\n\n";

	write_file(args[2], out);
}

void solve_three(const std::vector<std::string> &args) {
	auto input(read_file(args[1]));

	unsigned correct = 0, fixable = 0, unfixable = 0;
	unsigned max_even_error = 0;

	for (const auto &x : input) {
		unsigned bad_row = 0, bad_col = 0;

		for (int i = 0; i != 20; ++i) {
			unsigned black = 0, white = 0;
			for (int j = 0; j != 20; ++j) {
				if (x[i][j] == '0') {
					++white;
				}
				else if (x[i][j] == '1') {
					++black;
				}
			}

			if (black % 2 == 0 && x[i][20] == '1' || black % 2 == 1 && x[i][20] == '0') {
				++bad_row;
			}
		}

		for (int j = 0; j != 20; ++j) {
			unsigned black = 0, white = 0;
			for (int i = 0; i != 20; ++i) {
				if (x[i][j] == '0') {
					++white;
				}
				else if (x[i][j] == '1') {
					++black;
				}
			}

			if (black % 2 == 0 && x[20][j] == '1' || black % 2 == 1 && x[20][j] == '0') {
				++bad_col;
			}
		}

		if (bad_row == 0 && bad_col == 0) {
			++correct;
		}
		else if (bad_row <= 1 && bad_col <= 1) {
			++fixable;
		}
		else {
			++unfixable;
		}

		if (bad_row + bad_col > max_even_error) {
			max_even_error = bad_row + bad_col;
		}
	}

	const std::string out = "3.\npoprawne: " + std::to_string(correct) +
		"\nnaprawialne: " + std::to_string(fixable) + "\nnienaprawialne: " + std::to_string(unfixable) +
		"\nnajwieksza ilosc blednych bitow: " + std::to_string(max_even_error) + "\n\n";

	write_file(args[2], out);
}

void solve_four(const std::vector<std::string> &args) {
	auto input(read_file(args[1]));
	std::ostringstream ostr;
	unsigned image_cnt = 1;

	for (const auto &x : input) {
		std::set<unsigned> row_err, col_err;

		for (int i = 0; i != 20; ++i) {
			unsigned black_ctr = 0;
			for (int j = 0; j != 20; ++j) {
				if (x[i][j] == '1') {
					++black_ctr;
				}
			}

			if (black_ctr % 2 == 0 && x[i][20] == '1' || black_ctr % 2 == 1 && x[i][20] == '0') {
				row_err.insert(i);
			}
		}

		for (int j = 0; j != 20; ++j) {
			unsigned black_ctr = 0;
			for (int i = 0; i != 20; ++i) {
				if (x[i][j] == '1') {
					++black_ctr;
				}
			}

			if (black_ctr % 2 == 0 && x[20][j] == '1' || black_ctr % 2 == 1 && x[20][j] == '0') {
				col_err.insert(j);
			}
		}

		if (!(col_err.size() == 0 && row_err.size() == 0) && col_err.size() <= 1 && row_err.size() <= 1) {
			if (row_err.size() == 1 && col_err.size() == 1) {
				ostr << image_cnt << ": " << *row_err.begin() + 1 << " " << *col_err.begin() + 1 << '\n';
			}
			else if (row_err.size() == 1 && col_err.size() == 0) {
				ostr << image_cnt << ": " << *row_err.begin() + 1 << " " << 21 << '\n';
			}
			else if (row_err.size() == 0 && col_err.size() == 1) {
				ostr << image_cnt << ": " << 21 << " " << *col_err.begin() + 1 << '\n';
			}
		}

		++image_cnt;
	}

	write_file(args[2], "4.\n" + ostr.str() + "\n\n");
}