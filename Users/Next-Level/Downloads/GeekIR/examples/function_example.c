#include "../include/geekir.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    printf("=== GeekIR Function Example ===\n\n");
    
    // Create context and module
    GeekIRContext* context = geekir_context_create();
    GeekIRModule* module = geekir_module_create(context, "function_module");
    
    if (!context || !module) {
        printf("Failed to create context or module\n");
        return 1;
    }
    
    // Create types for factorial function
    GeekIRType* int32_type = geekir_type_get_int32(context);
    GeekIRType* void_type = geekir_type_get_void(context);
    GeekIRType* factorial_type = geekir_type_get_function(int32_type, &int32_type, 1, false);
    
    // Create factorial function
    GeekIRFunction* factorial = geekir_function_create(module, factorial_type, "factorial");
    GeekIRBasicBlock* entry = geekir_function_append_basic_block(factorial, "entry");
    GeekIRBasicBlock* base_case = geekir_function_append_basic_block(factorial, "base_case");
    GeekIRBasicBlock* recursive_case = geekir_function_append_basic_block(factorial, "recursive_case");
    
    GeekIRBuilder* builder = geekir_builder_create(context);
    
    // Entry block
    geekir_builder_set_position(builder, entry);
    GeekIRValue* n = geekir_function_get_param(factorial, 0);
    
    // Compare n <= 1
    GeekIRValue* const_1 = geekir_value_get_const_int(int32_type, 1, false);
    GeekIRInstruction* cmp = geekir_builder_icmp_sle(builder, n, const_1, "cmp");
    geekir_builder_cond_br(builder, (GeekIRValue*)cmp, base_case, recursive_case);
    
    // Base case: return 1
    geekir_builder_set_position(builder, base_case);
    geekir_builder_ret(builder, const_1);
    
    // Recursive case: n * factorial(n-1)
    geekir_builder_set_position(builder, recursive_case);
    GeekIRValue* const_0 = geekir_value_get_const_int(int32_type, 0, false);
    GeekIRInstruction* n_minus_1 = geekir_builder_sub(builder, n, const_1, "n_minus_1");
    GeekIRInstruction* factorial_call = geekir_builder_call(builder, (GeekIRValue*)factorial, (GeekIRValue**)&n_minus_1, 1, "factorial_call");
    GeekIRInstruction* result = geekir_builder_mul(builder, n, (GeekIRValue*)factorial_call, "result");
    geekir_builder_ret(builder, (GeekIRValue*)result);
    
    // Create a main function to test
    GeekIRType* main_type = geekir_type_get_function(int32_type, NULL, 0, false);
    GeekIRFunction* main_func = geekir_function_create(module, main_type, "main");
    GeekIRBasicBlock* main_entry = geekir_function_append_basic_block(main_func, "entry");
    
    geekir_builder_set_position(builder, main_entry);
    GeekIRValue* const_5 = geekir_value_get_const_int(int32_type, 5, false);
    GeekIRInstruction* main_call = geekir_builder_call(builder, (GeekIRValue*)factorial, &const_5, 1, "factorial_5");
    geekir_builder_ret(builder, (GeekIRValue*)main_call);
    
    // Verify and dump
    GeekIRResult result = geekir_module_verify(module);
    if (result == GEEKIR_SUCCESS) {
        printf("Module verification succeeded!\n\n");
        
        char* ir_output = NULL;
        if (geekir_module_dump_to_string(module, &ir_output) == GEEKIR_SUCCESS) {
            printf("Generated IR:\n");
            printf("%s\n", ir_output);
            free(ir_output);
        }
        
        geekir_module_write_bitcode(module, "function_example.bc");
        printf("Bitcode written to function_example.bc\n");
    } else {
        printf("Module verification failed: %s\n", geekir_result_to_string(result));
    }
    
    // Cleanup
    geekir_builder_dispose(builder);
    geekir_module_dispose(module);
    geekir_context_dispose(context);
    
    printf("\n=== Function Example Complete ===\n");
    return 0;
}
