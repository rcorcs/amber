
add_executable (fruits main.cpp)

file(COPY assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

target_link_libraries(fruits LINK_PUBLIC Amber)

