#pragma once

#include <memory>
#include <vector>
#include "curses_obj.h"
#include "menuitem.h"
#include "document.h"

namespace wano {
	class Menu : public curses::Window {
	public:
		Menu(shared_ptr<EventQueue> eq);
		void draw();
		void updatePos(int ln, int col);
	private:
		std::vector<MenuItem> items;
		int docx, docy;
		shared_ptr<EventQueue> eq;
	};
}