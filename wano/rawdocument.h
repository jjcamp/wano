#pragma once
#include <deque>
#include <string>
#include <istream>

namespace wano {
	class RawDocument : public std::deque<std::string> {
	public:
		RawDocument();
		RawDocument(std::istream& is);
	};
}