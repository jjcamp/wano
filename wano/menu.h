#pragma once

#include <memory>
#include <vector>
#include <sstream>
#include "../curses_ui/curses_ui.h"
#include "document.h"
#include "commonfunctions.h"

namespace wano {
	class Menu {
	public:
		Menu();
		const curses::Window& getWindow();
		void draw();
		void updatePos(const int ln, const int col);
		void focus(int ch);
	private:
		typedef struct { std::string label; char hotkey; curses_ui::Submenu submenu; } sub;

		std::vector<sub> items;
		int docx, docy;
		curses::Panel win;
	};
}