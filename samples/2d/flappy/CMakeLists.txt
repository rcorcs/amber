add_executable (flappy main.cpp)
#file(COPY assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries (flappy LINK_PUBLIC Amber)
