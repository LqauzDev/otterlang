#ifndef GEEKIR_H
#define GEEKIR_H

/*
 * GeekIR - Simple LLVM IR Manipulation Library
 * 
 * This is a single-header version for easy integration into existing projects.
 * Simply include this header and link against LLVM libraries.
 * 
 * Required LLVM libraries:
 * - core
 * - irreader  
 * - bitreader
 * - bitwriter
 * - analysis
 * - passes
 * - transformutils
 * - support
 */

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Include LLVM C API */
#include <llvm-c/Core.h>
#include <llvm-c/IRReader.h>
#include <llvm-c/BitReader.h>
#include <llvm-c/BitWriter.h>
#include <llvm-c/Analysis.h>
#include <llvm-c/Transforms/Scalar.h>
#include <llvm-c/Transforms/Utils.h>
#include <llvm-c/Target.h>
#include <llvm-c/TargetMachine.h>

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

/* Internal structure definitions */
struct GeekIRContext {
    LLVMContextRef llvm_context;
    char* error_message;
};

struct GeekIRModule {
    LLVMModuleRef llvm_module;
    GeekIRContext* context;
};

struct GeekIRType {
    LLVMTypeRef llvm_type;
    GeekIRContext* context;
};

struct GeekIRValue {
    LLVMValueRef llvm_value;
    GeekIRContext* context;
};

struct GeekIRInstruction {
    LLVMValueRef llvm_value;
    GeekIRContext* context;
};

struct GeekIRBasicBlock {
    LLVMBasicBlockRef llvm_block;
    GeekIRContext* context;
};

struct GeekIRFunction {
    LLVMValueRef llvm_value;
    GeekIRContext* context;
};

struct GeekIRBuilder {
    LLVMBuilderRef llvm_builder;
    GeekIRContext* context;
};

struct GeekIRAnalysis {
    GeekIRModule* module;
};

/* Internal utility functions */
static inline char* geekir_strdup(const char* str) {
    if (!str) return NULL;
    size_t len = strlen(str);
    char* result = malloc(len + 1);
    if (result) memcpy(result, str, len + 1);
    return result;
}

static inline void geekir_set_error(GeekIRContext* context, const char* message) {
    if (context && context->error_message) {
        free(context->error_message);
    }
    if (context && message) {
        context->error_message = geekir_strdup(message);
    }
}

/* Context management */
GeekIRContext* geekir_context_create(void) {
    GeekIRContext* context = calloc(1, sizeof(GeekIRContext));
    if (!context) return NULL;
    
    context->llvm_context = LLVMContextCreate();
    if (!context->llvm_context) {
        free(context);
        return NULL;
    }
    
    return context;
}

void geekir_context_dispose(GeekIRContext* context) {
    if (!context) return;
    if (context->llvm_context) LLVMContextDispose(context->llvm_context);
    if (context->error_message) free(context->error_message);
    free(context);
}

/* Module management */
GeekIRModule* geekir_module_create(GeekIRContext* context, const char* name) {
    if (!context || !name) return NULL;
    
    GeekIRModule* module = malloc(sizeof(GeekIRModule));
    if (!module) return NULL;
    
    module->llvm_module = LLVMModuleCreateWithNameInContext(name, context->llvm_context);
    if (!module->llvm_module) {
        free(module);
        return NULL;
    }
    
    module->context = context;
    return module;
}

void geekir_module_dispose(GeekIRModule* module) {
    if (!module) return;
    if (module->llvm_module) LLVMDisposeModule(module->llvm_module);
    free(module);
}

GeekIRResult geekir_module_verify(GeekIRModule* module) {
    if (!module) return GEEKIR_ERROR_NULL_POINTER;
    
    char* error = NULL;
    if (LLVMVerifyModule(module->llvm_module, LLVMReturnStatusAction, &error)) {
        if (error) {
            geekir_set_error(module->context, error);
            LLVMDisposeMessage(error);
        }
        return GEEKIR_ERROR_VERIFICATION_FAILED;
    }
    return GEEKIR_SUCCESS;
}

