cmake_minimum_required(VERSION 3.20.0)

list(APPEND EXTRA_DTC_OVERLAY_FILE ${CMAKE_CURRENT_SOURCE_DIR}/src/app.overlay)

list(APPEND DTS_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/..) 
find_package(Zephyr REQUIRED)
project(my_zephyr_app)

add_subdirectory(drivers/our_driver)

target_sources(app PRIVATE src/main.cpp)
