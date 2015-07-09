/*
 * Testapplication for use when developing
 *
 * Copyright (C) 2015 Martin Schwarz
 */

#include <iostream>
#include "core/util/Sample.hpp"
#include "core/util/AudioBuffer.hpp"

using namespace maudio;

int main(int argc, char *argv[]){
	std::cerr << "test" << std::endl;

	Sample s(std::vector<float>{5, 2, 1});
	std::cout << s[2] << std::endl;

	return 0;
}
