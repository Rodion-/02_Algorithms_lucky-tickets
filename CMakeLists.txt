cmake_minimum_required(VERSION 3.16)

project(algo2 VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "-Wall -pthread")

configure_file(TutorialConfig.h.in TutorialConfig.h)



add_executable(algo2 main.cpp )

#target_compile_features(thread cxx_std_17)


target_include_directories(algo2 PUBLIC
                           "${PROJECT_BINARY_DIR}"
                           )

target_link_libraries(algo2 -lX11 -lGLU -lGL)
                           	  
install(TARGETS algo2 DESTINATION bin)
install(FILES "${PROJECT_BINARY_DIR}/TutorialConfig.h"
  DESTINATION include
  )
