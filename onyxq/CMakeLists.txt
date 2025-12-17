cmake_minimum_required(VERSION 3.10)
project(onyxq VERSION 0.1.0 LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Find liboqs
find_package(PkgConfig REQUIRED)
pkg_check_modules(OQS REQUIRED liboqs)

# Build shared library
add_library(onyxq SHARED
    src/onyxq.c
)

target_include_directories(onyxq PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${OQS_INCLUDE_DIRS}
)

target_link_libraries(onyxq
    ${OQS_LIBRARIES}
)

# Install library
install(TARGETS onyxq
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)

install(FILES include/onyxq.h
    DESTINATION include
)
