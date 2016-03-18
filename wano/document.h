#pragma once

#include <vector>
#include <memory>
#include <functional>
#include "events.h"

namespace wano {
	typedef struct {
		int x;
		int y;
	} coord;

	class Document {
	public:
		Document(std::shared_ptr<EventQueue> eq);
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
		std::vector<int> readLine(int line);

	private:
		std::vector<std::shared_ptr<std::vector<int>>> buffer;
		coord curs;
		std::shared_ptr<EventQueue> eq;
	};
}