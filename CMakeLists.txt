cmake_minimum_required(VERSION 3.22)
project(wxWidgetsSampleProject)

# Set target directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/bin/)

add_executable(wxWidgetsSampleProject 
    ${CMAKE_CURRENT_LIST_DIR}/src/app.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/mainWindow.cpp
)

target_compile_definitions(wxWidgetsSampleProject PUBLIC
    _FILE_OFFSET_BITS=64 WXUSINGDLL __WXGTK__
)

target_include_directories(wxWidgetsSampleProject PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/deps/wxWidgets/include
    ${CMAKE_CURRENT_LIST_DIR}/deps/wxWidgets/lib/wx/include/gtk3-unicode-3.2
    ${CMAKE_CURRENT_LIST_DIR}/src
)

target_link_libraries(wxWidgetsSampleProject 
    ${CMAKE_CURRENT_LIST_DIR}/deps/wxWidgets/lib/libwx_baseu_net-3.2.so.0
    ${CMAKE_CURRENT_LIST_DIR}/deps/wxWidgets/lib/libwx_baseu-3.2.so.0
    ${CMAKE_CURRENT_LIST_DIR}/deps/wxWidgets/lib/libwx_gtk3u_core-3.2.so.0
)