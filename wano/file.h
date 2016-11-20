#pragma once

#include <fstream>
#include <stdexcept>
#include <boost/filesystem.hpp>
#include "document.h"

namespace fs = boost::filesystem;

namespace wano {
	class File : public fs::path {
	public:
		File();
		File(const std::string& filePath);

		bool exists();
		Document createDocument();
	};

	class FileException : public std::exception {
		const char* what() const throw() {
			return "Filesystem Error";
		}
	};

	class FileNotFoundException : public FileException {
		const char* what() const throw() {
			return "File Not Found";
		}
	};
}