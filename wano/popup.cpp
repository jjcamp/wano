#include "popup.h"

using namespace std;
using namespace curses;

namespace wano {
	Popup::Popup(const int begX, const int begY, const int width, const int height, vector<string>&& lines) :
		lines(lines),
		win(height + 2, width + 2, begY, begX) {}

	Popup Popup::create(const int begX, const int begY, vector<string>&& lines) {
		size_t width = 0;
		for (const auto& s : lines) {
			auto l = s.length();
			if (l > width) width = l;
		}
		return Popup(begX, begY, width, lines.size(), move(lines));
	}

	void Popup::draw() {
		win.attrOn(Color::Pair(1));
		for (auto i = 0; i != lines.size(); ++i) {
			win.move(i + 1, 1);
			win.clrToEOL();
			win.addStr(lines[i].c_str());
		}
		win.border(0, 0, 0, 0, 0, 0, 0, 0);
		win.attrOff(Color::Pair(1));
		win.refresh();
	}
}