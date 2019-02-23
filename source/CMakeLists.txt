# ------------------------------------------------------------------------------
# Initialize the project build with the proper name, making sure, at the lease,
# Cmake v2.6 is used to compile the project source code.
#
cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
project(BNCT)

# ------------------------------------------------------------------------------
# Find the Geant4 package, activating all available UI and VIS drivers by
# default. You can set WITH_GEANT4_UIVIS to OFF via the command line or
# ccmake/cmake-gui to build a batch-mode only executable.
#
option(WITH_GEANT4_UIVIS "Build example with Geant4 UI and Vis drivers" ON)
if(WITH_GEANT4_UIVIS)
  find_package(Geant4 REQUIRED ui_all vis_all)
else()
  find_package(Geant4 REQUIRED)
endif()

# ------------------------------------------------------------------------------
# Point to the Geant4 include directories and compile definitions.
#
include(${Geant4_USE_FILE})

# ------------------------------------------------------------------------------
# Locate the source and header files for this project.
#
include_directories(${PROJECT_SOURCE_DIR}/headers
                    ${Geant4_INCLUDE_DIR})
file(GLOB sources ${PROJECT_SOURCE_DIR}/sources/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/headers/*.hh)

# ------------------------------------------------------------------------------
# Add the project executable to the compilation and link it to the Geant4
# libraries.
#
add_executable(BNCT BNCT.cc ${sources} ${headers})
target_link_libraries(BNCT ${Geant4_LIBRARIES})

# ------------------------------------------------------------------------------
# Copy all the scripts/files to the build directory. This is so we can run the
# executable directly because it relies on these files being in directory the
# executable in ran from.
#
# Note: This assumes Cmake will copy all the scripts of each type.
#
set(BNCT_SCRIPTS
    init.mac
    )

foreach(_script ${BNCT_SCRIPTS})
  configure_file(${PROJECT_SOURCE_DIR}/${_script}
                 ${PROJECT_BINARY_DIR}/${_script}
                 COPYONLY
                 )
endforeach()

# ------------------------------------------------------------------------------
# Add program to the project targets
# (this avoids the need to type the program name after the bash command 'make')
#
add_custom_target(DEPENDS BNCT)

# ------------------------------------------------------------------------------
# Install the executable to the 'bin' directory under CMAKE_INSTALL_PREFIX
#
install(TARGETS BNCT DESTINATION bin)

set(CMAKE_BUILD_TYPE Debug)
