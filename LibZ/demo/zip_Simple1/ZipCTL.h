#pragma once
#include <zip.h>
#include <string>

class ZipCTL
{
private:
	zipFile zf_;

public:
	explicit ZipCTL(std::string fname);

	bool append_file(std::string fname, int level = Z_DEFAULT_COMPRESSION);

	~ZipCTL();
};

void operator<<(tm_zip& tmz_date, const time_t& gtime);