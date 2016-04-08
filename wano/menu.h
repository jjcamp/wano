#pragma once

#include <memory>
#include <vector>
#include "curses_obj.h"
#include "menuitem.h"
#include "document.h"

namespace wano {
	class Menu : public curses::Window {
	public:
		Menu(EventQueue* eq);
		void draw();
		void updatePos(const int ln, const int col);
	private:
		std::vector<MenuItem> items;
		int docx, docy;
		EventQueue* eq;
	};
}