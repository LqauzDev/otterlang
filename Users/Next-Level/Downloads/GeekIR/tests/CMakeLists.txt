# Tests CMakeLists.txt

# Test framework
add_executable(test_runner test_runner.c)
target_link_libraries(test_runner geekir)

# Individual test files
set(TEST_SOURCES
    test_context.c
    test_module.c
    test_types.c
    test_values.c
    test_function.c
    test_basic_block.c
    test_builder.c
    test_instructions.c
    test_analysis.c
    test_transforms.c
    test_serialization.c
    test_utils.c
)

# Add test sources to the test runner
target_sources(test_runner PRIVATE ${TEST_SOURCES})

# Enable testing
enable_testing()
add_test(NAME GeekIRTests COMMAND test_runner)
