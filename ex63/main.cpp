#include "matura.h"

#include <iostream>
#include <stdexcept>

int main(int argc, char **argv) {
	try {
		start(std::vector<std::string>(argv, argv + argc));
	}
	catch (const std::runtime_error &e) {
		std::cerr << e.what() << '\n';
		return -1;
	}

	return 0;
}