#ifndef GEEKIR_H
#define GEEKIR_H

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Forward declarations */
typedef struct GeekIRContext GeekIRContext;
typedef struct GeekIRModule GeekIRModule;
typedef struct GeekIRType GeekIRType;
typedef struct GeekIRValue GeekIRValue;
typedef struct GeekIRInstruction GeekIRInstruction;
typedef struct GeekIRBasicBlock GeekIRBasicBlock;
typedef struct GeekIRFunction GeekIRFunction;
typedef struct GeekIRBuilder GeekIRBuilder;
typedef struct GeekIRAnalysis GeekIRAnalysis;

/* Error handling */
typedef enum {
    GEEKIR_SUCCESS = 0,
    GEEKIR_ERROR_NULL_POINTER,
    GEEKIR_ERROR_INVALID_TYPE,
    GEEKIR_ERROR_OUT_OF_MEMORY,
    GEEKIR_ERROR_PARSE_FAILED,
    GEEKIR_ERROR_VERIFICATION_FAILED,
    GEEKIR_ERROR_UNKNOWN
} GeekIRResult;

/* Context management */
GeekIRContext* geekir_context_create(void);
void geekir_context_dispose(GeekIRContext* context);
GeekIRResult geekir_context_set_target_triple(GeekIRContext* context, const char* triple);
GeekIRResult geekir_context_set_data_layout(GeekIRContext* context, const char* layout);

/* Module management */
GeekIRModule* geekir_module_create(GeekIRContext* context, const char* name);
void geekir_module_dispose(GeekIRModule* module);
GeekIRResult geekir_module_verify(GeekIRModule* module);
GeekIRResult geekir_module_dump_to_file(GeekIRModule* module, const char* filename);
GeekIRResult geekir_module_dump_to_string(GeekIRModule* module, char** output);
GeekIRResult geekir_module_write_bitcode(GeekIRModule* module, const char* filename);
GeekIRModule* geekir_module_read_bitcode(GeekIRContext* context, const char* filename);
GeekIRModule* geekir_module_parse_ir(GeekIRContext* context, const char* ir_string);

/* Type system */
GeekIRType* geekir_type_get_void(GeekIRContext* context);
GeekIRType* geekir_type_get_int1(GeekIRContext* context);
GeekIRType* geekir_type_get_int8(GeekIRContext* context);
GeekIRType* geekir_type_get_int16(GeekIRContext* context);
GeekIRType* geekir_type_get_int32(GeekIRContext* context);
GeekIRType* geekir_type_get_int64(GeekIRContext* context);
GeekIRType* geekir_type_get_float(GeekIRContext* context);
GeekIRType* geekir_type_get_double(GeekIRContext* context);
GeekIRType* geekir_type_get_pointer(GeekIRType* element_type);
GeekIRType* geekir_type_get_array(GeekIRType* element_type, size_t size);
GeekIRType* geekir_type_get_vector(GeekIRType* element_type, size_t size);
GeekIRType* geekir_type_get_function(GeekIRType* return_type, GeekIRType** param_types, size_t param_count, bool is_var_args);
GeekIRType* geekir_type_get_struct(GeekIRContext* context, GeekIRType** element_types, size_t element_count, bool packed);

/* Value operations */
GeekIRValue* geekir_value_get_const_int(GeekIRType* type, uint64_t value, bool sign_extend);
GeekIRValue* geekir_value_get_const_float(GeekIRType* type, double value);
GeekIRValue* geekir_value_get_const_null(GeekIRType* type);
GeekIRValue* geekir_value_get_const_undef(GeekIRType* type);
GeekIRValue* geekir_value_get_const_zero(GeekIRType* type);
GeekIRValue* geekir_value_get_const_string(GeekIRContext* context, const char* string, size_t length);
GeekIRValue* geekir_value_get_const_gep(GeekIRValue* pointer, GeekIRValue** indices, size_t index_count);
GeekIRType* geekir_value_get_type(GeekIRValue* value);
bool geekir_value_is_const(GeekIRValue* value);

/* Function operations */
GeekIRFunction* geekir_function_create(GeekIRModule* module, GeekIRType* function_type, const char* name);
GeekIRFunction* geekir_function_get(GeekIRModule* module, const char* name);
GeekIRBasicBlock* geekir_function_append_basic_block(GeekIRFunction* function, const char* name);
GeekIRBasicBlock* geekir_function_get_entry_block(GeekIRFunction* function);
GeekIRType* geekir_function_get_return_type(GeekIRFunction* function);
size_t geekir_function_get_param_count(GeekIRFunction* function);
GeekIRValue* geekir_function_get_param(GeekIRFunction* function, size_t index);

