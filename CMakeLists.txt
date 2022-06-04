cmake_minimum_required(VERSION 3.22)
project(neunet)

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_EXE_LINKER_FLAGS "-static")

set(LIBS
        core
        )

foreach(LIB IN LISTS LIBS)
    list(APPEND SUB_DIRS "src/${LIB}")
endforeach()

foreach(DIR IN LISTS SUB_DIRS)
    add_subdirectory(${DIR})
endforeach()

add_executable(neunet main.cpp)

target_link_libraries(neunet PUBLIC ${LIBS})

target_include_directories(neunet PUBLIC ${SUB_DIRS})