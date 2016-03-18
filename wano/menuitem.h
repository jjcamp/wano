#pragma once

#include <string>
#include <memory>
#include "curses_obj.h"

namespace wano {
	class MenuItem {
	public:
		MenuItem(std::string text);
		void draw(curses::Window* menu);
		std::string text;
	};
}