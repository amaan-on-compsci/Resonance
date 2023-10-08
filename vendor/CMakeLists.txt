cmake_minimum_required(VERSION 3.5)
project(displayWaveform)

#wxWidgets flags
set(wxBUILD_SHARED OFF)
add_subdirectory(wxWidgets)

#Audio File Flags
set(BUILD_TESTS OFF)
set(BUILD_EXAMPLES OFF)
add_subdirectory(AudioFile)

add_library(vendor INTERFACE)
target_sources(vendor 
    INTERFACE 
        ${CMAKE_CURRENT_SOURCE_DIR}/AudioFile/AudioFile.h
    )

 target_link_libraries(vendor 
    INTERFACE 
        wx::net 
        wx::core
        wx::base
    )