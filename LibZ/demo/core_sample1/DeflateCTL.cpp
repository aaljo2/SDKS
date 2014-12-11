#include "DeflateCTL.h"
#include <zlib.h>
#include <vector>
#include <fstream>

//Auto_Deflate
class Auto_Deflate
{
private:
	z_stream& stream_;
	int ret_;
public:
	explicit Auto_Deflate(z_stream& stream) :stream_(stream){
		ret_ = deflateInit(&stream_, Z_DEFAULT_COMPRESSION);
	}

	~Auto_Deflate(){
		if (Z_OK != ret_) return;
		deflateEnd(&stream_);
	}

	bool operator !() const {
		return Z_OK != ret_;
	}
};

//DeflateCTL
bool 
DeflateCTL::deflate(std::string inputfile, std::string outputfile){
	z_stream stream;
	std::memset(&stream, 0, sizeof(z_stream));
	// set::memset는 string 헤더
	// z_stream 타입은 TriviallyCopyable 조건 만족

	Auto_Deflate auto_deflate(stream);
	if (!auto_deflate) return false;
		
	std::ifstream fp(inputfile, std::ios_base::binary);
	if (!fp) return false;
		
	std::ofstream wp(outputfile, std::ios_base::binary);
	if (!wp) return false;

	const int INPUTSIZE = 1024;
	std::vector<Bytef> in(INPUTSIZE);
	std::vector<Bytef> out(deflateBound(&stream, INPUTSIZE));

	do{
		fp.read(reinterpret_cast<char*>(in.data()), INPUTSIZE);

		stream.avail_in = (int)fp.gcount();
		stream.next_in = in.data();

		int flush = Z_NO_FLUSH;
		if (fp.eof()) { flush = Z_FINISH; }

		stream.avail_out = out.size();
		stream.next_out = out.data();
		::deflate(&stream, flush);

		int dsize = out.size() - stream.avail_out;
		wp.write(reinterpret_cast<const char*>(out.data()), dsize);
	} while (!fp.eof());

	return true;
}

