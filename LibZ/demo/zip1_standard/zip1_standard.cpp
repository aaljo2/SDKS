// zip1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "ZipCTL.h"

#include <string>
#include <fstream>

void simple_zip(std::string fname, std::string zfname){
	ZipCTL zf(zfname, APPEND_STATUS_CREATE);
	
	std::ifstream fp(fname, std::ios_base::binary);
	if (!fp) return;

	auto newzip = zf.factory_new(fname, fname);
	newzip<<fp;
}

int _tmain(int argc, _TCHAR* argv[]){
	simple_zip("test.txt", "test.zip");
	return 0;
}

