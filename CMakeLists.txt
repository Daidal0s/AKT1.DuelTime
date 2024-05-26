### Delete after template ###
# Project template word - PLACEHOLDER
# Library template word - Core
# Don't forget to rename folders~
### Delete after template ###

cmake_minimum_required(VERSION 3.5)

project(PLACEHOLDER VERSION 0.1 LANGUAGES CXX)

# Default Qt veriables
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# Project variables
set(ENABLE_TESTING "Enables testing mode" ON)
set(BUILD_PATH ${CMAKE_CURRENT_BINARY_DIR}/build)




# Compiler features
add_library(COMPILER_FEATURES INTERFACE)
target_compile_features(COMPILER_FEATURES 
  INTERFACE cxx_std_17
)

# Function for fast configuring
function(configure_target configureTarget)
  target_link_libraries(${configureTarget} 
    PRIVATE COMPILER_FEATURES
    PRIVATE Qt${QT_VERSION_MAJOR}::Core
  )
endfunction(configure_target)

# Function to fast copy build files
function(copy_main_file_to_dir target dir)
    add_custom_command(
        TARGET ${target} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
            "$<TARGET_FILE:${target}>"
            "${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/${dir}/$<TARGET_FILE_NAME:${target}>"
    )
endfunction(copy_main_file_to_dir)




# Packages to be found
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)




# Subdirs
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Core)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/PLACEHOLDER)




# CTest
if(ENABLE_TESTING)
  include(CTest)
endif()

# Test subdirs
if(ENABLE_TESTING)
  add_subdirectory(external)
  add_subdirectory(tests)
endif()
