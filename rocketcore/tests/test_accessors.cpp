#include "../src/Algorithm.h"

#include <iostream>

#include <unordered_map>
#include <vector>
using namespace rocket;

int main() {
	std::vector<int> v;
	std::unordered_map<int, int> m;
	m[1] = 2;
	m[3] = 56;
	m[7] = 1;

	auto t = std::make_tuple(1,2,3,4);
	getter<3> fourth;
	getter<1> tsecond;
	std::cout << fourth(t) << tsecond(t) << std::endl;

	transform(m, std::back_inserter(v), getter<0>{});
	transform(m, std::back_inserter(v), getter<1>{});

	for (auto& i : v) {
		std::cout << i << std::endl;
	}
}
