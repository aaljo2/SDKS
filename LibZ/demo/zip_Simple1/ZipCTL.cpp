#include "ZipCTL.h"
#include <filesystem>
#include <fstream>

void operator<<(tm_zip& tmz_date, const time_t& gtime){
	struct tm* tdata = std::localtime(&gtime);
	tmz_date.tm_year = tdata->tm_year;
	tmz_date.tm_mon = tdata->tm_mon;
	tmz_date.tm_mday = tdata->tm_mday;
	tmz_date.tm_hour = tdata->tm_hour;
	tmz_date.tm_min = tdata->tm_min;
	tmz_date.tm_sec = tdata->tm_sec;
};

ZipCTL::ZipCTL(std::string fname) {
	using namespace std::tr2::sys;

	path myfile(fname);
	int flags = exists(myfile) ? APPEND_STATUS_ADDINZIP : APPEND_STATUS_CREATE;
	this->zf_ = zipOpen(fname.data(), flags);
}

bool 
ZipCTL::append_file(std::string fname, int level){
	using namespace std::tr2::sys;

	path myfile(fname);
	if (!exists(myfile) || !this->zf_) return false;
	
	std::ifstream fp(fname, std::ios_base::binary);
	if (!fp) return false;

	zip_fileinfo info;
	std::memset(&info, 0, sizeof(zip_fileinfo));
	info.dosDate = false;

	std::time_t gtime = last_write_time(myfile);
	info.tmz_date << gtime;
	
	auto ret = zipOpenNewFileInZip(
		this->zf_,	myfile.filename().c_str(),
		&info,nullptr,
		0,nullptr,
		0,"comment",
		Z_DEFLATED,	level);
	if (ZIP_OK != ret)	return false;
			
	auto aclose = make_Auto_Close(this->zf_, zipCloseFileInZip);

	const int BUF = 1024;
	Bytef in[BUF];

	do{
		fp.read((char*)in, BUF);
		auto readsize = fp.gcount();
		ret = zipWriteInFileInZip(this->zf_, in, static_cast<unsigned int>(readsize));
		if (ZIP_OK != ret)	return false;
	} while (!fp.eof());

	return true;
}

ZipCTL::~ZipCTL(){
	if (!this->zf_) return;
	zipClose(zf_, "global_comment");
	this->zf_ = nullptr;
}
