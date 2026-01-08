#include "../include/geekir.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

int test_builder(void) {
    GeekIRContext* context = geekir_context_create();
    ASSERT(context != NULL, "Context creation should succeed");
    
    GeekIRModule* module = geekir_module_create(context, "test_module");
    ASSERT(module != NULL, "Module creation should succeed");
    
    // Create function and basic block
    GeekIRType* int32_type = geekir_type_get_int32(context);
    GeekIRType* void_type = geekir_type_get_void(context);
    GeekIRType* function_type = geekir_type_get_function(void_type, &int32_type, 1, false);
    
    GeekIRFunction* function = geekir_function_create(module, function_type, "test_function");
    GeekIRBasicBlock* entry_block = geekir_function_append_basic_block(function, "entry");
    
    // Test builder creation
    GeekIRBuilder* builder = geekir_builder_create(context);
    ASSERT(builder != NULL, "Builder creation should succeed");
    
    // Test builder positioning
    geekir_builder_set_position(builder, entry_block);
    
    // Test arithmetic operations
    GeekIRValue* param = geekir_function_get_param(function, 0);
    GeekIRValue* const_42 = geekir_value_get_const_int(int32_type, 42, false);
    
    GeekIRInstruction* add_instr = geekir_builder_add(builder, param, const_42, "result");
    ASSERT(add_instr != NULL, "Add instruction creation should succeed");
    
    GeekIRInstruction* sub_instr = geekir_builder_sub(builder, param, const_42, "sub_result");
    ASSERT(sub_instr != NULL, "Sub instruction creation should succeed");
    
    GeekIRInstruction* mul_instr = geekir_builder_mul(builder, param, const_42, "mul_result");
    ASSERT(mul_instr != NULL, "Mul instruction creation should succeed");
    
    GeekIRInstruction* div_instr = geekir_builder_div(builder, param, const_42, "div_result");
    ASSERT(div_instr != NULL, "Div instruction creation should succeed");
    
    GeekIRInstruction* rem_instr = geekir_builder_rem(builder, param, const_42, "rem_result");
    ASSERT(rem_instr != NULL, "Rem instruction creation should succeed");
    
    // Test bitwise operations
    GeekIRInstruction* and_instr = geekir_builder_and(builder, param, const_42, "and_result");
    ASSERT(and_instr != NULL, "And instruction creation should succeed");
    
    GeekIRInstruction* or_instr = geekir_builder_or(builder, param, const_42, "or_result");
    ASSERT(or_instr != NULL, "Or instruction creation should succeed");
    
    GeekIRInstruction* xor_instr = geekir_builder_xor(builder, param, const_42, "xor_result");
    ASSERT(xor_instr != NULL, "Xor instruction creation should succeed");
    
    GeekIRValue* const_1 = geekir_value_get_const_int(int32_type, 1, false);
    GeekIRInstruction* shl_instr = geekir_builder_shl(builder, param, const_1, "shl_result");
    ASSERT(shl_instr != NULL, "Shl instruction creation should succeed");
    
    GeekIRInstruction* lshr_instr = geekir_builder_lshr(builder, param, const_1, "lshr_result");
    ASSERT(lshr_instr != NULL, "Lshr instruction creation should succeed");
    
    GeekIRInstruction* ashr_instr = geekir_builder_ashr(builder, param, const_1, "ashr_result");
    ASSERT(ashr_instr != NULL, "Ashr instruction creation should succeed");
    
    // Test memory operations
    GeekIRInstruction* alloca_instr = geekir_builder_alloca(builder, int32_type, "local_var");
    ASSERT(alloca_instr != NULL, "Alloca instruction creation should succeed");
    
    GeekIRInstruction* store_instr = geekir_builder_store(builder, param, (GeekIRValue*)alloca_instr);
    ASSERT(store_instr != NULL, "Store instruction creation should succeed");
    
    GeekIRInstruction* load_instr = geekir_builder_load(builder, (GeekIRValue*)alloca_instr, "loaded_value");
    ASSERT(load_instr != NULL, "Load instruction creation should succeed");
    
    // Test GEP operations
    GeekIRType* int32_ptr_type = geekir_type_get_pointer(int32_type);
    GeekIRValue* const_0 = geekir_value_get_const_int(int32_type, 0, false);
    GeekIRValue* indices[] = { const_0 };
    
    GeekIRInstruction* gep_instr = geekir_builder_gep(builder, (GeekIRValue*)alloca_instr, indices, 1, "gep_result");
    ASSERT(gep_instr != NULL, "GEP instruction creation should succeed");
    
    GeekIRInstruction* inbounds_gep_instr = geekir_builder_inbounds_gep(builder, (GeekIRValue*)alloca_instr, indices, 1, "inbounds_gep_result");
    ASSERT(inbounds_gep_instr != NULL, "Inbounds GEP instruction creation should succeed");
    
    // Test comparison operations
    GeekIRInstruction* eq_instr = geekir_builder_icmp_eq(builder, param, const_42, "eq_result");
    ASSERT(eq_instr != NULL, "ICmp EQ instruction creation should succeed");
    
    GeekIRInstruction* ne_instr = geekir_builder_icmp_ne(builder, param, const_42, "ne_result");
    ASSERT(ne_instr != NULL, "ICmp NE instruction creation should succeed");
    
    GeekIRInstruction* slt_instr = geekir_builder_icmp_slt(builder, param, const_42, "slt_result");
    ASSERT(slt_instr != NULL, "ICmp SLT instruction creation should succeed");
    
    GeekIRInstruction* sgt_instr = geekir_builder_icmp_sgt(builder, param, const_42, "sgt_result");
    ASSERT(sgt_instr != NULL, "ICmp SGT instruction creation should succeed");
    
    // Test conversion operations
    GeekIRType* int64_type = geekir_type_get_int64(context);
    GeekIRInstruction* sext_instr = geekir_builder_sext(builder, param, int64_type, "sext_result");
    ASSERT(sext_instr != NULL, "Sext instruction creation should succeed");
    
    GeekIRInstruction* trunc_instr = geekir_builder_trunc(builder, (GeekIRValue*)sext_instr, int32_type, "trunc_result");
    ASSERT(trunc_instr != NULL, "Trunc instruction creation should succeed");
    
    // Test function calls
    GeekIRInstruction* call_instr = geekir_builder_call(builder, (GeekIRValue*)function, &param, 1, "call_result");
    ASSERT(call_instr != NULL, "Call instruction creation should succeed");
    
    // Test null pointer handling
    GeekIRBuilder* null_builder = geekir_builder_create(NULL);
    ASSERT(null_builder == NULL, "Null context builder creation should return NULL");
    
    // Test null operations
    GeekIRInstruction* null_add = geekir_builder_add(NULL, param, const_42, "null_add");
    ASSERT(null_add == NULL, "Null builder add should return NULL");
    
    GeekIRInstruction* null_param_add = geekir_builder_add(builder, NULL, const_42, "null_param_add");
    ASSERT(null_param_add == NULL, "Null param add should return NULL");
    
    GeekIRInstruction* null_const_add = geekir_builder_add(builder, param, NULL, "null_const_add");
    ASSERT(null_const_add == NULL, "Null const add should return NULL");
    
    geekir_builder_dispose(builder);
    geekir_module_dispose(module);
    geekir_context_dispose(context);
    
    return 1;
}
