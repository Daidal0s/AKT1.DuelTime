# Project variables
set(HEADERS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/headers)
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)




# Project files
set(APP_SOURCE
    ${SOURCE_DIR}/main.cpp
    ${SOURCE_DIR}/mainwindow.cpp
    ${SOURCE_DIR}/mainwindow.ui
)

# Project headers
set(APP_HEADERS
    ${HEADERS_DIR}/mainwindow.h
)




# Project sources
set(PROJECT_SOURCES
    ${APP_HEADERS}
    ${APP_SOURCE}
)




# Default Qt build
if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(PLACEHOLDER
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(PLACEHOLDER SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(PLACEHOLDER
            ${PROJECT_SOURCES}
        )
    endif()
endif()

# Configure Project
configure_target(PLACEHOLDER)

target_link_libraries(PLACEHOLDER
    PUBLIC Core
    PRIVATE Qt${QT_VERSION_MAJOR}::Widgets
)

# Including headers
target_include_directories(PLACEHOLDER PUBLIC ${HEADERS_DIR})

# Precompiled headers for Qt App
target_precompile_headers(PLACEHOLDER PRIVATE ${HEADERS_DIR}/stdafx.h)

if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.PLACEHOLDER)
endif()

set_target_properties(PLACEHOLDER PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS PLACEHOLDER
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(PLACEHOLDER)
endif()

copy_main_file_to_dir(PLACEHOLDER bin)
