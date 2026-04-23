cmake_minimum_required(VERSION 3.16)

# Project name and settings
project(practiceVP1 VERSION 0.1 LANGUAGES CXX)

# Enable Qt-specific options
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find Qt and required modules
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Network) # Added Network module
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Core Gui Network) # Added Network module

# --- START OF FONT RESOURCE ADDITION ---
set(MY_RESOURCES
    myresources.qrc # Name of your resources file
)

# Create the myresources.qrc file if it doesn't exist
if(NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${MY_RESOURCES})
    file(WRITE ${CMAKE_CURRENT_SOURCE_DIR}/${MY_RESOURCES} "<RCC>\n</RCC>")
endif()

# Add the font entry (assuming shooting_star.ttf is in the same directory)
file(APPEND ${CMAKE_CURRENT_SOURCE_DIR}/${MY_RESOURCES} "
    <qresource prefix=\"/fonts\">
        <file>shooting_star.ttf</file>
    </qresource>
")

qt_add_resources(practiceVP1 ${MY_RESOURCES}) # Use your project's target name here
# --- END OF FONT RESOURCE ADDITION ---

# Specify the location of zlib
set(ZLIB_DIR "C:/Users/erha/Downloads/zlib131/zlib-1.3.1") # Set your zlib path here

# Include zlib headers and link directories
include_directories(${ZLIB_DIR}/include)
link_directories(${ZLIB_DIR}/lib)

# Specify the project sources
set(PROJECT_SOURCES
    main.cpp
    compressanddecompress.h
    compressanddecompress.cpp
    compressanddecompress.ui
    resources.qrc #This line is no longer needed if you create resources.qrc using cmake
    compress.h
    compress.cpp
)

# Create the executable
if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(practiceVP1
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        mainwindow.h mainwindow.cpp mainwindow.ui
        encryptionanddecryption.h encryptionanddecryption.cpp encryptionanddecryption.ui
        encryption.h encryption.cpp
    )
else()
    add_executable(practiceVP1
        ${PROJECT_SOURCES}
    )
endif()

# Link the Qt libraries
target_link_libraries(practiceVP1 PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Network) # Added Network module linking

# Link zlibstatic for compression
target_link_libraries(practiceVP1 PRIVATE "C:/Users/erha/Downloads/zlib131/zlib-1.3.1/build/libzlibstatic.a")

# Link Vulkan if found (optional)
if(Vulkan_FOUND)
    target_link_libraries(practiceVP1 PRIVATE Vulkan::Vulkan)
endif()

# If on Windows, link winhttp
if(WIN32)
    target_link_libraries(practiceVP1 PRIVATE winhttp)
    target_compile_definitions(practiceVP1 PRIVATE _WIN32_WINNT=0x0601 WIN32_LEAN_AND_MEAN NOMINMAX)
endif()

# Set application properties
set_target_properties(practiceVP1 PROPERTIES
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

# Define installation paths
include(GNUInstallDirs)
install(TARGETS practiceVP1
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# Finalize executable for Qt 6
if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(practiceVP1)
endif()
