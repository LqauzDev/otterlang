#include "../include/geekir.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

int test_transforms(void) {
    GeekIRContext* context = geekir_context_create();
    ASSERT(context != NULL, "Context creation should succeed");
    
    GeekIRModule* module = geekir_module_create(context, "test_module");
    ASSERT(module != NULL, "Module creation should succeed");
    
    // Create a function with optimization opportunities
    GeekIRType* int32_type = geekir_type_get_int32(context);
    GeekIRType* void_type = geekir_type_get_void(context);
    GeekIRType* function_type = geekir_type_get_function(int32_type, &int32_type, 1, false);
    
    GeekIRFunction* function = geekir_function_create(module, function_type, "optimize_me");
    GeekIRBasicBlock* entry_block = geekir_function_append_basic_block(function, "entry");
    
    GeekIRBuilder* builder = geekir_builder_create(context);
    geekir_builder_set_position(builder, entry_block);
    
    GeekIRValue* param = geekir_function_get_param(function, 0);
    GeekIRValue* const_2 = geekir_value_get_const_int(int32_type, 2, false);
    GeekIRValue* const_3 = geekir_value_get_const_int(int32_type, 3, false);
    GeekIRValue* const_0 = geekir_value_get_const_int(int32_type, 0, false);
    GeekIRValue* const_1 = geekir_value_get_const_int(int32_type, 1, false);
    
    // Create optimization opportunities
    GeekIRInstruction* add_const = geekir_builder_add(builder, const_2, const_3, "add_const");
    GeekIRInstruction* redundant_add = geekir_builder_add(builder, param, const_0, "redundant_add");
    GeekIRInstruction* redundant_mul = geekir_builder_mul(builder, (GeekIRValue*)redundant_add, const_1, "redundant_mul");
    GeekIRInstruction* final_result = geekir_builder_add(builder, (GeekIRValue*)redundant_mul, (GeekIRValue*)add_const, "final_result");
    geekir_builder_ret(builder, (GeekIRValue*)final_result);
    
    // Verify module before optimization
    GeekIRResult result = geekir_module_verify(module);
    ASSERT(result == GEEKIR_SUCCESS, "Module verification should succeed before optimization");
    
    // Test constant folding
    result = geekir_transform_constant_folding(module);
    ASSERT(result == GEEKIR_SUCCESS, "Constant folding should succeed");
    
    result = geekir_module_verify(module);
    ASSERT(result == GEEKIR_SUCCESS, "Module verification should succeed after constant folding");
    
    // Test instruction combining
    result = geekir_transform_instruction_combining(module);
    ASSERT(result == GEEKIR_SUCCESS, "Instruction combining should succeed");
    
    result = geekir_module_verify(module);
    ASSERT(result == GEEKIR_SUCCESS, "Module verification should succeed after instruction combining");
    
    // Test dead code elimination
    result = geekir_transform_dead_code_elimination(module);
    ASSERT(result == GEEKIR_SUCCESS, "Dead code elimination should succeed");
    
    result = geekir_module_verify(module);
    ASSERT(result == GEEKIR_SUCCESS, "Module verification should succeed after dead code elimination");
    
    // Test reassociation
    result = geekir_transform_reassociate(module);
    ASSERT(result == GEEKIR_SUCCESS, "Reassociation should succeed");
    
    result = geekir_module_verify(module);
    ASSERT(result == GEEKIR_SUCCESS, "Module verification should succeed after reassociation");
    
    // Test GVN
    result = geekir_transform_gvn(module);
    ASSERT(result == GEEKIR_SUCCESS, "GVN should succeed");
    
    result = geekir_module_verify(module);
    ASSERT(result == GEEKIR_SUCCESS, "Module verification should succeed after GVN");
    
    // Test CFG simplification
    result = geekir_transform_cfg_simplification(module);
    ASSERT(result == GEEKIR_SUCCESS, "CFG simplification should succeed");
    
    result = geekir_module_verify(module);
    ASSERT(result == GEEKIR_SUCCESS, "Module verification should succeed after CFG simplification");
    
    // Test LICM
    result = geekir_transform_licm(module);
    ASSERT(result == GEEKIR_SUCCESS, "LICM should succeed");
    
    result = geekir_module_verify(module);
    ASSERT(result == GEEKIR_SUCCESS, "Module verification should succeed after LICM");
    
    // Test loop unroll
    result = geekir_transform_loop_unroll(module);
    ASSERT(result == GEEKIR_SUCCESS, "Loop unroll should succeed");
    
    result = geekir_module_verify(module);
    ASSERT(result == GEEKIR_SUCCESS, "Module verification should succeed after loop unroll");
    
    // Test mem2reg
    result = geekir_transform_mem2reg(module);
    ASSERT(result == GEEKIR_SUCCESS, "Mem2reg should succeed");
    
    result = geekir_module_verify(module);
    ASSERT(result == GEEKIR_SUCCESS, "Module verification should succeed after mem2reg");
    
    // Test SCCP
    result = geekir_transform_sccp(module);
    ASSERT(result == GEEKIR_SUCCESS, "SCCP should succeed");
    
    result = geekir_module_verify(module);
    ASSERT(result == GEEKIR_SUCCESS, "Module verification should succeed after SCCP");
    
    // Test aggressive optimization
    result = geekir_transform_optimize_aggressive(module);
    ASSERT(result == GEEKIR_SUCCESS, "Aggressive optimization should succeed");
    
    result = geekir_module_verify(module);
    ASSERT(result == GEEKIR_SUCCESS, "Module verification should succeed after aggressive optimization");
    
    // Test null pointer handling
    result = geekir_transform_constant_folding(NULL);
    ASSERT(result == GEEKIR_ERROR_NULL_POINTER, "Null module constant folding should return error");
    
    result = geekir_transform_instruction_combining(NULL);
    ASSERT(result == GEEKIR_ERROR_NULL_POINTER, "Null module instruction combining should return error");
    
    result = geekir_transform_dead_code_elimination(NULL);
    ASSERT(result == GEEKIR_ERROR_NULL_POINTER, "Null module dead code elimination should return error");
    
    result = geekir_transform_reassociate(NULL);
    ASSERT(result == GEEKIR_ERROR_NULL_POINTER, "Null module reassociate should return error");
    
    result = geekir_transform_gvn(NULL);
    ASSERT(result == GEEKIR_ERROR_NULL_POINTER, "Null module GVN should return error");
    
    result = geekir_transform_cfg_simplification(NULL);
    ASSERT(result == GEEKIR_ERROR_NULL_POINTER, "Null module CFG simplification should return error");
    
    result = geekir_transform_licm(NULL);
    ASSERT(result == GEEKIR_ERROR_NULL_POINTER, "Null module LICM should return error");
    
    result = geekir_transform_loop_unroll(NULL);
    ASSERT(result == GEEKIR_ERROR_NULL_POINTER, "Null module loop unroll should return error");
    
    result = geekir_transform_mem2reg(NULL);
    ASSERT(result == GEEKIR_ERROR_NULL_POINTER, "Null module mem2reg should return error");
    
    result = geekir_transform_sccp(NULL);
    ASSERT(result == GEEKIR_ERROR_NULL_POINTER, "Null module SCCP should return error");
    
    result = geekir_transform_optimize_aggressive(NULL);
    ASSERT(result == GEEKIR_ERROR_NULL_POINTER, "Null module aggressive optimization should return error");
    
    geekir_builder_dispose(builder);
    geekir_module_dispose(module);
    geekir_context_dispose(context);
    
    return 1;
}
