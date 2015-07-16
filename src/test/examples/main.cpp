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

	Sample s(std::vector<float>{5, 2});
	float x = s[1];
	s[1] = 50;
	x = 10;
	std::cout << s[1] << " " << x << std::endl;

	AudioBuffer b(10, 2);
	b.set(2, s);

	try{
		std::cout << b[2][0] << std::endl;
	}
	catch(std::exception &e){
		std::cout << e.what() << std::endl;
	}

	return 0;
}
