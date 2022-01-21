#include "matura.h"
#include <string>
#include <iostream>

int main(int argc, char **argv) {
	try {
		solve_four(std::vector<std::string>(argv, argv + argc));
	}
	catch (std::runtime_error err) {
		std::cerr << err.what() << '\n';
	}

	return 0;
}