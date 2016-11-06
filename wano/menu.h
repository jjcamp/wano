#pragma once

#include <memory>
#include <vector>
#include "../curses_ui/curses_obj.h"
#include "menuitem.h"
#include "document.h"

namespace wano {
	class Menu {
	public:
		Menu(EventQueue* eq);
		const curses::Window& getWindow();
		void draw();
		void updatePos(const int ln, const int col);
	private:
		std::vector<MenuItem> items;
		int docx, docy;
		EventQueue* eq;
		curses::Window win;
	};
}