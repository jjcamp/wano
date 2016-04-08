#pragma once
#include <vector>
#include <string>

namespace wano {
	class RawDocument : public std::vector<std::string> {
	public:
		RawDocument() :
			std::vector<std::string> ()
		{}
	};
}