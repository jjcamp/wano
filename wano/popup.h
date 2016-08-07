#pragma once
#include <vector>
#include <string>
#include "curses_obj.h"

namespace wano {
	class Popup {
	public:
		Popup(const int begX, const int begY, const int width, const int height, std::vector<std::string>&& lines);
		static Popup create(const int begX, const int begY, std::vector<std::string>&& lines);
		void draw();
	private:
		curses::Window win;
		std::vector<std::string> lines;
	};
}
