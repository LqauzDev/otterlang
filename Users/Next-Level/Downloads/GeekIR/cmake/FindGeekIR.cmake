# FindGeekIR.cmake - Find GeekIR library
# This can be used to find GeekIR in other projects

# Find the header
find_path(GEEKIR_INCLUDE_DIR
    NAMES geekir.h
    PATHS
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/geekir
        /usr/local/include
        /usr/include
    DOC "GeekIR header directory"
)

# Check if header was found
if(GEEKIR_INCLUDE_DIR)
    # Verify the header exists and is readable
    if(EXISTS "${GEEKIR_INCLUDE_DIR}/geekir.h")
        set(GEEKIR_FOUND TRUE)
        message(STATUS "Found GeekIR header: ${GEEKIR_INCLUDE_DIR}/geekir.h")
    else()
        set(GEEKIR_FOUND FALSE)
        message(WARNING "GeekIR header not found")
    endif()
else()
    set(GEEKIR_FOUND FALSE)
    message(WARNING "GeekIR include directory not found")
endif()

# Create imported target
if(GEEKIR_FOUND AND NOT TARGET GeekIR::GeekIR)
    add_library(GeekIR::GeekIR INTERFACE IMPORTED)
    
    # Set include directories
    set_target_properties(GeekIR::GeekIR PROPERTIES
        INTERFACE_INCLUDE_DIRECTORIES "${GEEKIR_INCLUDE_DIR}"
    )
    
    # Note: User needs to link LLVM libraries separately
    # This is intentional since GeekIR is header-only
endif()

# Variables for backward compatibility
set(GEEKIR_INCLUDE_DIRS ${GEEKIR_INCLUDE_DIR})

# Handle find_package arguments
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(GeekIR
    REQUIRED_VARS GEEKIR_INCLUDE_DIR
    VERSION_VAR GEEKIR_VERSION
)

mark_as_advanced(GEEKIR_INCLUDE_DIR)
