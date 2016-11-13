#include "rawdocument.h"

using namespace std;

namespace wano {
	RawDocument::RawDocument() :
		deque<string>() {
		this->emplace_back(string());
	}

	RawDocument::RawDocument(istream& stream) :
		deque <string>() {
		auto line = std::string();
		int ch;
		while ((ch = stream.get()) && !stream.eof()) {
			switch (ch) {
			case (char)'\r':
				continue;
			case (char)'\n':
				this->emplace_back(line);
				line = std::string();
				continue;
			default:
				line += ch;
			}
		}
		this->emplace_back(line);
	}
}