#----------------------------------------------------------------------------
# Setup the project
cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
project(MuModel)

#----------------------------------------------------------------------------
# Find Geant4 packag
#
find_package(Geant4 REQUIRED ui_all vis_all)

#----------------------------------------------------------------------------
# Find ROOT packag
#
execute_process(COMMAND root-config --incdir OUTPUT_VARIABLE ROOT_INCLUDE_DIR)
execute_process(COMMAND root-config --nonew --libs COMMAND tr -d \\n OUTPUT_VARIABLE ROOT_LD_DIR)

#----------------------------------------------------------------------------
# Setup Geant4 include directories and compile definitions
#
include(${Geant4_USE_FILE})

# In case we need optimisation flags not set in Geant libraries
#set(CMAKE_CXX_FLAGS "-march=native ${CMAKE_CXX_FLAGS}")

#----------------------------------------------------------------------------
# Setup ROOT include directories
#
include_directories(${ROOT_INCLUDE_DIR})

#----------------------------------------------------------------------------
# Locate sources and headers for this project
#
include_directories(${PROJECT_SOURCE_DIR}/include 
                    ${Geant4_INCLUDE_DIR})
file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)

#----------------------------------------------------------------------------
# Add the executable, and link it to the Geant4 libraries
#
add_executable(MuModel MuModel.cc ${sources} ${headers})
target_link_libraries(MuModel ${Geant4_LIBRARIES} ${ROOT_LD_DIR})

#----------------------------------------------------------------------------
# Install the executable to 'bin' directory under CMAKE_INSTALL_PREFIX
#
install(TARGETS MuModel DESTINATION bin)

