#include "../include/geekir.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    printf("=== GeekIR Serialization Example ===\n\n");
    
    // Create original module
    GeekIRContext* context = geekir_context_create();
    GeekIRModule* original_module = geekir_module_create(context, "original_module");
    
    if (!context || !original_module) {
        printf("Failed to create context or module\n");
        return 1;
    }
    
    // Create a simple function in the original module
    GeekIRType* int32_type = geekir_type_get_int32(context);
    GeekIRType* void_type = geekir_type_get_void(context);
    GeekIRType* function_type = geekir_type_get_function(int32_type, &int32_type, 1, false);
    
    GeekIRFunction* function = geekir_function_create(original_module, function_type, "add_one");
    GeekIRBasicBlock* entry = geekir_function_append_basic_block(function, "entry");
    
    GeekIRBuilder* builder = geekir_builder_create(context);
    geekir_builder_set_position(builder, entry);
    
    GeekIRValue* param = geekir_function_get_param(function, 0);
    GeekIRValue* const_1 = geekir_value_get_const_int(int32_type, 1, false);
    GeekIRInstruction* result = geekir_builder_add(builder, param, const_1, "result");
    geekir_builder_ret(builder, (GeekIRValue*)result);
    
    printf("Original module created successfully.\n");
    
    // Serialize to bitcode
    GeekIRResult result_code = geekir_module_write_bitcode(original_module, "test_module.bc");
    if (result_code != GEEKIR_SUCCESS) {
        printf("Failed to write bitcode: %s\n", geekir_result_to_string(result_code));
        return 1;
    }
    printf("Module serialized to test_module.bc\n");
    
    // Serialize to IR string
    char* ir_string = NULL;
    result_code = geekir_module_dump_to_string(original_module, &ir_string);
    if (result_code != GEEKIR_SUCCESS) {
        printf("Failed to dump IR to string: %s\n", geekir_result_to_string(result_code));
        return 1;
    }
    printf("IR string generated (length: %zu)\n", strlen(ir_string));
    
    // Save IR to file
    FILE* ir_file = fopen("test_module.ll", "w");
    if (ir_file) {
        fprintf(ir_file, "%s", ir_string);
        fclose(ir_file);
        printf("IR saved to test_module.ll\n");
    }
    
    // Now test deserialization from bitcode
    printf("\nTesting bitcode deserialization...\n");
    GeekIRModule* bitcode_module = geekir_module_read_bitcode(context, "test_module.bc");
    if (!bitcode_module) {
        printf("Failed to read bitcode\n");
        free(ir_string);
        geekir_builder_dispose(builder);
        geekir_module_dispose(original_module);
        geekir_context_dispose(context);
        return 1;
    }
    
    printf("Bitcode deserialized successfully!\n");
    
    // Verify the deserialized module
    result_code = geekir_module_verify(bitcode_module);
    printf("Bitcode module verification: %s\n", 
           result_code == GEEKIR_SUCCESS ? "SUCCESS" : "FAILED");
    
    // Test parsing from IR string
    printf("\nTesting IR string parsing...\n");
    GeekIRModule* ir_module = geekir_module_parse_ir(context, ir_string);
    if (!ir_module) {
        printf("Failed to parse IR string\n");
        free(ir_string);
        geekir_builder_dispose(builder);
        geekir_module_dispose(bitcode_module);
        geekir_module_dispose(original_module);
        geekir_context_dispose(context);
        return 1;
    }
    
    printf("IR string parsed successfully!\n");
    
    // Verify the parsed module
    result_code = geekir_module_verify(ir_module);
    printf("IR module verification: %s\n", 
           result_code == GEEKIR_SUCCESS ? "SUCCESS" : "FAILED");
    
    // Show the parsed IR
    char* parsed_ir = NULL;
    if (geekir_module_dump_to_string(ir_module, &parsed_ir) == GEEKIR_SUCCESS) {
        printf("\nParsed IR content:\n");
        printf("%s\n", parsed_ir);
        free(parsed_ir);
    }
    
    // Test round-trip serialization
    printf("\nTesting round-trip serialization...\n");
    
    // Write parsed module back to bitcode
    result_code = geekir_module_write_bitcode(ir_module, "test_module_roundtrip.bc");
    if (result_code == GEEKIR_SUCCESS) {
        printf("Round-trip bitcode written to test_module_roundtrip.bc\n");
    }
    
    // Read it back again
    GeekIRModule* roundtrip_module = geekir_module_read_bitcode(context, "test_module_roundtrip.bc");
    if (roundtrip_module) {
        result_code = geekir_module_verify(roundtrip_module);
        printf("Round-trip module verification: %s\n", 
               result_code == GEEKIR_SUCCESS ? "SUCCESS" : "FAILED");
        geekir_module_dispose(roundtrip_module);
    }
    
    // Cleanup
    free(ir_string);
    geekir_builder_dispose(builder);
    geekir_module_dispose(ir_module);
    geekir_module_dispose(bitcode_module);
    geekir_module_dispose(original_module);
    geekir_context_dispose(context);
    
    printf("\n=== Serialization Example Complete ===\n");
    return 0;
}
