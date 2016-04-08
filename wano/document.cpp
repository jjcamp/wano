#include "document.h"

using namespace std;

namespace wano {
	Document::Document(EventQueue* eq) :
		buffer(),
		eq{ eq },
		curs { 0, 0 }
	{
		buffer.emplace_back("");
	}

	coord Document::insCh(int ch) {
		auto& by = buffer[curs.y];
		by.insert(by.begin() + curs.x, ch);
		return this->cursRight();
	}

	coord Document::delCh() {
		auto& by = buffer[curs.y];
		if (curs.x < by.size()) {
			by.erase(by.begin() + curs.x);
		}
		return curs;
	}

	coord Document::newLine() {
		// TODO:: Split current line if needed
		buffer.emplace(buffer.begin() + curs.y + 1, "");
		return this->cursMove(0, curs.y + 1);
	}

	coord Document::cursMove(int x, int y) {
		auto changedY = false;
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
			else if (by.size() >= x) {
				curs.x = x;
			}
			else {
				curs.x = by.size();
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
		return this->cursMove(by.size(), curs.y);
	}

	coord Document::cursHome() {
		return this->cursMove(0, curs.y);
	}

	const string& Document::readLine(int line) const {
		return buffer[line];
	}
}
