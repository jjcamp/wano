#pragma once

#include <exception>
#include <string>
#include <boost/filesystem.hpp>
#include "document.h"

namespace fs = boost::filesystem;

namespace wano {
	class File : public fs::path {
	public:
		File() : fs::path() {}
		File(const std::string& filePath) : fs::path(filePath) {}

		bool exists() {
			return fs::status(*this).type() == fs::file_type::regular_file;
		}
	};

	class FileException : public std::exception {
		const char* what() const throw() {
			return "Filesystem Error";
		}
	};
}