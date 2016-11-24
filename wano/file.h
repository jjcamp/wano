#pragma once

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <memory>
#include <boost/filesystem.hpp>
#include "document.h"

namespace fs = boost::filesystem;

namespace wano {
	class File : public fs::path {
	public:
		File();
		File(const std::string& filePath);

		bool exists();
		// If the file does not exist, creates an empty document
		Document createDocument();
		void saveDocument(std::shared_ptr<Document> doc);
	};

	class FileException : public std::exception {
		const char* what() const throw() {
			return "Filesystem Error";
		}
	};
}