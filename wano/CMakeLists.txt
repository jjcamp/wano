include_directories(${CURSES_INCLUDE_DIR})

add_executable(wano
    wano.cpp
    curses_obj.cpp
    document.cpp
    textarea.cpp
    popup.cpp
    menuitem.cpp
    menu.cpp
    getmodch-win.cpp
    getmodch-nix.cpp
)

target_link_libraries(wano ${CURSES_LIBRARIES})
