cmake_minimum_required(VERSION 3.5)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
#set(CMAKE_GENERATOR "Ninja")
#set(CMAKE_GENERATOR "Unix Makefiles" CACHE INTERNAL "" FORCE)


project(otus-6 LANGUAGES CXX)
#add_compile_options(-Werror)
#add_compile_options(-Wall)
#add_compile_options(-Wextra)
#add_compile_options(-Warray-bounds)
#add_compile_options(-Weffc++)

add_executable(otus-6 src/main.cpp)
set_target_properties(otus-6 PROPERTIES CXX_STANDARD 20 CXX_STANDARD_REQUIRED ON)

