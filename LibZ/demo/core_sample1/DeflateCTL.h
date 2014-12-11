#pragma once
#include <string>
//DeflateCTL
class DeflateCTL{
public:
	DeflateCTL()= delete;
	DeflateCTL(const DeflateCTL&) = delete;
	DeflateCTL(DeflateCTL&&) = delete;
	DeflateCTL& operator = (const DeflateCTL&) = delete;
	DeflateCTL&& operator = (DeflateCTL&&) = delete;
	~DeflateCTL() = delete;

	static bool deflate(std::string inputfile, std::string outputfile);
};

