cmake_minimum_required(VERSION 3.16)
project(career_guidance LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(career_lib
    cpp/src/skill.cpp
    cpp/src/person.cpp
    cpp/src/student.cpp
    cpp/src/requirement.cpp
    cpp/src/quiz.cpp
    cpp/src/recommendation.cpp
    cpp/src/guidance_system.cpp
    cpp/src/directions/01_it_direction.cpp
    cpp/src/directions/02_development_direction.cpp
    cpp/src/directions/03_frontend_direction.cpp
    cpp/src/directions/04_backend_direction.cpp
    cpp/src/directions/05_fullstack_direction.cpp
    cpp/src/directions/06_data_direction.cpp
    cpp/src/directions/07_security_direction.cpp
    cpp/src/directions/08_testing_direction.cpp
    cpp/src/directions/09_mobile_direction.cpp
    cpp/src/directions/10_ai_direction.cpp
)

target_include_directories(career_lib PUBLIC cpp/include)

if(MSVC)
    target_compile_options(career_lib PRIVATE /W4)
else()
    target_compile_options(career_lib PRIVATE -Wall -Wextra -Wpedantic)
endif()
