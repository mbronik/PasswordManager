cmake_minimum_required(VERSION 3.21)
project(PasswordManager)

set(CMAKE_CXX_STANDARD 17)

add_executable(PasswordManager main.cpp MainMenu.cpp MainMenu.h Password.cpp Password.h PasswordManager.cpp PasswordManager.h Category.cpp Category.h Logic.cpp Logic.h)
