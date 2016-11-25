#pragma once

#include <vector>
#include <functional>
#include "commonfunctions.h"

namespace wano {
	struct Hotkey {
		char key;
		std::function<void()> func;

		void operator()() {
			func();
		}
	};

	class Hotkeys {
	private:
		std::vector<Hotkey> hotkeys;

	public:
		void add(Hotkey hk) {
			hotkeys.emplace_back(hk);
		}

		void handleCh(int ch) {
			for (auto& hk : hotkeys) {
				if (hk.key == ch) {
					hk();
					break;
				}
			}
		}

		static Hotkeys defaults() {
			auto hotkeys = Hotkeys();
			hotkeys.add(Hotkey{ 's', functions::saveCurrentDocument });
			return hotkeys;
		}
	};
}