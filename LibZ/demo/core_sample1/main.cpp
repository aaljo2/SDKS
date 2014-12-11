#include <iostream>
#include "DeflateCTL.h"
#include "InflateCTL.h"

int main(int argc, char* argv[])
{
	if (argc != 4){
		std::cout << "need argument 4" << std::endl;
		return 0;
	}
	auto ret = DeflateCTL::deflate(argv[1], argv[2]);
	std::cout << "DeflateCTL result:" << ret << std::endl;

	ret = InflateCTL::inflate(argv[2], argv[3]);
	std::cout << "InflateCTL result:" << ret << std::endl;

	return 0;
}
