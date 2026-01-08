#include "../include/geekir.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

int test_module(void) {
    GeekIRContext* context = geekir_context_create();
    ASSERT(context != NULL, "Context creation should succeed");
    
    // Test module creation
    GeekIRModule* module = geekir_module_create(context, "test_module");
    ASSERT(module != NULL, "Module creation should succeed");
    
    // Test module verification (empty module should be valid)
    GeekIRResult result = geekir_module_verify(module);
    ASSERT(result == GEEKIR_SUCCESS, "Empty module verification should succeed");
    
    // Test module dump to string
    char* ir_output = NULL;
    result = geekir_module_dump_to_string(module, &ir_output);
    ASSERT(result == GEEKIR_SUCCESS, "Module dump to string should succeed");
    ASSERT(ir_output != NULL, "IR output should not be NULL");
    ASSERT(strlen(ir_output) > 0, "IR output should not be empty");
    free(ir_output);
    
    // Test module dump to file
    result = geekir_module_dump_to_file(module, "test_module.ll");
    ASSERT(result == GEEKIR_SUCCESS, "Module dump to file should succeed");
    
    // Test bitcode write
    result = geekir_module_write_bitcode(module, "test_module.bc");
    ASSERT(result == GEEKIR_SUCCESS, "Bitcode write should succeed");
    
    // Test bitcode read
    GeekIRModule* read_module = geekir_module_read_bitcode(context, "test_module.bc");
    ASSERT(read_module != NULL, "Bitcode read should succeed");
    
    // Verify read module
    result = geekir_module_verify(read_module);
    ASSERT(result == GEEKIR_SUCCESS, "Read module verification should succeed");
    
    geekir_module_dispose(read_module);
    
    // Test IR parsing
    const char* ir_string = "define i32 @test() {\nret i32 42\n}\n";
    GeekIRModule* parsed_module = geekir_module_parse_ir(context, ir_string);
    ASSERT(parsed_module != NULL, "IR parsing should succeed");
    
    // Verify parsed module
    result = geekir_module_verify(parsed_module);
    ASSERT(result == GEEKIR_SUCCESS, "Parsed module verification should succeed");
    
    geekir_module_dispose(parsed_module);
    
    // Test null pointer handling
    GeekIRModule* null_module = geekir_module_create(NULL, "test");
    ASSERT(null_module == NULL, "Null context should return NULL");
    
    GeekIRModule* null_name_module = geekir_module_create(context, NULL);
    ASSERT(null_name_module == NULL, "Null name should return NULL");
    
    result = geekir_module_verify(NULL);
    ASSERT(result == GEEKIR_ERROR_NULL_POINTER, "Null module verification should return error");
    
    result = geekir_module_dump_to_string(NULL, &ir_output);
    ASSERT(result == GEEKIR_ERROR_NULL_POINTER, "Null module dump to string should return error");
    
    result = geekir_module_dump_to_file(NULL, "test.ll");
    ASSERT(result == GEEKIR_ERROR_NULL_POINTER, "Null module dump to file should return error");
    
    result = geekir_module_write_bitcode(NULL, "test.bc");
    ASSERT(result == GEEKIR_ERROR_NULL_POINTER, "Null module bitcode write should return error");
    
    GeekIRModule* null_read_module = geekir_module_read_bitcode(NULL, "test.bc");
    ASSERT(null_read_module == NULL, "Null context bitcode read should return NULL");
    
    GeekIRModule* null_file_module = geekir_module_read_bitcode(context, NULL);
    ASSERT(null_file_module == NULL, "Null filename bitcode read should return NULL");
    
    GeekIRModule* null_parse_module = geekir_module_parse_ir(NULL, ir_string);
    ASSERT(null_parse_module == NULL, "Null context IR parsing should return NULL");
    
    GeekIRModule* null_string_module = geekir_module_parse_ir(context, NULL);
    ASSERT(null_string_module == NULL, "Null string IR parsing should return NULL");
    
    geekir_module_dispose(module);
    geekir_context_dispose(context);
    
    return 1;
}
