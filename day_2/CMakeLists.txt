# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.

cmake_minimum_required(VERSION 3.30)
project(day_2)

set(CMAKE_CXX_STANDARD 20)

add_executable(day_2 main.cpp
        NumberComperator.cpp
        NumberComperator.hpp)