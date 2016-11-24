#include "nameddocument.h"

using namespace std;

namespace wano {
	NamedDocument::NamedDocument(shared_ptr<Document> doc) :
		_doc{ doc }
	{}

	NamedDocument::NamedDocument(shared_ptr<Document> doc, File file) :
		_doc{ doc },
		_file(make_unique<File>(file))
	{}

	NamedDocument::NamedDocument(shared_ptr<Document> doc, const std::string& filePath) :
		_doc{ doc },
		_file(make_unique<File>(filePath))
	{}

	bool NamedDocument::hasFile() {
		return this->_file != nullptr;
	}

	File NamedDocument::file() {
		if (this->hasFile())
			return *this->_file;
		return File();
	}

	shared_ptr<Document> NamedDocument::document() {
		return this->_doc;
	}

	void NamedDocument::toFile() {
		auto stream = ofstream(this->_file->string(), ios::out);
		if (stream.fail())
			throw FileException();
		this->_doc->write(stream);
	}

	NamedDocument NamedDocument::fromFile(File file) {
		if (!file.exists())
			return NamedDocument(make_shared<Document>(), file);
		auto stream = ifstream(file.string(), ios::in);
		return NamedDocument(make_shared<Document>(stream), file);
	}

	NamedDocument NamedDocument::fromFile(const string& filePath) {
		return NamedDocument::fromFile(File(filePath));
	}
}