#include "../include/geekir.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

int test_serialization(void) {
    GeekIRContext* context = geekir_context_create();
    ASSERT(context != NULL, "Context creation should succeed");
    
    GeekIRModule* module = geekir_module_create(context, "test_module");
    ASSERT(module != NULL, "Module creation should succeed");
    
    // Create a simple function
    GeekIRType* int32_type = geekir_type_get_int32(context);
    GeekIRType* void_type = geekir_type_get_void(context);
    GeekIRType* function_type = geekir_type_get_function(int32_type, &int32_type, 1, false);
    
    GeekIRFunction* function = geekir_function_create(module, function_type, "test_function");
    GeekIRBasicBlock* entry_block = geekir_function_append_basic_block(function, "entry");
    
    GeekIRBuilder* builder = geekir_builder_create(context);
    geekir_builder_set_position(builder, entry_block);
    
    GeekIRValue* param = geekir_function_get_param(function, 0);
    GeekIRValue* const_42 = geekir_value_get_const_int(int32_type, 42, false);
    GeekIRInstruction* add_instr = geekir_builder_add(builder, param, const_42, "result");
    geekir_builder_ret(builder, (GeekIRValue*)add_instr);
    
    // Test module dump to string
    char* ir_output = NULL;
    GeekIRResult result = geekir_module_dump_to_string(module, &ir_output);
    ASSERT(result == GEEKIR_SUCCESS, "Module dump to string should succeed");
    ASSERT(ir_output != NULL, "IR output should not be NULL");
    ASSERT(strlen(ir_output) > 0, "IR output should not be empty");
    
    // Test module dump to file
    result = geekir_module_dump_to_file(module, "test_serialization.ll");
    ASSERT(result == GEEKIR_SUCCESS, "Module dump to file should succeed");
    
    // Test bitcode write
    result = geekir_module_write_bitcode(module, "test_serialization.bc");
    ASSERT(result == GEEKIR_SUCCESS, "Bitcode write should succeed");
    
    // Test bitcode read
    GeekIRModule* read_module = geekir_module_read_bitcode(context, "test_serialization.bc");
    ASSERT(read_module != NULL, "Bitcode read should succeed");
    
    // Verify read module
    result = geekir_module_verify(read_module);
    ASSERT(result == GEEKIR_SUCCESS, "Read module verification should succeed");
    
    // Test IR parsing
    GeekIRModule* parsed_module = geekir_module_parse_ir(context, ir_output);
    ASSERT(parsed_module != NULL, "IR parsing should succeed");
    
    // Verify parsed module
    result = geekir_module_verify(parsed_module);
    ASSERT(result == GEEKIR_SUCCESS, "Parsed module verification should succeed");
    
    // Test round-trip serialization
    char* roundtrip_ir = NULL;
    result = geekir_module_dump_to_string(parsed_module, &roundtrip_ir);
    ASSERT(result == GEEKIR_SUCCESS, "Round-trip dump to string should succeed");
    ASSERT(roundtrip_ir != NULL, "Round-trip IR should not be NULL");
    ASSERT(strlen(roundtrip_ir) > 0, "Round-trip IR should not be empty");
    
    // Compare original and round-trip IR (they should be semantically equivalent)
    // Note: The exact string might differ due to formatting, but the structure should be the same
    ASSERT(strstr(roundtrip_ir, "test_function") != NULL, "Round-trip IR should contain function name");
    ASSERT(strstr(roundtrip_ir, "add") != NULL, "Round-trip IR should contain add instruction");
    
    // Test round-trip bitcode
    result = geekir_module_write_bitcode(parsed_module, "test_serialization_roundtrip.bc");
    ASSERT(result == GEEKIR_SUCCESS, "Round-trip bitcode write should succeed");
    
    GeekIRModule* roundtrip_module = geekir_module_read_bitcode(context, "test_serialization_roundtrip.bc");
    ASSERT(roundtrip_module != NULL, "Round-trip bitcode read should succeed");
    
    result = geekir_module_verify(roundtrip_module);
    ASSERT(result == GEEKIR_SUCCESS, "Round-trip module verification should succeed");
    
    // Test null pointer handling
    GeekIRResult null_result = geekir_module_dump_to_string(NULL, &ir_output);
    ASSERT(null_result == GEEKIR_ERROR_NULL_POINTER, "Null module dump to string should return error");
    
    null_result = geekir_module_dump_to_string(module, NULL);
    ASSERT(null_result == GEEKIR_ERROR_NULL_POINTER, "Null output pointer should return error");
    
    null_result = geekir_module_dump_to_file(NULL, "test.ll");
    ASSERT(null_result == GEEKIR_ERROR_NULL_POINTER, "Null module dump to file should return error");
    
    null_result = geekir_module_dump_to_file(module, NULL);
    ASSERT(null_result == GEEKIR_ERROR_NULL_POINTER, "Null filename should return error");
    
    null_result = geekir_module_write_bitcode(NULL, "test.bc");
    ASSERT(null_result == GEEKIR_ERROR_NULL_POINTER, "Null module bitcode write should return error");
    
    null_result = geekir_module_write_bitcode(module, NULL);
    ASSERT(null_result == GEEKIR_ERROR_NULL_POINTER, "Null filename bitcode write should return error");
    
    GeekIRModule* null_read_module = geekir_module_read_bitcode(NULL, "test.bc");
    ASSERT(null_read_module == NULL, "Null context bitcode read should return NULL");
    
    GeekIRModule* null_file_module = geekir_module_read_bitcode(context, NULL);
    ASSERT(null_file_module == NULL, "Null filename bitcode read should return NULL");
    
    GeekIRModule* null_parse_module = geekir_module_parse_ir(NULL, ir_output);
    ASSERT(null_parse_module == NULL, "Null context IR parsing should return NULL");
    
    GeekIRModule* null_string_module = geekir_module_parse_ir(context, NULL);
    ASSERT(null_string_module == NULL, "Null string IR parsing should return NULL");
    
    // Cleanup
    free(ir_output);
    free(roundtrip_ir);
    
    geekir_builder_dispose(builder);
    geekir_module_dispose(roundtrip_module);
    geekir_module_dispose(parsed_module);
    geekir_module_dispose(read_module);
    geekir_module_dispose(module);
    geekir_context_dispose(context);
    
    return 1;
}
