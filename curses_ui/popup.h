#pragma once

#include <functional>
#include "panel_obj.h"

namespace curses_ui {
	class Popup {
	public:
		struct Result {	// using a struct as an enum to allow easily extensible result types
			static constexpr int CONTINUE = -1;
			static constexpr int EXIT = 0;
			static constexpr int OKAY = 1;
		};

		Popup(const int nlines, const int ncols, const int begin_y, const int begin_x);
		virtual int show();
		int show(std::function<int(int)> innerLoop);

	protected:
		curses::Panel panel;
		curses::Cursor beforeShow();
		void afterShow(curses::Cursor prevCursor);
	};
}