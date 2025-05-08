cmake_minimum_required(VERSION 3.21)
project(cnn_cpp_slint)

find_package(Slint REQUIRED)

# 🔧 Kaynakları doğrudan burada veriyoruz
add_executable(cnn_cpp_slint
    main.cpp
)

# 🔧 Slint arayüz dosyasını ayrıca ekle
slint_target_sources(cnn_cpp_slint
    ui/main_window.slint
)
