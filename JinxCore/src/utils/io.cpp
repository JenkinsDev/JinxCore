#include "io.h"

namespace jinx { namespace utils { 

	std::string getFileContents(std::string fileName) {
		using namespace std;

		ifstream ifs(fileName);
		string content(
			(istreambuf_iterator<char>(ifs)),
			(istreambuf_iterator<char>())
			);

		return content;
	}

} }