#include "../include/geekir.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

int test_context(void) {
    // Test context creation
    GeekIRContext* context = geekir_context_create();
    ASSERT(context != NULL, "Context creation should succeed");
    
    // Test context disposal
    geekir_context_dispose(context);
    
    // Test null context disposal (should not crash)
    geekir_context_dispose(NULL);
    
    // Test context operations
    context = geekir_context_create();
    ASSERT(context != NULL, "Context creation should succeed");
    
    GeekIRResult result = geekir_context_set_target_triple(context, "x86_64-unknown-linux-gnu");
    ASSERT(result == GEEKIR_SUCCESS, "Setting target triple should succeed");
    
    result = geekir_context_set_data_layout(context, "e-m:e-i64:64-f80:128-n8:16:32:64-S128");
    ASSERT(result == GEEKIR_SUCCESS, "Setting data layout should succeed");
    
    // Test null pointer handling
    result = geekir_context_set_target_triple(NULL, "test");
    ASSERT(result == GEEKIR_ERROR_NULL_POINTER, "Null context should return error");
    
    result = geekir_context_set_data_layout(NULL, "test");
    ASSERT(result == GEEKIR_ERROR_NULL_POINTER, "Null context should return error");
    
    geekir_context_dispose(context);
    
    return 1;
}
