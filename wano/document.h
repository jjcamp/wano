#pragma once

#include <vector>
#include <memory>
#include <functional>
#include <iostream>
#include <fstream>
#include <sstream>
#include <boost/filesystem.hpp>
#include "rawdocument.h"
#include "events.h"

namespace fs = boost::filesystem;

namespace wano {
	typedef struct {
		int x;
		int y;
	} coord;

	class Document {
	public:
		Document();
		Document(std::istream& stream);
		coord insCh(int ch);
		coord delCh();
		coord newLine();
		coord cursMove(int x, int y);
		coord cursRight(int num);
		coord cursRight();
		coord cursLeft(int num);
		coord cursLeft();
		coord cursDown(int num);
		coord cursDown();
		coord cursUp(int num);
		coord cursUp();
		coord cursEnd();
		coord cursHome();
		coord insStr(const std::string&& str);
		const std::string& readLine(int line) const;

		static Document fromString(std::string str);
		static Document fromFile(fs::path file);
	private:
		RawDocument buffer;
		coord curs;
	};
}