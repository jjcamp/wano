#pragma once

#include <memory>
#include "curses_obj.h"
#include "panel.h"

namespace curses {
	class Panel : public Window {
	public:
		Panel(const int nlines, const int ncols, const int begin_y, const int begin_x);
		Panel(WINDOW* win);

		const Panel& above() const;
		const Panel& below() const;
		void movepanel(const int start_y, const int start_x);  // move_panel
		void top();
		void bottom();
		void hide();
		void show();
		bool hidden() const;

		static void update();
		static const Panel& topmost();	// panel_above(nullptr)
		static const Panel& bottommost();	// panel_below(nullptr)

	protected:
		std::unique_ptr<PANEL, int(*)(PANEL*)> pan;
	};
}