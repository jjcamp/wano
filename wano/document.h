#pragma once

#include <vector>
#include <memory>
#include <functional>
#include "rawdocument.h"
#include "events.h"

namespace wano {
	typedef struct {
		int x;
		int y;
	} coord;

	class Document {
	public:
		Document(EventQueue* eq);
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
		const std::string& readLine(int line);

	private:
		RawDocument buffer;
		coord curs;
		EventQueue* eq;
	};
}