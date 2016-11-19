Wano
====
Wano aims to be a portable nano clone that uses the familiar windows-like shortcuts.

Building
--------
Wano has been built with VS2015, Clang 3.4, and GCC 5.4 but should be able to be built with any compiler that supports C++14.

**Dependencies:**
- Boost::filesystem (until C++17 STL support is more widespread)
- curses (ncurses or pdcurses, depending on platform)

On Windows, you can use [vcpkg](https://github.com/Microsoft/vcpkg) to grab the dependencies, but pdcurses must be built statically and moved into the /lib folder.

Both a VS solution file and CMake files are included.

Major TODOs
-----------
* Add functionality to menus (and shortcuts)
* Implement saving and loading
