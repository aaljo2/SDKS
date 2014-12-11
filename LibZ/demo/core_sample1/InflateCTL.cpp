#include "InflateCTL.h"
#include <zlib.h>
#include <vector>
#include <fstream>

//Auto_Inflate
class Auto_Inflate
{
private:
	z_stream& stream_;
	int ret_;

public:
	explicit Auto_Inflate(z_stream& stream) :stream_(stream){
		ret_ = inflateInit(&stream_);
	}

	~Auto_Inflate(){
		if (Z_OK != ret_) return;
		inflateEnd(&stream_);
	}

	bool operator !() const {
		return Z_OK != ret_;
	}
};

//InflateCTL
bool
InflateCTL::inflate(std::string inputfile, std::string outputfile){
	z_stream stream;
	std::memset(&stream, 0, sizeof(z_stream));
	// set::memset는 string 헤더
	// z_stream 타입은 TriviallyCopyable 조건 만족

	Auto_Inflate auto_inflate(stream);
	if (!auto_inflate) return false;

	std::ifstream fp(inputfile, std::ios_base::binary);
	if (!fp) return false;

	std::ofstream wp(outputfile, std::ios_base::binary);
	if (!wp) return false;

	const int INPUTSIZE = 1024;
	std::vector<Bytef> in(INPUTSIZE);
	std::vector<Bytef> out(INPUTSIZE);

	do{
		fp.read(reinterpret_cast<char*>(in.data()), INPUTSIZE);
		stream.avail_in = (int)fp.gcount();
		stream.next_in = in.data();

		do{
			stream.avail_out = out.size();
			stream.next_out = out.data();
			::inflate(&stream, Z_NO_FLUSH);

			int dsize = out.size() - stream.avail_out;
			wp.write(reinterpret_cast<const char*>(out.data()), dsize);
		} while(0 != stream.avail_in);

	} while (!fp.eof());
	return true;
}