GeekIRResult geekir_module_dump_to_string(GeekIRModule* module, char** output) {
    if (!module || !output) return GEEKIR_ERROR_NULL_POINTER;
    
    char* llvm_output = LLVMPrintModuleToString(module->llvm_module);
    if (!llvm_output) return GEEKIR_ERROR_UNKNOWN;
    
    *output = geekir_strdup(llvm_output);
    LLVMDisposeMessage(llvm_output);
    
    return *output ? GEEKIR_SUCCESS : GEEKIR_ERROR_OUT_OF_MEMORY;
}

GeekIRResult geekir_module_write_bitcode(GeekIRModule* module, const char* filename) {
    if (!module || !filename) return GEEKIR_ERROR_NULL_POINTER;
    
    return LLVMWriteBitcodeToFile(module->llvm_module, filename) ? GEEKIR_ERROR_UNKNOWN : GEEKIR_SUCCESS;
}

/* Type system */
GeekIRType* geekir_type_get_void(GeekIRContext* context) {
    if (!context) return NULL;
    
    GeekIRType* type = malloc(sizeof(GeekIRType));
    if (!type) return NULL;
    
    type->llvm_type = LLVMVoidTypeInContext(context->llvm_context);
    type->context = context;
    return type;
}

GeekIRType* geekir_type_get_int32(GeekIRContext* context) {
    if (!context) return NULL;
    
    GeekIRType* type = malloc(sizeof(GeekIRType));
    if (!type) return NULL;
    
    type->llvm_type = LLVMInt32TypeInContext(context->llvm_context);
    type->context = context;
    return type;
}

GeekIRType* geekir_type_get_int64(GeekIRContext* context) {
    if (!context) return NULL;
    
    GeekIRType* type = malloc(sizeof(GeekIRType));
    if (!type) return NULL;
    
    type->llvm_type = LLVMInt64TypeInContext(context->llvm_context);
    type->context = context;
    return type;
}

GeekIRType* geekir_type_get_pointer(GeekIRType* element_type) {
    if (!element_type) return NULL;
    
    GeekIRType* type = malloc(sizeof(GeekIRType));
    if (!type) return NULL;
    
    type->llvm_type = LLVMPointerType(element_type->llvm_type, 0);
    type->context = element_type->context;
    return type;
}

GeekIRType* geekir_type_get_function(GeekIRType* return_type, GeekIRType** param_types, size_t param_count, bool is_var_args) {
    if (!return_type) return NULL;
    
    GeekIRType* type = malloc(sizeof(GeekIRType));
    if (!type) return NULL;
    
    LLVMTypeRef* llvm_param_types = NULL;
    if (param_count > 0 && param_types) {
        llvm_param_types = malloc(param_count * sizeof(LLVMTypeRef));
        if (!llvm_param_types) {
            free(type);
            return NULL;
        }
        
        for (size_t i = 0; i < param_count; i++) {
            if (!param_types[i]) {
                free(llvm_param_types);
                free(type);
                return NULL;
            }
            llvm_param_types[i] = param_types[i]->llvm_type;
        }
    }
    
    type->llvm_type = LLVMFunctionType(return_type->llvm_type, llvm_param_types, (unsigned)param_count, is_var_args ? 1 : 0);
    type->context = return_type->context;
    
    free(llvm_param_types);
    return type;
}

/* Value operations */
GeekIRValue* geekir_value_get_const_int(GeekIRType* type, uint64_t value, bool sign_extend) {
    if (!type) return NULL;
    
    GeekIRValue* val = malloc(sizeof(GeekIRValue));
    if (!val) return NULL;
    
    val->llvm_value = LLVMConstInt(type->llvm_type, value, sign_extend ? 1 : 0);
    val->context = type->context;
    return val;
}

/* Function operations */
GeekIRFunction* geekir_function_create(GeekIRModule* module, GeekIRType* function_type, const char* name) {
    if (!module || !function_type || !name) return NULL;
    
    GeekIRFunction* function = malloc(sizeof(GeekIRFunction));
    if (!function) return NULL;
    
    function->llvm_value = LLVMAddFunction(module->llvm_module, name, function_type->llvm_type);
    function->context = module->context;
    
    return function;
}

