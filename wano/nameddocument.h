#pragma once

#include <memory>
#include <iostream>
#include "document.h"
#include "file.h"

namespace wano {
	class NamedDocument {
	private:
		std::weak_ptr<Document> _doc;
		std::unique_ptr<File> _file;

	public:
		NamedDocument(std::weak_ptr<Document> doc) : _doc{ doc } {}
		NamedDocument(std::weak_ptr<Document> doc, File file) :
			_doc{ doc }, _file(std::make_unique<File>(file)) {}
		NamedDocument(std::weak_ptr<Document> doc, const std::string& filePath) :
			_doc{ doc }, _file(std::make_unique<File>(filePath)) {}

		bool hasDoc() {
			return _doc.expired();
		}

		bool hasFile() {
			return _file != nullptr;
		}

		std::shared_ptr<Document> document() {
			return _doc.lock();
		}

		File file() {
			if (this->hasFile())
				return *_file;
			return File();
		}
	};
}