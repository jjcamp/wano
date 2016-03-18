#include "document.h"

using namespace std;

namespace wano {
	Document::Document(shared_ptr<EventQueue> eq) :
		buffer(),
		eq{ eq }
	{
		curs.x = 0;
		curs.y = 0;
		buffer.push_back(make_shared<vector<int>>(0));
	}

	coord Document::insCh(int ch) {
		auto by = buffer[curs.y];
		by->insert(by->begin() + curs.x, ch);
		return this->cursRight();
	}

	coord Document::delCh() {
		auto by = buffer[curs.y];
		if (curs.x < by->size()) {
			by->erase(by->begin() + curs.x);
		}
		return curs;
	}

	coord Document::newLine() {
		// TODO:: Split current line if needed
		buffer.insert(buffer.begin() + curs.y + 1, make_shared<vector<int>>(0));
		return this->cursMove(0, curs.y + 1);
	}

	coord Document::cursMove(int x, int y) {
		bool changedY = false;
		// Don't bother doing operations on unchanged coordinates
		if (y != curs.y) {
			changedY = true;
			if (y < 0) {
				curs.y = 0;
			}
			else if (buffer.size() > y) {
				curs.y = y;
			}
			else {
				curs.y = buffer.size() - 1;
			}
		}
		// If y changed, x may have to move
		if (x != curs.x || changedY) {
			auto by = buffer[curs.y];
			if (x < 0) {
				curs.x = 0;
			}
			else if (by->size() >= x) {
				curs.x = x;
			}
			else {
				curs.x = by->size();
			}
		}
		this->eq->fire<coord>(DOC_MOVE, curs);
		return curs;
	}

	coord Document::cursRight(int num) {
		return this->cursMove(curs.x + num, curs.y);
	}

	coord Document::cursRight() {
		return this->cursRight(1);
	}

	coord Document::cursLeft(int num) {
		return this->cursMove(curs.x - num, curs.y);
	}

	coord Document::cursLeft() {
		return this->cursLeft(1);
	}

	coord Document::cursDown(int num) {
		return this->cursMove(curs.x, curs.y + num);
	}

	coord Document::cursDown() {
		return this->cursDown(1);
	}

	coord Document::cursUp(int num) {
		return this->cursMove(curs.x, curs.y - num);
	}

	coord Document::cursUp() {
		return this->cursUp(1);
	}

	coord Document::cursEnd() {
		auto by = buffer[curs.y];
		return this->cursMove(by->size(), curs.y);
	}

	coord Document::cursHome() {
		return this->cursMove(0, curs.y);
	}

	vector<int> Document::readLine(int line) {
		// Copying may not be the way to go, but it is a pretty
		// small vector
		return vector<int>(*buffer[line]);
	}
}