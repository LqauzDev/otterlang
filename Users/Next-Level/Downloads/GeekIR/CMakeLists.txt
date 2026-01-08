cmake_minimum_required(VERSION 3.15)
project(GeekIR VERSION 1.0.0 LANGUAGES C)

# Set C standard
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Find LLVM
find_package(LLVM REQUIRED CONFIG)
message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

# Set LLVM variables
set(LLVM_RUNTIME_OUTPUT_INTDIR ${CMAKE_BINARY_DIR}/bin)
set(LLVM_LIBRARY_OUTPUT_INTDIR ${CMAKE_BINARY_DIR}/lib)
set(LLVM_USE_CRT_DEBUG OFF)

include_directories(${LLVM_INCLUDE_DIRS})
separate_arguments(LLVM_DEFINITIONS_LIST NATIVE_COMMAND ${LLVM_DEFINITIONS})
add_definitions(${LLVM_DEFINITIONS_LIST})

llvm_map_components_to_libnames(llvm_libs
    core
    irreader
    bitreader
    bitwriter
    analysis
    passes
    transformutils
    support
    executionengine
    mc
    nativecodegen
)

# Create the library
add_library(geekir STATIC
    src/context.c
    src/module.c
    src/types.c
    src/values.c
    src/instructions.c
    src/basic_block.c
    src/function.c
    src/builder.c
    src/analysis.c
    src/transforms.c
    src/dumper.c
    src/reader.c
    src/writer.c
    src/utils.c
)

target_include_directories(geekir PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

target_link_libraries(geekir PRIVATE ${llvm_libs})

# Create shared library version
add_library(geekir_shared SHARED
    src/context.c
    src/module.c
    src/types.c
    src/values.c
    src/instructions.c
    src/basic_block.c
    src/function.c
    src/builder.c
    src/analysis.c
    src/transforms.c
    src/dumper.c
    src/reader.c
    src/writer.c
    src/utils.c
)

target_include_directories(geekir_shared PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

target_link_libraries(geekir_shared PRIVATE ${llvm_libs})
set_target_properties(geekir_shared PROPERTIES OUTPUT_NAME geekir)

# Examples
add_subdirectory(examples)

# Tests
enable_testing()
add_subdirectory(tests)

# Installation
install(TARGETS geekir geekir_shared
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
)

install(DIRECTORY include/ DESTINATION include)

# Package configuration
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/GeekIRConfigVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY AnyNewerVersion
)

configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/GeekIRConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/GeekIRConfig.cmake"
    INSTALL_DESTINATION lib/cmake/GeekIR
)

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/GeekIRConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/GeekIRConfigVersion.cmake"
    DESTINATION lib/cmake/GeekIR
)
