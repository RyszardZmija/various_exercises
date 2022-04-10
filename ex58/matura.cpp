#include "matura.h"

#include <utility>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <algorithm>

#include <set>

std::vector<temp_rec> read_file(const std::string &file_name, int base) {
	std::ifstream ifs(file_name);

	if (ifs) {
		std::vector<temp_rec> input;

		for (std::string line; std::getline(ifs, line);) {
			std::istringstream istr(line);

			std::string comp;
			istr >> comp;

			int time = std::stoi(comp, nullptr, base);
			
			istr >> comp;

			int temp = std::stoi(comp, nullptr, base);

			input.emplace_back(time, temp);
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
	if (args.size() != 5) {
		throw std::runtime_error("wrong number of cmd args");
	}

	solve_four(args);
}

std::string convert_to_bin(int val) {
	std::string bin_rep;
	bool negative = false;

	if (val < 0) {
		negative = true;
		val = -val;
	}

	while (val > 0) {
		int rem = val % 2;

		switch (rem) {
		case 0:
			bin_rep.push_back('0');
			break;
		case 1:
			bin_rep.push_back('1');
			break;
		}

		val /= 2;
	}

	if (negative) {
		bin_rep.push_back('-');
	}

	std::reverse(bin_rep.begin(), bin_rep.end());

	return bin_rep;
}

temp_rec find_smallest_temp(const std::vector<temp_rec> &vec) {
	int min_time = vec[0].first, min_temp = vec[0].second;

	for (int i = 1; i != vec.size(); ++i) {
		if (vec[i].second < min_temp) {
			min_temp = vec[i].second;
			min_time = vec[i].first;
		}
	}

	return std::pair<int, int>(min_time, min_temp);
}

std::set<int> find_recs(const std::vector<temp_rec> &vec) {
	std::set<int> rec{ 1 };

	unsigned day_ctr = 2;
	int temp_max = vec[0].second;

	for (int i = 1; i != vec.size(); ++i) {
		if (vec[i].second > temp_max) {
			rec.insert(day_ctr);
			temp_max = vec[i].second;
		}

		++day_ctr;
	}

	return rec;
}


void solve_one(const std::vector<std::string> &args) {
	auto b_one_temp(read_file(args[1], 2));
	auto b_two_temp(read_file(args[2], 4));
	auto b_three_temp(read_file(args[3], 8));

	int b_one_lowest = find_smallest_temp(b_one_temp).second;
	int b_two_lowest = find_smallest_temp(b_two_temp).second;
	int b_three_lowest = find_smallest_temp(b_three_temp).second;

	const std::string out = "58.1\n\nstacja 1: " + convert_to_bin(b_one_lowest) +
		"\nstacja 2: " + convert_to_bin(b_two_lowest) + "\n" +
		"stacja 3: " + convert_to_bin(b_three_lowest) + "\n\n";

	write_file(args[4], out);
}

void solve_two(const std::vector<std::string> &args) {
	auto b_one_temp(read_file(args[1], 2));
	auto b_two_temp(read_file(args[2], 4));
	auto b_three_temp(read_file(args[3], 8));

	unsigned satisfied_ctr = 0;
	int clock = 12;

	// all vectors will have the same size because of the nature of the data
	for (decltype(b_one_temp.size()) i = 0; i != b_one_temp.size(); ++i) {
		if (b_one_temp[i].first != clock && b_two_temp[i].first != clock
			&& b_three_temp[i].first != clock) {

			++satisfied_ctr;
		}

		clock += 24;
	}

	write_file(args[4], "58.2\n" + std::to_string(satisfied_ctr) + "\n\n");
}

void solve_three(const std::vector<std::string> &args) {
	auto b_first_temp(read_file(args[1], 2));
	auto b_second_temp(read_file(args[2], 4));
	auto b_three_temp(read_file(args[3], 8));

	auto b_first_recs(find_recs(b_first_temp));
	auto b_second_recs(find_recs(b_second_temp));
	auto b_three_recs(find_recs(b_three_temp));

	std::set<int> record_days;
	record_days.insert(b_first_recs.cbegin(), b_first_recs.cend());
	record_days.insert(b_second_recs.cbegin(), b_second_recs.cend());
	record_days.insert(b_three_recs.cbegin(), b_three_recs.cend());

	write_file(args[4], "58.3\n" + std::to_string(record_days.size()) + "\n\n");
}

void solve_four(const std::vector<std::string> &args) {
	auto b_one_temp(read_file(args[1], 2));

	int max_jump = calc_temp_jmp(b_one_temp[0].second, 1, b_one_temp[1].second, 2);

	for (int j = 2; j < b_one_temp.size(); ++j) {
		int jump = calc_temp_jmp(b_one_temp[0].second, 1, b_one_temp[j].second,
			j + 1);

		if (jump > max_jump) {
			max_jump = jump;
		}
	}

	for (int i = 1; i < b_one_temp.size() - 1; ++i) {
		for (int j = i + 1; j < b_one_temp.size(); ++j) {
			int jump = calc_temp_jmp(b_one_temp[i].second, i + 1,
				b_one_temp[j].second, j + 1);

			if (jump > max_jump) {
				max_jump = jump;
			}
		}
	}

	write_file(args[4], "58.4\nmaksymalny skok: "
		+ std::to_string(max_jump) + "\n\n");
}