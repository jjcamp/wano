include_directories(${CURSES_INCLUDE_DIR} ${Boost_INCLUDE_DIR})

add_executable(wano
    wano.cpp
    document.cpp
    textarea.cpp
    menu.cpp
    rawdocument.cpp
    file.cpp
)

target_link_libraries(wano curses_ui ${CURSES_LIBRARIES} ${PANEL_LIBRARY} ${Boost_LIBRARIES})