/* Basic block operations */
GeekIRBasicBlock* geekir_basic_block_create(GeekIRContext* context, const char* name);
GeekIRBasicBlock* geekir_basic_block_get_next(GeekIRBasicBlock* block);
GeekIRBasicBlock* geekir_basic_block_get_prev(GeekIRBasicBlock* block);
GeekIRFunction* geekir_basic_block_get_parent(GeekIRBasicBlock* block);
GeekIRInstruction* geekir_basic_block_get_first_instr(GeekIRBasicBlock* block);
GeekIRInstruction* geekir_basic_block_get_last_instr(GeekIRBasicBlock* block);

/* IR Builder */
GeekIRBuilder* geekir_builder_create(GeekIRContext* context);
void geekir_builder_dispose(GeekIRBuilder* builder);
void geekir_builder_set_position(GeekIRBuilder* builder, GeekIRBasicBlock* block);
void geekir_builder_set_position_before(GeekIRBuilder* builder, GeekIRInstruction* instr);
void geekir_builder_set_position_after(GeekIRBuilder* builder, GeekIRInstruction* instr);

/* Instruction builders - Arithmetic */
GeekIRInstruction* geekir_builder_add(GeekIRBuilder* builder, GeekIRValue* left, GeekIRValue* right, const char* name);
GeekIRInstruction* geekir_builder_sub(GeekIRBuilder* builder, GeekIRValue* left, GeekIRValue* right, const char* name);
GeekIRInstruction* geekir_builder_mul(GeekIRBuilder* builder, GeekIRValue* left, GeekIRValue* right, const char* name);
GeekIRInstruction* geekir_builder_div(GeekIRBuilder* builder, GeekIRValue* left, GeekIRValue* right, const char* name);
GeekIRInstruction* geekir_builder_rem(GeekIRBuilder* builder, GeekIRValue* left, GeekIRValue* right, const char* name);

/* Instruction builders - Bitwise */
GeekIRInstruction* geekir_builder_and(GeekIRBuilder* builder, GeekIRValue* left, GeekIRValue* right, const char* name);
GeekIRInstruction* geekir_builder_or(GeekIRBuilder* builder, GeekIRValue* left, GeekIRValue* right, const char* name);
GeekIRInstruction* geekir_builder_xor(GeekIRBuilder* builder, GeekIRValue* left, GeekIRValue* right, const char* name);
GeekIRInstruction* geekir_builder_shl(GeekIRBuilder* builder, GeekIRValue* left, GeekIRValue* right, const char* name);
GeekIRInstruction* geekir_builder_lshr(GeekIRBuilder* builder, GeekIRValue* left, GeekIRValue* right, const char* name);
GeekIRInstruction* geekir_builder_ashr(GeekIRBuilder* builder, GeekIRValue* left, GeekIRValue* right, const char* name);

/* Instruction builders - Memory */
GeekIRInstruction* geekir_builder_alloca(GeekIRBuilder* builder, GeekIRType* type, const char* name);
GeekIRInstruction* geekir_builder_load(GeekIRBuilder* builder, GeekIRValue* pointer, const char* name);
GeekIRInstruction* geekir_builder_store(GeekIRBuilder* builder, GeekIRValue* value, GeekIRValue* pointer);
GeekIRInstruction* geekir_builder_gep(GeekIRBuilder* builder, GeekIRValue* pointer, GeekIRValue** indices, size_t index_count, const char* name);
GeekIRInstruction* geekir_builder_inbounds_gep(GeekIRBuilder* builder, GeekIRValue* pointer, GeekIRValue** indices, size_t index_count, const char* name);

/* Instruction builders - Control flow */
GeekIRInstruction* geekir_builder_br(GeekIRBuilder* builder, GeekIRBasicBlock* dest);
GeekIRInstruction* geekir_builder_cond_br(GeekIRBuilder* builder, GeekIRValue* condition, GeekIRBasicBlock* then_block, GeekIRBasicBlock* else_block);
GeekIRInstruction* geekir_builder_ret(GeekIRBuilder* builder, GeekIRValue* value);
GeekIRInstruction* geekir_builder_ret_void(GeekIRBuilder* builder);
GeekIRInstruction* geekir_builder_switch(GeekIRBuilder* builder, GeekIRValue* value, GeekIRBasicBlock* default_block, size_t num_cases);

