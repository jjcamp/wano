#pragma once

#include <memory>
#include <string>
#include "document.h"
#include "file.h"

namespace wano {
	class NamedDocument {
	private:
		std::shared_ptr<Document> _doc;
		std::unique_ptr<File> _file;

	public:
		NamedDocument(std::shared_ptr<Document> doc);
		NamedDocument(std::shared_ptr<Document> doc, File file);
		NamedDocument(std::shared_ptr<Document> doc, const std::string& filePath);
		
		bool hasFile();
		File file();
		std::shared_ptr<Document> document();

		void toFile();

		static NamedDocument fromFile(File file);
		static NamedDocument fromFile(const std::string& filePath);
	};
}