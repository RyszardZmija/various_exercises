#include "matura.h"
#include <stdexcept>
#include <iostream>

int main(int argc, char **argv) {
	try {
		solve_three(std::vector<std::string>(argv, argv + argc));
	}
	catch (const std::runtime_error &err) {
		std::cerr << err.what() << '\n';
	}

	return 0;
}