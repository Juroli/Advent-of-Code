# CMakeList.txt : CMake project for AoC_Solver_Engine, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (AoC_Solver_Engine "src/AoC_Solver_Engine.cpp" "src/AoC_Solver_Engine.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET AoC_Solver_Engine PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
