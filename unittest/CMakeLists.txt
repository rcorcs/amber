add_executable (UnitTests ArrayTest.cpp VectorTest.cpp UnitTests.cpp)
target_link_libraries (UnitTests LINK_PUBLIC Amber)

add_custom_command(TARGET UnitTests
    # Run after all other rules within the target have been executed
    POST_BUILD
    COMMAND ./UnitTests
    COMMENT "This command will be executed after building bar"
    VERBATIM
)

