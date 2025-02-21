cmake_minimum_required(VERSION 3.28)

project(world)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(fmt CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
find_package(unofficial-uwebsockets CONFIG REQUIRED)

add_executable(world 
    "server/main.cpp"
    "server/world/world.cpp")

target_include_directories(world PRIVATE "server")
target_link_libraries(world PRIVATE 
    fmt::fmt 
    nlohmann_json::nlohmann_json 
    unofficial::uwebsockets::uwebsockets)

add_executable(test server/test.cpp)
target_include_directories(test PRIVATE "server")
target_link_libraries(test PRIVATE 
    fmt::fmt 
    nlohmann_json::nlohmann_json 
    unofficial::uwebsockets::uwebsockets)