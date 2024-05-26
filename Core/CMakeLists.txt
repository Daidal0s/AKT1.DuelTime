### Delete after template ###
# Library template word - Core
# Class template word - сore
### Delete after template ###




# Project variables
set(HEADERS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/headers)
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(HEADERS_INLUDES ${HEADERS_DIR}/core.h)

# Source to compile
set(PROJECT_SOURCES
  ${SOURCE_DIR}/core.cpp
)


# Qt wrap
qt_wrap_cpp(PROJECT_SOURCES ${HEADERS_INCLUDES})

# Library
add_library(Core STATIC
  ${PROJECT_SOURCES}
)




# Target configuration
configure_target(Core)

# Library links
target_link_libraries(Core 
  # Some libs
)

# Library includes
target_include_directories(Core PUBLIC ${HEADERS_DIR})

# Static precompiler
target_precompile_headers(Core PRIVATE ${HEADERS_DIR}/stdafx.h)

# Library Definitions
target_compile_definitions(Core PRIVATE Core_LIBRARY)

copy_main_file_to_dir(Core bin)
