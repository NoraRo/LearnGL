#include "IO.h"

#include <string>
#include <fstream>
#include <streambuf>

namespace io
{
	using namespace std;

	string
	read_file(const char* path)
	{
		std::ifstream t(path);
		std::string constent((std::istreambuf_iterator<char>(t)),
						std::istreambuf_iterator<char>());
		return constent;
	}
}
