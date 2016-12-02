#pragma once

#include <string>
#include <unordered_map>
#include <limits>
#include "curses_obj.h"

namespace curses_ui {
    struct ColorsException : public std::exception {
		const char* what() const throw() {
			return "Colors Exception";
		}
	};

    class Colors {
    public:
        void add(const std::string& key, short foreground, short background);
		void addIfMissing(const std::string& key, short foreground, short background);
        void set(curses::Window& win, const std::string& key) const;
        void unset(curses::Window& win, const std::string& key) const;
        bool exists(const std::string& key) const;
		static Colors instance;
    private:
        short find(const std::string& key) const;
        short findIndex(short foreground, short background) const;
        std::unordered_map<std::string, short> color_map;
        short next_index = 1;
    };
}