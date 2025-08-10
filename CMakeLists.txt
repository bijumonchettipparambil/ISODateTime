cmake_minimum_required(VERSION 3.31)
project(ISODateTime LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Sources
set(ISODateTime_SOURCES
        ISODateTime.cpp
)
set(ISODateTime_HEADERS
        ISODateTime.h
)

# Build the static library
add_library(ISODateTime STATIC ${ISODateTime_SOURCES} ${ISODateTime_HEADERS})

# Public headers are in the project root (so dependents can #include "ISODateTime.h")
target_include_directories(ISODateTime
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

# (Optional) Useful defaults
target_compile_features(ISODateTime PUBLIC cxx_std_17)
set_target_properties(ISODateTime PROPERTIES
        POSITION_INDEPENDENT_CODE ON     # good even for static libs if they might be linked into shared libs
)

# (Optional) Alias target for modern usage
add_library(ISODateTime::ISODateTime ALIAS ISODateTime)
