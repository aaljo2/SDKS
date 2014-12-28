// directory_list.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <iostream>
#include <string>
#include <filesystem>
#include <vector>


void folderlist(std::tr2::sys::path root, std::vector<std::tr2::sys::path>& filelist){
	using namespace std::tr2::sys;

	directory_iterator path_end;
	directory_iterator itr;
	for (itr = root; itr != path_end; ++itr){
		if (is_directory(itr->path())){
			folderlist(*itr, filelist);
			continue;
		}
		filelist.push_back(itr->path());
	}
}

int _tmain(int argc, _TCHAR* argv[]){
	std::string mdir = ".";
	std::vector<std::tr2::sys::path> filelist;
	folderlist(std::tr2::sys::path(mdir), filelist);
	
	for (auto& item : filelist){
		std::string mpath = item.string().substr(mdir.size() + 1);
		std::cout << mpath << std::endl;
	}

	return 0;
}

