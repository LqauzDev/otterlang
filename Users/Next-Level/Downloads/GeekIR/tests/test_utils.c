#include "../include/geekir.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

int test_utils(void) {
    // Test version information
    const char* version_string = geekir_get_version_string();
    ASSERT(version_string != NULL, "Version string should not be NULL");
    ASSERT(strlen(version_string) > 0, "Version string should not be empty");
    
    uint32_t major = geekir_get_version_major();
    uint32_t minor = geekir_get_version_minor();
    uint32_t patch = geekir_get_version_patch();
    ASSERT(major == 1, "Major version should be 1");
    ASSERT(minor == 0, "Minor version should be 0");
    ASSERT(patch == 0, "Patch version should be 0");
    
    // Test result to string
    const char* success_string = geekir_result_to_string(GEEKIR_SUCCESS);
    ASSERT(success_string != NULL, "Success result string should not be NULL");
    ASSERT(strcmp(success_string, "Success") == 0, "Success result string should match");
    
    const char* null_pointer_string = geekir_result_to_string(GEEKIR_ERROR_NULL_POINTER);
    ASSERT(null_pointer_string != NULL, "Null pointer result string should not be NULL");
    ASSERT(strcmp(null_pointer_string, "Null pointer error") == 0, "Null pointer result string should match");
    
    const char* invalid_result_string = geekir_result_to_string((GeekIRResult)999);
    ASSERT(invalid_result_string != NULL, "Invalid result string should not be NULL");
    ASSERT(strcmp(invalid_result_string, "Invalid error code") == 0, "Invalid result string should match");
    
    return 1;
}
