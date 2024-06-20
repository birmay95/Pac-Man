cmake_minimum_required(VERSION 3.26)
project(Sem_3)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXE_LINKER_FLAGS "-static -static-libgcc")
set(SFML_STATIC_LIBRARIES TRUE)

add_executable(course_work
        course_work/Item.cpp
        course_work/Item.h
        course_work/Map.h
        course_work/Entity.cpp
        course_work/Entity.h
        course_work/PacMan.cpp
        course_work/PacMan.h
        course_work/Map.cpp
        course_work/Ghost.cpp
        course_work/Ghost.h
        course_work/Menu.cpp
        course_work/Menu.h
        course_work/Game.cpp
        course_work/Game.h
        course_work/mainGame.cpp
        course_work/Exception.cpp
        course_work/Exception.h
        course_work/OptionsMenu.cpp
        course_work/OptionsMenu.h
        course_work/Tree.cpp
        course_work/Tree.h
)

set(SFML_DIR "D:\\Sem_3\\lib\\sfml\\GCC 13.1.0 MinGW (SEH) - 64-bit\\SFML-2.6.0\\lib\\cmake\\SFML")

target_link_libraries(course_work sfml-audio sfml-network sfml-graphics sfml-window sfml-system)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML 2.6 REQUIRED COMPONENTS audio network graphics window system)
