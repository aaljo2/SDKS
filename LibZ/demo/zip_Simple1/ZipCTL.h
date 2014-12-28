#pragma once
#include <zip.h>
#include <string>

void operator<<(tm_zip& tmz_date, const time_t& gtime);

template<typename T, typename FN >
class Auto_Close{
private:
	T& data_;
	FN& fn_;
public:
	Auto_Close(T& data, FN& fn) :data_{ data }, fn_{ fn }
	{
	}

	~Auto_Close(){
		fn_(data_);
	}
};

template<typename T, typename FN >
Auto_Close<T, FN> 
make_Auto_Close(T& data, FN& fn){
	return Auto_Close<T, FN>(data, fn);
};

//ZipCTL
class ZipCTL{
private:
	zipFile zf_;
	
public:
	explicit ZipCTL(std::string fname);
	bool append_file(std::string fname, int level = Z_DEFAULT_COMPRESSION);

	~ZipCTL();
};


