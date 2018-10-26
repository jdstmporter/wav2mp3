/*
 * mp3.cpp
 *
 *  Created on: 23 Apr 2018
 *      Author: julianporter
 */

#include <fstream>
#include "mp3info.hpp"

int main(int argc,char *argv[]) {
	try {

		std::string infile(argv[1]);
		mp3::MP3Test test(infile);
		test.parse(false);
		auto result=test();
		std::cout << *result << std::endl;
	}
	catch(std::exception &e) {
			std::cerr << e.what() << std::endl;
		}
		return 0;
}


