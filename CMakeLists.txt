cmake_minimum_required(VERSION 3.21)
project(cnn_cpp_slint)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Slint'in kurulu olduğu yeri belirt
find_package(Slint REQUIRED)

add_executable(cnn_cpp_slint
    main.cpp
)
slint_target_sources(cnn_cpp_slint
    ui/main_window.slint
)


# Slint'i linkle
target_link_libraries(cnn_cpp_slint PRIVATE Slint::Slint)
