#include "../include/geekir.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

int test_analysis(void) {
    GeekIRContext* context = geekir_context_create();
    ASSERT(context != NULL, "Context creation should succeed");
    
    GeekIRModule* module = geekir_module_create(context, "test_module");
    ASSERT(module != NULL, "Module creation should succeed");
    
    // Create a simple function for analysis
    GeekIRType* int32_type = geekir_type_get_int32(context);
    GeekIRType* void_type = geekir_type_get_void(context);
    GeekIRType* function_type = geekir_type_get_function(void_type, &int32_type, 1, false);
    
    GeekIRFunction* function = geekir_function_create(module, function_type, "test_function");
    GeekIRBasicBlock* entry_block = geekir_function_append_basic_block(function, "entry");
    GeekIRBasicBlock* second_block = geekir_function_append_basic_block(function, "second");
    
    GeekIRBuilder* builder = geekir_builder_create(context);
    geekir_builder_set_position(builder, entry_block);
    
    GeekIRValue* param = geekir_function_get_param(function, 0);
    GeekIRValue* const_42 = geekir_value_get_const_int(int32_type, 42, false);
    GeekIRInstruction* add_instr = geekir_builder_add(builder, param, const_42, "result");
    geekir_builder_br(builder, second_block);
    
    geekir_builder_set_position(builder, second_block);
    geekir_builder_ret_void(builder);
    
    // Test analysis creation
    GeekIRAnalysis* analysis = geekir_analysis_create(module);
    ASSERT(analysis != NULL, "Analysis creation should succeed");
    
    // Test function verification
    bool function_valid = geekir_analysis_verify_function(analysis, function);
    ASSERT(function_valid == true, "Function verification should succeed");
    
    // Test module verification
    bool module_valid = geekir_analysis_verify_module(analysis, module);
    ASSERT(module_valid == true, "Module verification should succeed");
    
    // Test instruction counting
    size_t instr_count = geekir_analysis_count_instructions(analysis, function);
    ASSERT(instr_count == 2, "Function should have 2 instructions");
    
    // Test basic block counting
    size_t bb_count = geekir_analysis_count_basic_blocks(analysis, function);
    ASSERT(bb_count == 2, "Function should have 2 basic blocks");
    
    // Test critical edge detection (simple case - should not be critical)
    bool is_critical = geekir_analysis_is_critical_edge(analysis, entry_block, second_block);
    ASSERT(is_critical == false, "Simple edge should not be critical");
    
    // Test null pointer handling
    GeekIRAnalysis* null_analysis = geekir_analysis_create(NULL);
    ASSERT(null_analysis == NULL, "Null module analysis creation should return NULL");
    
    bool null_function_valid = geekir_analysis_verify_function(NULL, function);
    ASSERT(null_function_valid == false, "Null analysis function verification should return false");
    
    bool null_function = geekir_analysis_verify_function(analysis, NULL);
    ASSERT(null_function == false, "Null function verification should return false");
    
    bool null_module_valid = geekir_analysis_verify_module(NULL, module);
    ASSERT(null_module_valid == false, "Null analysis module verification should return false");
    
    bool null_mod = geekir_analysis_verify_module(analysis, NULL);
    ASSERT(null_mod == false, "Null module verification should return false");
    
    size_t null_instr_count = geekir_analysis_count_instructions(NULL, function);
    ASSERT(null_instr_count == 0, "Null analysis instruction count should return 0");
    
    size_t null_func_instr_count = geekir_analysis_count_instructions(analysis, NULL);
    ASSERT(null_func_instr_count == 0, "Null function instruction count should return 0");
    
    size_t null_bb_count = geekir_analysis_count_basic_blocks(NULL, function);
    ASSERT(null_bb_count == 0, "Null analysis basic block count should return 0");
    
    size_t null_func_bb_count = geekir_analysis_count_basic_blocks(analysis, NULL);
    ASSERT(null_func_bb_count == 0, "Null function basic block count should return 0");
    
    bool null_critical1 = geekir_analysis_is_critical_edge(NULL, entry_block, second_block);
    ASSERT(null_critical1 == false, "Null analysis critical edge should return false");
    
    bool null_critical2 = geekir_analysis_is_critical_edge(analysis, NULL, second_block);
    ASSERT(null_critical2 == false, "Null source critical edge should return false");
    
    bool null_critical3 = geekir_analysis_is_critical_edge(analysis, entry_block, NULL);
    ASSERT(null_critical3 == false, "Null destination critical edge should return false");
    
    geekir_analysis_dispose(analysis);
    geekir_builder_dispose(builder);
    geekir_module_dispose(module);
    geekir_context_dispose(context);
    
    return 1;
}
