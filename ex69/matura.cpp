#include "matura.h"

#include <fstream>

#include <map>
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

std::vector<std::string> find_genes(const std::string &genotype) {
	std::vector<std::string> genes;
	std::string::size_type i = 0;

	while (i < genotype.size()) {
		auto start_index = genotype.find("AA", i);
		decltype(start_index) end_index = 0;

		if (start_index < genotype.size()) {
			end_index = genotype.find("BB", start_index);

			if (end_index < genotype.size()) {
				genes.push_back(genotype.substr(start_index, end_index - start_index + 2));
			}
			else {
				break;
			}
		}
		else {
			break;
		}
		
		i = end_index + 1;
	}

	return genes;
}

bool is_palindrome(const std::string &str) {
	std::string cpy(str);

	std::reverse(cpy.begin(), cpy.end());

	return str == cpy;
}

void start(const std::vector<std::string> &args) {
	if (args.size() != 3) {
		throw std::runtime_error("wrong number of cmd line args");
	}

	solve_four(args);
}

void solve_one(const std::vector<std::string> &args) {
	auto input(read_file(args[1]));

	std::map<unsigned, unsigned> species_map;

	for (const auto &x : input) {
		++species_map[x.size()];
	}

	auto max_elem = std::max_element(species_map.cbegin(), species_map.cend(),
		[](std::pair<unsigned, unsigned> p1, std::pair<unsigned, unsigned> p2) {
			return p1.second < p2.second;
		});

	const std::string out = "69.1\nliczba gatunkow: " + std::to_string(species_map.size()) +
		"\nnajwieksza liczba osobnikow reprezentujacych ten sam gatunek: " + std::to_string(max_elem->second) + "\n\n";

	write_file(args[2], out);
}

void solve_two(const std::vector<std::string> &args) {
	auto input(read_file(args[1]));
	const std::string mutating_gene("BCDDC");

	unsigned satisfied_ctr = 0;

	for (const auto &x : input) {
		auto genes(find_genes(x));

		for (const auto &g : genes) {
			if (g.find(mutating_gene) != std::string::npos) {
				++satisfied_ctr;
				break;
			}
		}
	}

	write_file(args[2], "69.2\nliczba osobnikow z mutacja: " + std::to_string(satisfied_ctr) + "\n\n");
}

void solve_three(const std::vector<std::string> &args) {
	auto input(read_file(args[1]));
	
	unsigned max_genes = 0, longest_gene_size = 0;

	for (const auto &x : input) {
		auto genes(find_genes(x));

		for (const auto &g : genes) {
			if (g.size() > longest_gene_size) {
				longest_gene_size = g.size();
			}
		}

		if (genes.size() > max_genes) {
			max_genes = genes.size();
		}
	}

	write_file(args[2], "69.3\nnajwieksza liczba genow u jednego osobnika: " + std::to_string(max_genes)
		+ "\nnajwieksza dlugosc genu: " + std::to_string(longest_gene_size) + "\n\n");
}

void solve_four(const std::vector<std::string> &args) {
	auto input(read_file(args[1]));

	unsigned strong_immunity_ctr = 0, moderate_immunity_ctr = 0;

	for (const auto &x : input) {
		if (is_palindrome(x)) {
			++strong_immunity_ctr;
			++moderate_immunity_ctr;
		}
		else {
			std::string cpy(x);
			std::reverse(cpy.begin(), cpy.end());

			auto genes1(find_genes(x)), genes2(find_genes(cpy));

			if (genes1 == genes2) {
				++moderate_immunity_ctr;
			}
		}
	}

	const std::string out = "69.4\nliczba silnie odpornych: " + std::to_string(strong_immunity_ctr) +
		"\nliczba odpornych: " + std::to_string(moderate_immunity_ctr) + "\n\n";

	write_file(args[2], out);
}