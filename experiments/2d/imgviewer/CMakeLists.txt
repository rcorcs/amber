# Add executable called "imgviewer" that is built from the source file
# "main.cpp". The extensions are automatically found.
add_executable (imgviewer main.cpp)

#target_include_directories(imgviewer PUBLIC $(CMAKE_CURRENT_SOURCE_DIR)/include)

# Link the executable to the Amber library. Since the Hello library has
# public include directories we will use those link directories when building
# helloDemo
target_link_libraries (imgviewer LINK_PUBLIC Amber)

