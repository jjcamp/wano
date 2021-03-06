#pragma once

#include <iostream>
#include <string>
#include "rawdocument.h"
#include "events.h"

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

		void write(std::ostream& stream);
		static Document fromString(std::string str);
	private:
		RawDocument buffer;
		coord curs;
	};
}