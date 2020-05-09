add_executable (character main.cpp)
file(COPY assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries (character LINK_PUBLIC Amber)

