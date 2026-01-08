#include "../include/geekir.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    printf("=== GeekIR Basic Example ===\n\n");
    
    // Create context and module
    GeekIRContext* context = geekir_context_create();
    if (!context) {
        printf("Failed to create context\n");
        return 1;
    }
    
    GeekIRModule* module = geekir_module_create(context, "basic_module");
    if (!module) {
        printf("Failed to create module\n");
        geekir_context_dispose(context);
        return 1;
    }
    
    // Create types
    GeekIRType* int32_type = geekir_type_get_int32(context);
    GeekIRType* void_type = geekir_type_get_void(context);
    GeekIRType* function_type = geekir_type_get_function(void_type, &int32_type, 1, false);
    
    // Create a simple function
    GeekIRFunction* function = geekir_function_create(module, function_type, "simple_function");
    if (!function) {
        printf("Failed to create function\n");
        geekir_module_dispose(module);
        geekir_context_dispose(context);
        return 1;
    }
    
    // Create basic block
    GeekIRBasicBlock* entry_block = geekir_function_append_basic_block(function, "entry");
    if (!entry_block) {
        printf("Failed to create basic block\n");
        geekir_module_dispose(module);
        geekir_context_dispose(context);
        return 1;
    }
    
    // Create builder
    GeekIRBuilder* builder = geekir_builder_create(context);
    if (!builder) {
        printf("Failed to create builder\n");
        geekir_module_dispose(module);
        geekir_context_dispose(context);
        return 1;
    }
    
    // Build simple function: return the input value + 42
    geekir_builder_set_position(builder, entry_block);
    
    // Get function parameter
    GeekIRValue* param = geekir_function_get_param(function, 0);
    GeekIRValue* const_42 = geekir_value_get_const_int(int32_type, 42, false);
    
    // Add 42 to parameter
    GeekIRInstruction* add_result = geekir_builder_add(builder, param, const_42, "result");
    
    // Return result
    geekir_builder_ret(builder, (GeekIRValue*)add_result);
    
    // Verify module
    GeekIRResult result = geekir_module_verify(module);
    if (result != GEEKIR_SUCCESS) {
        printf("Module verification failed: %s\n", geekir_result_to_string(result));
    } else {
        printf("Module verification succeeded!\n");
    }
    
    // Dump module to string
    char* ir_output = NULL;
    result = geekir_module_dump_to_string(module, &ir_output);
    if (result == GEEKIR_SUCCESS) {
        printf("\nGenerated IR:\n");
        printf("%s\n", ir_output);
        free(ir_output);
    }
    
    // Write bitcode
    result = geekir_module_write_bitcode(module, "basic_example.bc");
    if (result == GEEKIR_SUCCESS) {
        printf("Bitcode written to basic_example.bc\n");
    }
    
    // Cleanup
    geekir_builder_dispose(builder);
    geekir_module_dispose(module);
    geekir_context_dispose(context);
    
    printf("\n=== Basic Example Complete ===\n");
    return 0;
}
