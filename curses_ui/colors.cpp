#include "colors.h"

using namespace std;
using namespace curses;

namespace curses_ui {
	Colors Colors::instance;

    void Colors::add(const string& key, short foreground, short background) {
        if (this->exists(key))
            throw ColorsException();
        auto existing = this->findIndex(foreground, background);
        if (existing != -1) {
            auto res = this->color_map.emplace(key, existing);
            if (res.second == false)
                throw ColorsException();
        }
        else {
            if (this->next_index == COLOR_PAIRS)
                throw ColorsException();
            auto res = this->color_map.emplace(key, this->next_index);
            if (res.second == false)
                throw ColorsException();
            Color::InitPair(this->next_index, foreground, background);
            this->next_index++;
        }
    }

	void Colors::addIfMissing(const string& key, short foreground, short background) {
		if (this->exists(key))
			return;
		this->add(key, foreground, background);
	}

    void Colors::set(Window& win, const string& key) const {
        auto cp = this->find(key);
        win.attrOn(Color::Pair(cp));
    }

    void Colors::unset(Window& win, const string& key) const {
        auto cp = this->find(key);
        win.attrOff(Color::Pair(cp));
    }

    bool Colors::exists(const string& key) const {
        return this->color_map.find(key) != color_map.end();
    }

    short Colors::find(const string& key) const {
        auto it = color_map.find(key);
        if (it == color_map.end())
            throw ColorsException();
        return it->second;
    }

    short Colors::findIndex(short foreground, short background) const {
        short fg, bg;
        for (short i = 1; i < this->next_index; i++) {
			Color::PairContent(i, &fg, &bg);
            if (fg == foreground && bg == background)
                return i;
        }
        return -1;
    }
}