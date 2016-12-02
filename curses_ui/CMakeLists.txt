include_directories(${CURSES_INCLUDE_DIR})

add_library(
    curses_ui
    STATIC
    curses_obj.cpp
    getmodch-nix.cpp
    getmodch-win.cpp
    term-nix.cpp
    panel_obj.cpp
    popup.cpp
    menuitem.cpp
    submenu.cpp
    msgbox.cpp
    colors.cpp
)
