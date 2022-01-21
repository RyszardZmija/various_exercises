#include "matura.h"

#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>

int main(int argc, char **argv) {
	try {
		solve_three(std::vector<std::string>(argv, argv + argc));
	}
	catch (std::runtime_error err) {
		std::cerr << err.what() << '\n';
	}

	return 0;
}