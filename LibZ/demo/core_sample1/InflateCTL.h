#pragma once
#include <string>
//InflateCTL
class InflateCTL
{
public:
public:
	InflateCTL() = delete;
	InflateCTL(const InflateCTL&) = delete;
	InflateCTL(InflateCTL&&) = delete;
	InflateCTL& operator = (const InflateCTL&) = delete;
	InflateCTL&& operator = (InflateCTL&&) = delete;
	~InflateCTL() = delete;

	static bool inflate(std::string inputfile, std::string outputfile);
};

