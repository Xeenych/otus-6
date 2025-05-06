cmake_minimum_required(VERSION 3.5)

add_executable(timeit 
    main.cpp
)

set_target_properties(timeit PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
        )
