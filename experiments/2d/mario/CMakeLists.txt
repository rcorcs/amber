add_executable (mario main.cpp)
file(COPY assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries (mario LINK_PUBLIC Amber)

