#include "document.h"

using namespace std;

namespace wano {
	Document::Document() :
		buffer(),
		curs{ 0, 0 }
	{}

	Document::Document(istream& stream) :
		buffer(stream),
		curs{ 0, 0 }
	{}

	coord Document::insCh(int ch) {
		auto& by = buffer[curs.y];
		by.insert(by.begin() + curs.x, ch);
		return this->cursRight();
	}

	coord Document::delCh() {
		auto& by = buffer[curs.y];
		if (curs.x < by.size())
			by.erase(by.begin() + curs.x);
		else if (curs.y < buffer.size() - 1) {
			by += buffer[curs.y + 1];
			buffer.erase(buffer.cbegin() + curs.y + 1);
		}
		return curs;
	}

	coord Document::newLine() {
		auto& by = buffer[curs.y];
		if (curs.x == by.size())
			buffer.emplace(buffer.begin() + curs.y + 1, "");
		else {
			auto mvStr = by.substr(curs.x);
			by.erase(curs.x);
			buffer.emplace(buffer.begin() + curs.y + 1, mvStr);
		}
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

	coord Document::insStr(const string&& str) {
		auto& by = buffer[curs.y];
		by.insert(curs.x, str);
		return this->cursRight(str.length());
	}

	const string& Document::readLine(int line) const {
		return buffer[line];
	}

	void Document::write(ostream& stream) {
		buffer.write(stream);
	}

	Document Document::fromString(string str) {
		auto stream = istringstream(str);
		return Document(stream);
	}
}