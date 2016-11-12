#include "panel_obj.h"

using namespace std;

namespace curses {
	// Uses the userptr supplied by the panel library to store a reference
	// to the wrapper class.

	Panel::Panel(WINDOW* win) :
		Window(win),
		pan(new_panel(win), del_panel) {
		set_panel_userptr(pan.get(), this);
	}

	Panel::Panel(const int nlines, const int ncols, const int begin_y, const int begin_x) :
		Window(nlines, ncols, begin_y, begin_x),
		pan(new_panel(this->win.get()), del_panel) {
		set_panel_userptr(pan.get(), this);
	}

	const Panel& Panel::above() const {
		return *(static_cast<const Panel*>(panel_userptr(panel_above(pan.get()))));
	}

	const Panel& Panel::below() const {
		return *(static_cast<const Panel*>(panel_userptr(panel_below(pan.get()))));
	}
	
	void Panel::movepanel(const int start_y, const int start_x) {
		if (move_panel(pan.get(), start_y, start_x) == ERR)
			throw CursesException();
	}
	
	void Panel::top() {
		if (top_panel(pan.get()) == ERR)
			throw CursesException();
	}

	void Panel::bottom() {
		if (bottom_panel(pan.get()) == ERR)
			throw CursesException();
	}

	void Panel::hide() {
		if (hide_panel(pan.get()) == ERR)
			throw CursesException();
	}

	void Panel::show() {
		if (show_panel(pan.get()) == ERR)
			throw CursesException();
	}

	bool Panel::hidden() const {
		if (panel_hidden(pan.get()) == OK)
			return true;
		return false;
	}

	void Panel::update() {
		update_panels();
	}

	const Panel& Panel::topmost() {
		return *(static_cast<const Panel*>(panel_userptr(panel_above(nullptr))));
	}

	const Panel& Panel::bottommost() {
		return *(static_cast<const Panel*>(panel_userptr(panel_below(nullptr))));
	}
}