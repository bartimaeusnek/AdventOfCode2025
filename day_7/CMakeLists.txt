# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.

cmake_minimum_required(VERSION 4.0)
project(day_7)

set(CMAKE_CXX_STANDARD 20)

add_executable(day_7 main.cpp Position.h Board.cpp Board.hpp Cell.hpp Cell.cpp CellType.hpp)