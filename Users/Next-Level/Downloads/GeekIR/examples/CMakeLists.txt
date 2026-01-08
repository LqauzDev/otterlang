# Examples CMakeLists.txt

# Example 1: Basic IR creation
add_executable(basic_example basic_example.c)
target_link_libraries(basic_example geekir)

# Example 2: Function creation and manipulation
add_executable(function_example function_example.c)
target_link_libraries(function_example geekir)

# Example 3: Optimization passes
add_executable(optimization_example optimization_example.c)
target_link_libraries(optimization_example geekir)

# Example 4: IR parsing and serialization
add_executable(serialization_example serialization_example.c)
target_link_libraries(serialization_example geekir)

# Example 5: Advanced control flow
add_executable(control_flow_example control_flow_example.c)
target_link_libraries(control_flow_example geekir)
