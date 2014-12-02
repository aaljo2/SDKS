// zip_Simple1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "ZipCTL.h"

int _tmain(int argc, _TCHAR* argv[])
{	
	if (argc < 3) return 0;
	
	ZipCTL ctl(argv[1]);

	for (int i = 2; i < argc; ++i){
		ctl.append_file(argv[i]);
	}

	return 0;
}

