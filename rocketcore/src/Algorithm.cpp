#define TEST_ALGORITHMS 1

#ifdef TEST_ALGORITHMS

#include "Algorithm.h"

#include <algorithm>
#include <iostream>
#include <map>
#include <string>

using namespace rocket;

void test_map() {
	std::map<int, std::string> m;
	m[2] = "Wohoo";
	m[7] = "Nohop";

	auto const m2 = m;

	find_and_apply(m, 2, [] (std::string& s) {
		std::cout << s << std::endl;
	});

	find_and_apply(m2, 2, [] (std::string const& s) {
		std::cout << s << std::endl;
	});
}

#endif
