cmake_minimum_required(VERSION 3.14)
project(tinkoff21-22)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -pedantic -Wfloat-equal -Wconversion -Wlogical-op -Wshift-overflow=2 -fsanitize=address -fsanitize=undefined -fno-sanitize-recover -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC -DONPC")