#include "matura.h"

#include <cmath>

std::string dec_to_bin(long long val) {
	bool is_negative = false;

	if (val < 0) {
		is_negative = true;
		val = -val;
	}

	std::ostringstream bin_rep;

	while (val) {
		bin_rep << val % 2;
		val /= 2;
	}

	std::string bin_str(bin_rep.str());
	std::reverse(bin_str.begin(), bin_str.end());

	return '-' + bin_str;
}

int convert_to_base(const std::string &num, int base) {
	if (!num.empty() && num.front() == '-') {
		return -(std::stoi(num.substr(1, num.size() - 1)), nullptr, base);
	}
	else {
		return std::stoi(num, nullptr, base);
	}
}

std::vector<weather_rec> read_file(const std::string &file_name, int base) {
	std::ifstream ifs(file_name);

	if (ifs) {
		std::vector<weather_rec> input_data;

		for (std::string line; std::getline(ifs, line);) {
			std::istringstream istr(line);
			std::string clock, temp;
			istr >> clock >> temp;

			input_data.emplace_back(std::stoi(clock, nullptr, base),
				std::stoi(temp, nullptr, base));
		}

		return input_data;
	}
	else {
		throw std::runtime_error("could not open the file " + file_name);
	}
}

void solve_one(const std::vector<std::string> &args) {
	if (args.size() != 4) {
		throw std::runtime_error("wrong number of cmd args");
	}

	auto first_station_data = read_file(args[1], 2);
	auto second_station_data = read_file(args[2], 4);
	auto third_station_data = read_file(args[3], 8);

	auto f = [](const weather_rec &lhs, const weather_rec &rhs) {
		return lhs.second < rhs.second;
	};

	auto first_station_min = std::min_element(first_station_data.cbegin(),
		first_station_data.cend(), f);

	auto second_station_min = std::min_element(second_station_data.cbegin(),
		second_station_data.cend(), f);

	auto third_station_min = std::min_element(third_station_data.cbegin(),
		third_station_data.cend(), f);

	std::cout << "minimum temperature for the first station: " <<
		dec_to_bin(first_station_min->second) << '\n';
	std::cout << "minimum temperature for the second station: " <<
		dec_to_bin(second_station_min->second) << '\n';
	std::cout << "minimum temperature for the third station: " <<
		dec_to_bin(third_station_min->second) << '\n';
}

void solve_two(const std::vector<std::string> &args) {
	if (args.size() != 4) {
		throw std::runtime_error("wrong number of cmd args");
	}
	std::vector<std::vector<weather_rec>> readings(3);
	readings[0] = read_file(args[1], 2);
	readings[1] = read_file(args[2], 4);
	readings[2] = read_file(args[3], 8);

	unsigned wrong_clock_ctr = 0;
	unsigned correct_clock = 12;

	for (decltype(readings[0].size()) i = 0; i != readings[0].size(); ++i) {
		if (readings[0][i].first != correct_clock &&
			readings[1][i].first != correct_clock &&
			readings[2][i].first != correct_clock) {

			++wrong_clock_ctr;
		}

		correct_clock += 24;
	}

	std::cout << "number of wrong simultaneous clock readings: "
		<< wrong_clock_ctr << '\n';
}

void solve_three(const std::vector<std::string> &args) {
	if (args.size() != 4) {
		throw std::runtime_error("wrong number of cmd args");
	}

	std::vector<std::vector<weather_rec>> readings(3);
	readings[0] = read_file(args[1], 2);
	readings[1] = read_file(args[2], 4);
	readings[2] = read_file(args[3], 8);

	std::vector<int> records{ readings[0][0].second,
		readings[1][0].second, readings[2][0].second };

	unsigned record_day_ctr = 1;

	for (decltype(readings[0].size()) i = 1; i != readings[0].size(); ++i) {
		bool record_day = false;

		if (readings[0][i].second > records[0]) {
			record_day = true;
			records[0] = readings[0][i].second;
		}
		if (readings[1][i].second > records[1]) {
			record_day = true;
			records[1] = readings[1][i].second;
		}
		if (readings[2][i].second > records[2]) {
			record_day = true;
			records[2] = readings[2][i].second;
		}

		if (record_day) {
			++record_day_ctr;
		}
	}

	std::cout << "number of record days: " << record_day_ctr << '\n';
}

void solve_four(const std::vector<std::string> &args) {
	if (args.size() != 4) {
		throw std::runtime_error("wrong number of cmd args");
	}

	auto reading = read_file(args[1], 2);
	int max_jump = 0;

	for (int i = 0; i != reading.size() - 1; ++i) {
		for (int j = i + 1; j != reading.size(); ++j) {
			int jump = static_cast<int>(std::ceil(
				std::pow(reading[i].second - reading[j].second, 2) / std::abs(i - j)));

			if (jump > max_jump) {
				max_jump = jump;
			}
		}
	}

	std::cout << "greatest jump is " << max_jump << '\n';
}