GeekIRBasicBlock* geekir_function_append_basic_block(GeekIRFunction* function, const char* name) {
    if (!function || !name) return NULL;
    
    GeekIRBasicBlock* block = malloc(sizeof(GeekIRBasicBlock));
    if (!block) return NULL;
    
    block->llvm_block = LLVMAppendBasicBlockInContext(function->context->llvm_context, function->llvm_value, name);
    block->context = function->context;
    
    return block;
}

size_t geekir_function_get_param_count(GeekIRFunction* function) {
    if (!function) return 0;
    return LLVMCountParams(function->llvm_value);
}

GeekIRValue* geekir_function_get_param(GeekIRFunction* function, size_t index) {
    if (!function || index >= geekir_function_get_param_count(function)) return NULL;
    
    GeekIRValue* value = malloc(sizeof(GeekIRValue));
    if (!value) return NULL;
    
    LLVMValueRef* params = malloc((index + 1) * sizeof(LLVMValueRef));
    if (!params) {
        free(value);
        return NULL;
    }
    
    LLVMGetParams(function->llvm_value, params);
    value->llvm_value = params[index];
    value->context = function->context;
    
    free(params);
    return value;
}

/* IR Builder */
GeekIRBuilder* geekir_builder_create(GeekIRContext* context) {
    if (!context) return NULL;
    
    GeekIRBuilder* builder = malloc(sizeof(GeekIRBuilder));
    if (!builder) return NULL;
    
    builder->llvm_builder = LLVMCreateBuilderInContext(context->llvm_context);
    if (!builder->llvm_builder) {
        free(builder);
        return NULL;
    }
    
    builder->context = context;
    return builder;
}

void geekir_builder_dispose(GeekIRBuilder* builder) {
    if (!builder) return;
    if (builder->llvm_builder) LLVMDisposeBuilder(builder->llvm_builder);
    free(builder);
}

void geekir_builder_set_position(GeekIRBuilder* builder, GeekIRBasicBlock* block) {
    if (!builder || !block) return;
    LLVMPositionBuilderAtEnd(builder->llvm_builder, block->llvm_block);
}

/* Instruction builders - Arithmetic */
GeekIRInstruction* geekir_builder_add(GeekIRBuilder* builder, GeekIRValue* left, GeekIRValue* right, const char* name) {
    if (!builder || !left || !right) return NULL;
    
    GeekIRInstruction* instruction = malloc(sizeof(GeekIRInstruction));
    if (!instruction) return NULL;
    
    instruction->llvm_value = LLVMBuildAdd(builder->llvm_builder, left->llvm_value, right->llvm_value, name ? name : "");
    instruction->context = builder->context;
    
    return instruction;
}

GeekIRInstruction* geekir_builder_ret(GeekIRBuilder* builder, GeekIRValue* value) {
    if (!builder) return NULL;
    
    GeekIRInstruction* instruction = malloc(sizeof(GeekIRInstruction));
    if (!instruction) return NULL;
    
    instruction->llvm_value = LLVMBuildRet(builder->llvm_builder, value ? value->llvm_value : NULL);
    instruction->context = builder->context;
    
    return instruction;
}

/* Utility functions */
const char* geekir_result_to_string(GeekIRResult result) {
    switch (result) {
        case GEEKIR_SUCCESS: return "Success";
        case GEEKIR_ERROR_NULL_POINTER: return "Null pointer error";
        case GEEKIR_ERROR_INVALID_TYPE: return "Invalid type error";
        case GEEKIR_ERROR_OUT_OF_MEMORY: return "Out of memory error";
        case GEEKIR_ERROR_PARSE_FAILED: return "Parse failed error";
        case GEEKIR_ERROR_VERIFICATION_FAILED: return "Verification failed error";
        case GEEKIR_ERROR_UNKNOWN: return "Unknown error";
        default: return "Invalid error code";
    }
}

#ifdef __cplusplus
}
#endif

#endif /* GEEKIR_H */
