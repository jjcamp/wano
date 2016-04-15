#pragma once
#include <deque>
#include <string>

namespace wano {
	class RawDocument : public std::deque<std::string> {
	public:
		RawDocument() :	std::deque<std::string>() {
			this->emplace_back(std::string(""));
		}
	};
}