/* Instruction builders - Comparison */
GeekIRInstruction* geekir_builder_icmp_eq(GeekIRBuilder* builder, GeekIRValue* left, GeekIRValue* right, const char* name);
GeekIRInstruction* geekir_builder_icmp_ne(GeekIRBuilder* builder, GeekIRValue* left, GeekIRValue* right, const char* name);
GeekIRInstruction* geekir_builder_icmp_slt(GeekIRBuilder* builder, GeekIRValue* left, GeekIRValue* right, const char* name);
GeekIRInstruction* geekir_builder_icmp_sle(GeekIRBuilder* builder, GeekIRValue* left, GeekIRValue* right, const char* name);
GeekIRInstruction* geekir_builder_icmp_sgt(GeekIRBuilder* builder, GeekIRValue* left, GeekIRValue* right, const char* name);
GeekIRInstruction* geekir_builder_icmp_sge(GeekIRBuilder* builder, GeekIRValue* left, GeekIRValue* right, const char* name);
GeekIRInstruction* geekir_builder_icmp_ult(GeekIRBuilder* builder, GeekIRValue* left, GeekIRValue* right, const char* name);
GeekIRInstruction* geekir_builder_icmp_ule(GeekIRBuilder* builder, GeekIRValue* left, GeekIRValue* right, const char* name);
GeekIRInstruction* geekir_builder_icmp_ugt(GeekIRBuilder* builder, GeekIRValue* left, GeekIRValue* right, const char* name);
GeekIRInstruction* geekir_builder_icmp_uge(GeekIRBuilder* builder, GeekIRValue* left, GeekIRValue* right, const char* name);

/* Instruction builders - Conversion */
GeekIRInstruction* geekir_builder_trunc(GeekIRBuilder* builder, GeekIRValue* value, GeekIRType* dest_type, const char* name);
GeekIRInstruction* geekir_builder_zext(GeekIRBuilder* builder, GeekIRValue* value, GeekIRType* dest_type, const char* name);
GeekIRInstruction* geekir_builder_sext(GeekIRBuilder* builder, GeekIRValue* value, GeekIRType* dest_type, const char* name);
GeekIRInstruction* geekir_builder_fptoui(GeekIRBuilder* builder, GeekIRValue* value, GeekIRType* dest_type, const char* name);
GeekIRInstruction* geekir_builder_fptosi(GeekIRBuilder* builder, GeekIRValue* value, GeekIRType* dest_type, const char* name);
GeekIRInstruction* geekir_builder_uitofp(GeekIRBuilder* builder, GeekIRValue* value, GeekIRType* dest_type, const char* name);
GeekIRInstruction* geekir_builder_sitofp(GeekIRBuilder* builder, GeekIRValue* value, GeekIRType* dest_type, const char* name);
GeekIRInstruction* geekir_builder_fptrunc(GeekIRBuilder* builder, GeekIRValue* value, GeekIRType* dest_type, const char* name);
GeekIRInstruction* geekir_builder_fpext(GeekIRBuilder* builder, GeekIRValue* value, GeekIRType* dest_type, const char* name);

/* Instruction builders - Function calls */
GeekIRInstruction* geekir_builder_call(GeekIRBuilder* builder, GeekIRValue* function, GeekIRValue** args, size_t arg_count, const char* name);

/* Analysis */
GeekIRAnalysis* geekir_analysis_create(GeekIRModule* module);
void geekir_analysis_dispose(GeekIRAnalysis* analysis);
bool geekir_analysis_verify_function(GeekIRAnalysis* analysis, GeekIRFunction* function);
bool geekir_analysis_verify_module(GeekIRAnalysis* analysis, GeekIRModule* module);
size_t geekir_analysis_count_instructions(GeekIRAnalysis* analysis, GeekIRFunction* function);
size_t geekir_analysis_count_basic_blocks(GeekIRAnalysis* analysis, GeekIRFunction* function);
bool geekir_analysis_is_critical_edge(GeekIRAnalysis* analysis, GeekIRBasicBlock* src, GeekIRBasicBlock* dest);

/* Optimization passes */
GeekIRResult geekir_transform_constant_folding(GeekIRModule* module);
GeekIRResult geekir_transform_dead_code_elimination(GeekIRModule* module);
GeekIRResult geekir_transform_instruction_combining(GeekIRModule* module);
GeekIRResult geekir_transform_reassociate(GeekIRModule* module);
GeekIRResult geekir_transform_gvn(GeekIRModule* module);
GeekIRResult geekir_transform_cfg_simplification(GeekIRModule* module);
GeekIRResult geekir_transform_licm(GeekIRModule* module);
GeekIRResult geekir_transform_loop_unroll(GeekIRModule* module);
GeekIRResult geekir_transform_mem2reg(GeekIRModule* module);
GeekIRResult geekir_transform_sccp(GeekIRModule* module);
GeekIRResult geekir_transform_optimize_aggressive(GeekIRModule* module);

/* Utility functions */
const char* geekir_get_version_string(void);
uint32_t geekir_get_version_major(void);
uint32_t geekir_get_version_minor(void);
uint32_t geekir_get_version_patch(void);
const char* geekir_result_to_string(GeekIRResult result);
const char* geekir_type_to_string(GeekIRType* type);
const char* geekir_value_to_string(GeekIRValue* value);
const char* geekir_instruction_to_string(GeekIRInstruction* instruction);

#ifdef __cplusplus
}
#endif

#endif /* GEEKIR_H */
