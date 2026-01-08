#include "../include/geekir.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    printf("=== GeekIR Control Flow Example ===\n\n");
    
    // Create context and module
    GeekIRContext* context = geekir_context_create();
    GeekIRModule* module = geekir_module_create(context, "control_flow_module");
    
    if (!context || !module) {
        printf("Failed to create context or module\n");
        return 1;
    }
    
    // Create types
    GeekIRType* int32_type = geekir_type_get_int32(context);
    GeekIRType* void_type = geekir_type_get_void(context);
    GeekIRType* bool_type = geekir_type_get_int1(context);
    
    // Create a function that demonstrates various control flow patterns
    GeekIRType* loop_function_type = geekir_type_get_function(int32_type, &int32_type, 1, false);
    GeekIRFunction* loop_function = geekir_function_create(module, loop_function_type, "sum_up_to_n");
    
    // Create basic blocks for the loop
    GeekIRBasicBlock* entry = geekir_function_append_basic_block(loop_function, "entry");
    GeekIRBasicBlock* loop_header = geekir_function_append_basic_block(loop_function, "loop_header");
    GeekIRBasicBlock* loop_body = geekir_function_append_basic_block(loop_function, "loop_body");
    GeekIRBasicBlock* exit = geekir_function_append_basic_block(loop_function, "exit");
    
    GeekIRBuilder* builder = geekir_builder_create(context);
    
    // Entry block: initialize variables
    geekir_builder_set_position(builder, entry);
    GeekIRValue* n = geekir_function_get_param(loop_function, 0);
    
    // Allocate space for sum and i
    GeekIRType* int32_ptr_type = geekir_type_get_pointer(int32_type);
    GeekIRInstruction* sum_alloca = geekir_builder_alloca(builder, int32_type, "sum");
    GeekIRInstruction* i_alloca = geekir_builder_alloca(builder, int32_type, "i");
    
    // Initialize sum = 0, i = 0
    GeekIRValue* const_0 = geekir_value_get_const_int(int32_type, 0, false);
    GeekIRValue* const_1 = geekir_value_get_const_int(int32_type, 1, false);
    
    geekir_builder_store(builder, const_0, (GeekIRValue*)sum_alloca);
    geekir_builder_store(builder, const_0, (GeekIRValue*)i_alloca);
    
    // Jump to loop header
    geekir_builder_br(builder, loop_header);
    
    // Loop header: check condition i < n
    geekir_builder_set_position(builder, loop_header);
    GeekIRInstruction* i_load = geekir_builder_load(builder, (GeekIRValue*)i_alloca, "i");
    GeekIRInstruction* condition = geekir_builder_icmp_slt(builder, (GeekIRValue*)i_load, n, "cond");
    geekir_builder_cond_br(builder, (GeekIRValue*)condition, loop_body, exit);
    
    // Loop body: sum += i; i++
    geekir_builder_set_position(builder, loop_body);
    
    // sum += i
    GeekIRInstruction* sum_load = geekir_builder_load(builder, (GeekIRValue*)sum_alloca, "sum");
    GeekIRInstruction* new_sum = geekir_builder_add(builder, (GeekIRValue*)sum_load, (GeekIRValue*)i_load, "new_sum");
    geekir_builder_store(builder, (GeekIRValue*)new_sum, (GeekIRValue*)sum_alloca);
    
    // i++
    GeekIRInstruction* new_i = geekir_builder_add(builder, (GeekIRValue*)i_load, const_1, "new_i");
    geekir_builder_store(builder, (GeekIRValue*)new_i, (GeekIRValue*)i_alloca);
    
    // Jump back to loop header
    geekir_builder_br(builder, loop_header);
    
    // Exit block: return sum
    geekir_builder_set_position(builder, exit);
    GeekIRInstruction* final_sum = geekir_builder_load(builder, (GeekIRValue*)sum_alloca, "final_sum");
    geekir_builder_ret(builder, (GeekIRValue*)final_sum);
    
    // Create a function with switch statement
    GeekIRType* switch_function_type = geekir_type_get_function(int32_type, &int32_type, 1, false);
    GeekIRFunction* switch_function = geekir_function_create(module, switch_function_type, "switch_example");
    
    GeekIRBasicBlock* switch_entry = geekir_function_append_basic_block(switch_function, "entry");
    GeekIRBasicBlock* case_0 = geekir_function_append_basic_block(switch_function, "case_0");
    GeekIRBasicBlock* case_1 = geekir_function_append_basic_block(switch_function, "case_1");
    GeekIRBasicBlock* case_2 = geekir_function_append_basic_block(switch_function, "case_2");
    GeekIRBasicBlock* default_case = geekir_function_append_basic_block(switch_function, "default_case");
    GeekIRBasicBlock* switch_exit = geekir_function_append_basic_block(switch_function, "exit");
    
    // Switch implementation
    geekir_builder_set_position(builder, switch_entry);
    GeekIRValue* switch_value = geekir_function_get_param(switch_function, 0);
    
    GeekIRInstruction* switch_instr = geekir_builder_switch(builder, switch_value, default_case, 3);
    
    // Add switch cases (this would need additional LLVM API calls to add cases)
    // For simplicity, we'll jump directly to cases based on comparisons
    
    GeekIRValue* const_case0 = geekir_value_get_const_int(int32_type, 0, false);
    GeekIRValue* const_case1 = geekir_value_get_const_int(int32_type, 1, false);
    GeekIRValue* const_case2 = geekir_value_get_const_int(int32_type, 2, false);
    
    GeekIRInstruction* cmp0 = geekir_builder_icmp_eq(builder, switch_value, const_case0, "cmp0");
    GeekIRInstruction* cmp1 = geekir_builder_icmp_eq(builder, switch_value, const_case1, "cmp1");
    GeekIRInstruction* cmp2 = geekir_builder_icmp_eq(builder, switch_value, const_case2, "cmp2");
    
    GeekIRBasicBlock* check_case1 = geekir_function_append_basic_block(switch_function, "check_case1");
    GeekIRBasicBlock* check_case2 = geekir_function_append_basic_block(switch_function, "check_case2");
    
    geekir_builder_cond_br(builder, (GeekIRValue*)cmp0, case_0, check_case1);
    
    geekir_builder_set_position(builder, check_case1);
    geekir_builder_cond_br(builder, (GeekIRValue*)cmp1, case_1, check_case2);
    
    geekir_builder_set_position(builder, check_case2);
    geekir_builder_cond_br(builder, (GeekIRValue*)cmp2, case_2, default_case);
    
    // Case implementations
    geekir_builder_set_position(builder, case_0);
    GeekIRValue* ret0 = geekir_value_get_const_int(int32_type, 100, false);
    geekir_builder_br(builder, switch_exit);
    
    geekir_builder_set_position(builder, case_1);
    GeekIRValue* ret1 = geekir_value_get_const_int(int32_type, 200, false);
    geekir_builder_br(builder, switch_exit);
    
    geekir_builder_set_position(builder, case_2);
    GeekIRValue* ret2 = geekir_value_get_const_int(int32_type, 300, false);
    geekir_builder_br(builder, switch_exit);
    
    geekir_builder_set_position(builder, default_case);
    GeekIRValue* ret_default = geekir_value_get_const_int(int32_type, -1, false);
    geekir_builder_br(builder, switch_exit);
    
    geekir_builder_set_position(builder, switch_exit);
    // We would need phi nodes here to merge the return values
    // For simplicity, just return a default value
    geekir_builder_ret(builder, ret_default);
    
    // Create a main function to test
    GeekIRType* main_type = geekir_type_get_function(int32_type, NULL, 0, false);
    GeekIRFunction* main_func = geekir_function_create(module, main_type, "main");
    GeekIRBasicBlock* main_entry = geekir_function_append_basic_block(main_func, "entry");
    
    geekir_builder_set_position(builder, main_entry);
    GeekIRValue* const_10 = geekir_value_get_const_int(int32_type, 10, false);
    GeekIRInstruction* loop_call = geekir_builder_call(builder, (GeekIRValue*)loop_function, &const_10, 1, "sum_result");
    geekir_builder_ret(builder, (GeekIRValue*)loop_call);
    
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
        
        geekir_module_write_bitcode(module, "control_flow_example.bc");
        printf("Bitcode written to control_flow_example.bc\n");
    } else {
        printf("Module verification failed: %s\n", geekir_result_to_string(result));
    }
    
    // Cleanup
    geekir_builder_dispose(builder);
    geekir_module_dispose(module);
    geekir_context_dispose(context);
    
    printf("\n=== Control Flow Example Complete ===\n");
    return 0;
}
