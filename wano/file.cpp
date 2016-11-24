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
			return Document();
		auto stream = ifstream(this->string(), ios::in);
		return Document(stream);
	}

	void File::saveDocument(shared_ptr<Document> doc) {
		auto stream = ofstream(this->string(), ios::out);
		if (stream.fail())
			throw FileException();
		doc->write(stream);
	}
}