#include "../include/geekir.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

int test_instructions(void) {
    GeekIRContext* context = geekir_context_create();
    ASSERT(context != NULL, "Context creation should succeed");
    
    GeekIRModule* module = geekir_module_create(context, "test_module");
    ASSERT(module != NULL, "Module creation should succeed");
    
    // Create function and basic blocks
    GeekIRType* int32_type = geekir_type_get_int32(context);
    GeekIRType* void_type = geekir_type_get_void(context);
    GeekIRType* function_type = geekir_type_get_function(int32_type, &int32_type, 1, false);
    
    GeekIRFunction* function = geekir_function_create(module, function_type, "test_function");
    GeekIRBasicBlock* entry_block = geekir_function_append_basic_block(function, "entry");
    GeekIRBasicBlock* then_block = geekir_function_append_basic_block(function, "then");
    GeekIRBasicBlock* else_block = geekir_function_append_basic_block(function, "else");
    GeekIRBasicBlock* exit_block = geekir_function_append_basic_block(function, "exit");
    
    GeekIRBuilder* builder = geekir_builder_create(context);
    geekir_builder_set_position(builder, entry_block);
    
    GeekIRValue* param = geekir_function_get_param(function, 0);
    GeekIRValue* const_0 = geekir_value_get_const_int(int32_type, 0, false);
    GeekIRValue* const_42 = geekir_value_get_const_int(int32_type, 42, false);
    
    // Test control flow instructions
    GeekIRInstruction* br_instr = geekir_builder_br(builder, then_block);
    ASSERT(br_instr != NULL, "Br instruction creation should succeed");
    
    geekir_builder_set_position(builder, then_block);
    GeekIRInstruction* ret_instr = geekir_builder_ret(builder, const_42);
    ASSERT(ret_instr != NULL, "Ret instruction creation should succeed");
    
    geekir_builder_set_position(builder, else_block);
    GeekIRInstruction* ret_void_instr = geekir_builder_ret_void(builder);
    ASSERT(ret_void_instr != NULL, "Ret void instruction creation should succeed");
    
    // Test conditional branch
    GeekIRBasicBlock* cond_block = geekir_function_append_basic_block(function, "cond");
    geekir_builder_set_position(builder, cond_block);
    
    GeekIRInstruction* cmp_instr = geekir_builder_icmp_eq(builder, param, const_0, "cmp");
    ASSERT(cmp_instr != NULL, "Comparison instruction creation should succeed");
    
    GeekIRInstruction* cond_br_instr = geekir_builder_cond_br(builder, (GeekIRValue*)cmp_instr, then_block, else_block);
    ASSERT(cond_br_instr != NULL, "Conditional br instruction creation should succeed");
    
    // Test switch instruction
    GeekIRBasicBlock* switch_block = geekir_function_append_basic_block(function, "switch");
    GeekIRBasicBlock* default_block = geekir_function_append_basic_block(function, "default");
    
    geekir_builder_set_position(builder, switch_block);
    GeekIRInstruction* switch_instr = geekir_builder_switch(builder, param, default_block, 2);
    ASSERT(switch_instr != NULL, "Switch instruction creation should succeed");
    
    // Test all comparison operations
    GeekIRInstruction* eq_instr = geekir_builder_icmp_eq(builder, param, const_42, "eq");
    ASSERT(eq_instr != NULL, "ICmp EQ instruction creation should succeed");
    
    GeekIRInstruction* ne_instr = geekir_builder_icmp_ne(builder, param, const_42, "ne");
    ASSERT(ne_instr != NULL, "ICmp NE instruction creation should succeed");
    
    GeekIRInstruction* slt_instr = geekir_builder_icmp_slt(builder, param, const_42, "slt");
    ASSERT(slt_instr != NULL, "ICmp SLT instruction creation should succeed");
    
    GeekIRInstruction* sle_instr = geekir_builder_icmp_sle(builder, param, const_42, "sle");
    ASSERT(sle_instr != NULL, "ICmp SLE instruction creation should succeed");
    
    GeekIRInstruction* sgt_instr = geekir_builder_icmp_sgt(builder, param, const_42, "sgt");
    ASSERT(sgt_instr != NULL, "ICmp SGT instruction creation should succeed");
    
    GeekIRInstruction* sge_instr = geekir_builder_icmp_sge(builder, param, const_42, "sge");
    ASSERT(sge_instr != NULL, "ICmp SGE instruction creation should succeed");
    
    GeekIRInstruction* ult_instr = geekir_builder_icmp_ult(builder, param, const_42, "ult");
    ASSERT(ult_instr != NULL, "ICmp ULT instruction creation should succeed");
    
    GeekIRInstruction* ule_instr = geekir_builder_icmp_ule(builder, param, const_42, "ule");
    ASSERT(ule_instr != NULL, "ICmp ULE instruction creation should succeed");
    
    GeekIRInstruction* ugt_instr = geekir_builder_icmp_ugt(builder, param, const_42, "ugt");
    ASSERT(ugt_instr != NULL, "ICmp UGT instruction creation should succeed");
    
    GeekIRInstruction* uge_instr = geekir_builder_icmp_uge(builder, param, const_42, "uge");
    ASSERT(uge_instr != NULL, "ICmp UGE instruction creation should succeed");
    
    // Test conversion operations
    GeekIRType* int64_type = geekir_type_get_int64(context);
    GeekIRType* int16_type = geekir_type_get_int16(context);
    GeekIRType* float_type = geekir_type_get_float(context);
    GeekIRType* double_type = geekir_type_get_double(context);
    
    GeekIRInstruction* trunc_instr = geekir_builder_trunc(builder, param, int16_type, "trunc");
    ASSERT(trunc_instr != NULL, "Trunc instruction creation should succeed");
    
    GeekIRInstruction* zext_instr = geekir_builder_zext(builder, (GeekIRValue*)trunc_instr, int64_type, "zext");
    ASSERT(zext_instr != NULL, "Zext instruction creation should succeed");
    
    GeekIRInstruction* sext_instr = geekir_builder_sext(builder, param, int64_type, "sext");
    ASSERT(sext_instr != NULL, "Sext instruction creation should succeed");
    
    GeekIRInstruction* fptoui_instr = geekir_builder_fptoui(builder, (GeekIRValue*)float_type, int32_type, "fptoui");
    ASSERT(fptoui_instr != NULL, "FPTOUI instruction creation should succeed");
    
    GeekIRInstruction* fptosi_instr = geekir_builder_fptosi(builder, (GeekIRValue*)float_type, int32_type, "fptosi");
    ASSERT(fptosi_instr != NULL, "FPTOSI instruction creation should succeed");
    
    GeekIRInstruction* uitofp_instr = geekir_builder_uitofp(builder, param, float_type, "uitofp");
    ASSERT(uitofp_instr != NULL, "UITOFP instruction creation should succeed");
    
    GeekIRInstruction* sitofp_instr = geekir_builder_sitofp(builder, param, float_type, "sitofp");
    ASSERT(sitofp_instr != NULL, "SITOFP instruction creation should succeed");
    
    GeekIRInstruction* fptrunc_instr = geekir_builder_fptrunc(builder, (GeekIRValue*)double_type, float_type, "fptrunc");
    ASSERT(fptrunc_instr != NULL, "FPTRUNC instruction creation should succeed");
    
    GeekIRInstruction* fpext_instr = geekir_builder_fpext(builder, (GeekIRValue*)float_type, double_type, "fpext");
    ASSERT(fpext_instr != NULL, "FPEXT instruction creation should succeed");
    
    // Test function call
    GeekIRInstruction* call_instr = geekir_builder_call(builder, (GeekIRValue*)function, &param, 1, "call");
    ASSERT(call_instr != NULL, "Call instruction creation should succeed");
    
    // Test instruction to string
    const char* instr_string = geekir_instruction_to_string(add_instr);
    ASSERT(instr_string != NULL, "Instruction to string should succeed");
    ASSERT(strlen(instr_string) > 0, "Instruction string should not be empty");
    
    // Test null pointer handling for instructions
    GeekIRInstruction* null_br = geekir_builder_br(NULL, then_block);
    ASSERT(null_br == NULL, "Null builder br should return NULL");
    
    GeekIRInstruction* null_block_br = geekir_builder_br(builder, NULL);
    ASSERT(null_block_br == NULL, "Null block br should return NULL");
    
    GeekIRInstruction* null_ret = geekir_builder_ret(NULL, param);
    ASSERT(null_ret == NULL, "Null builder ret should return NULL");
    
    GeekIRInstruction* null_cond_br = geekir_builder_cond_br(NULL, (GeekIRValue*)cmp_instr, then_block, else_block);
    ASSERT(null_cond_br == NULL, "Null builder cond br should return NULL");
    
    GeekIRInstruction* null_cond = geekir_builder_cond_br(builder, NULL, then_block, else_block);
    ASSERT(null_cond == NULL, "Null condition cond br should return NULL");
    
    GeekIRInstruction* null_then = geekir_builder_cond_br(builder, (GeekIRValue*)cmp_instr, NULL, else_block);
    ASSERT(null_then == NULL, "Null then cond br should return NULL");
    
    GeekIRInstruction* null_else = geekir_builder_cond_br(builder, (GeekIRValue*)cmp_instr, then_block, NULL);
    ASSERT(null_else == NULL, "Null else cond br should return NULL");
    
    GeekIRInstruction* null_call = geekir_builder_call(NULL, (GeekIRValue*)function, &param, 1, "call");
    ASSERT(null_call == NULL, "Null builder call should return NULL");
    
    GeekIRInstruction* null_func_call = geekir_builder_call(builder, NULL, &param, 1, "call");
    ASSERT(null_func_call == NULL, "Null function call should return NULL");
    
    const char* null_instr_string = geekir_instruction_to_string(NULL);
    ASSERT(null_instr_string != NULL, "Null instruction to string should not crash");
    ASSERT(strcmp(null_instr_string, "Invalid instruction") == 0, "Null instruction string should match");
    
    geekir_builder_dispose(builder);
    geekir_module_dispose(module);
    geekir_context_dispose(context);
    
    return 1;
}
