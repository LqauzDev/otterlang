#include "../include/geekir.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    printf("=== GeekIR Optimization Example ===\n\n");
    
    // Create context and module
    GeekIRContext* context = geekir_context_create();
    GeekIRModule* module = geekir_module_create(context, "optimization_module");
    
    if (!context || !module) {
        printf("Failed to create context or module\n");
        return 1;
    }
    
    // Create types
    GeekIRType* int32_type = geekir_type_get_int32(context);
    GeekIRType* void_type = geekir_type_get_void(context);
    GeekIRType* function_type = geekir_type_get_function(int32_type, &int32_type, 1, false);
    
    // Create a function with optimization opportunities
    GeekIRFunction* function = geekir_function_create(module, function_type, "optimize_me");
    GeekIRBasicBlock* entry = geekir_function_append_basic_block(function, "entry");
    
    GeekIRBuilder* builder = geekir_builder_create(context);
    geekir_builder_set_position(builder, entry);
    
    GeekIRValue* x = geekir_function_get_param(function, 0);
    
    // Create some optimization opportunities:
    // 1. Constant folding: (2 + 3) * 4 should be optimized to 20
    GeekIRValue* const_2 = geekir_value_get_const_int(int32_type, 2, false);
    GeekIRValue* const_3 = geekir_value_get_const_int(int32_type, 3, false);
    GeekIRValue* const_4 = geekir_value_get_const_int(int32_type, 4, false);
    
    GeekIRInstruction* add_const = geekir_builder_add(builder, const_2, const_3, "add_const");
    GeekIRInstruction* mul_const = geekir_builder_mul(builder, (GeekIRValue*)add_const, const_4, "mul_const");
    
    // 2. Dead code: unused computation
    GeekIRValue* const_5 = geekir_value_get_const_int(int32_type, 5, false);
    GeekIRValue* const_6 = geekir_value_get_const_int(int32_type, 6, false);
    GeekIRInstruction* dead_code = geekir_builder_add(builder, const_5, const_6, "dead_code");
    
    // 3. Redundant operations: x + 0 should be optimized to x
    GeekIRValue* const_0 = geekir_value_get_const_int(int32_type, 0, false);
    GeekIRInstruction* redundant_add = geekir_builder_add(builder, x, const_0, "redundant_add");
    
    // 4. Algebraic simplification: x * 1 should be optimized to x
    GeekIRValue* const_1 = geekir_value_get_const_int(int32_type, 1, false);
    GeekIRInstruction* redundant_mul = geekir_builder_mul(builder, (GeekIRValue*)redundant_add, const_1, "redundant_mul");
    
    // 5. Final result: combine with constant result
    GeekIRInstruction* final_result = geekir_builder_add(builder, (GeekIRValue*)redundant_mul, (GeekIRValue*)mul_const, "final_result");
    
    geekir_builder_ret(builder, (GeekIRValue*)final_result);
    
    printf("Before optimization:\n");
    char* ir_before = NULL;
    if (geekir_module_dump_to_string(module, &ir_before) == GEEKIR_SUCCESS) {
        printf("%s\n", ir_before);
        free(ir_before);
    }
    
    // Run optimization passes
    printf("\nRunning optimization passes...\n");
    
    GeekIRResult opt_result;
    
    opt_result = geekir_transform_constant_folding(module);
    printf("Constant folding: %s\n", opt_result == GEEKIR_SUCCESS ? "SUCCESS" : "FAILED");
    
    opt_result = geekir_transform_instruction_combining(module);
    printf("Instruction combining: %s\n", opt_result == GEEKIR_SUCCESS ? "SUCCESS" : "FAILED");
    
    opt_result = geekir_transform_dead_code_elimination(module);
    printf("Dead code elimination: %s\n", opt_result == GEEKIR_SUCCESS ? "SUCCESS" : "FAILED");
    
    opt_result = geekir_transform_reassociate(module);
    printf("Reassociation: %s\n", opt_result == GEEKIR_SUCCESS ? "SUCCESS" : "FAILED");
    
    opt_result = geekir_transform_gvn(module);
    printf("GVN (Global Value Numbering): %s\n", opt_result == GEEKIR_SUCCESS ? "SUCCESS" : "FAILED");
    
    printf("\nAfter optimization:\n");
    char* ir_after = NULL;
    if (geekir_module_dump_to_string(module, &ir_after) == GEEKIR_SUCCESS) {
        printf("%s\n", ir_after);
        free(ir_after);
    }
    
    // Verify optimized module
    GeekIRResult verify_result = geekir_module_verify(module);
    printf("\nOptimized module verification: %s\n", 
           verify_result == GEEKIR_SUCCESS ? "SUCCESS" : "FAILED");
    
    // Write optimized bitcode
    if (geekir_module_write_bitcode(module, "optimization_example.bc") == GEEKIR_SUCCESS) {
        printf("Optimized bitcode written to optimization_example.bc\n");
    }
    
    // Cleanup
    geekir_builder_dispose(builder);
    geekir_module_dispose(module);
    geekir_context_dispose(context);
    
    printf("\n=== Optimization Example Complete ===\n");
    return 0;
}
