#pragma once
#include <deque>
#include <string>
#include <iostream>

namespace wano {
	class RawDocument : public std::deque<std::string> {
	public:
		RawDocument();
		RawDocument(std::istream& is);
		void write(std::ostream& os);
	};
}