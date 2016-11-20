#include "file.h"

using namespace std;

namespace wano {
	File::File() :
		fs::path()
	{}

	File::File(const std::string& filePath) :
		fs::path(filePath)
	{}

	bool File::exists() {
		return fs::status(*this).type() == fs::file_type::regular_file;
	}

	Document File::createDocument() {
		if (!this->exists())
			throw FileNotFoundException();
		auto stream = ifstream(this->string(), ios::in);
		return Document(stream);
	}
}