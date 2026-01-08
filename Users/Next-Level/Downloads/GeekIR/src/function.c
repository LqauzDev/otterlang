#include "../include/internal/common.h"
#include <stdlib.h>
#include <string.h>

GeekIRFunction* geekir_function_create(GeekIRModule* module, GeekIRType* function_type, const char* name) {
    GEEKIR_CHECK_NULL(module, NULL);
    GEEKIR_CHECK_NULL(function_type, NULL);
    GEEKIR_CHECK_NULL(name, NULL);
    
    GeekIRFunction* function = malloc(sizeof(GeekIRFunction));
    if (!function) {
        return NULL;
    }
    
    function->llvm_value = LLVMAddFunction(module->llvm_module, name, function_type->llvm_type);
    function->context = module->context;
    
    return function;
}

GeekIRFunction* geekir_function_get(GeekIRModule* module, const char* name) {
    GEEKIR_CHECK_NULL(module, NULL);
    GEEKIR_CHECK_NULL(name, NULL);
    
    LLVMValueRef llvm_func = LLVMGetNamedFunction(module->llvm_module, name);
    if (!llvm_func) {
        return NULL;
    }
    
    GeekIRFunction* function = malloc(sizeof(GeekIRFunction));
    if (!function) {
        return NULL;
    }
    
    function->llvm_value = llvm_func;
    function->context = module->context;
    
    return function;
}

GeekIRBasicBlock* geekir_function_append_basic_block(GeekIRFunction* function, const char* name) {
    GEEKIR_CHECK_NULL(function, NULL);
    GEEKIR_CHECK_NULL(name, NULL);
    
    GeekIRBasicBlock* block = malloc(sizeof(GeekIRBasicBlock));
    if (!block) {
        return NULL;
    }
    
    block->llvm_block = LLVMAppendBasicBlockInContext(
        function->context->llvm_context, function->llvm_value, name);
    block->context = function->context;
    
    return block;
}

GeekIRBasicBlock* geekir_function_get_entry_block(GeekIRFunction* function) {
    GEEKIR_CHECK_NULL(function, NULL);
    
    LLVMBasicBlockRef entry_block = LLVMGetEntryBasicBlock(function->llvm_value);
    if (!entry_block) {
        return NULL;
    }
    
    GeekIRBasicBlock* block = malloc(sizeof(GeekIRBasicBlock));
    if (!block) {
        return NULL;
    }
    
    block->llvm_block = entry_block;
    block->context = function->context;
    
    return block;
}

GeekIRType* geekir_function_get_return_type(GeekIRFunction* function) {
    GEEKIR_CHECK_NULL(function, NULL);
    
    GeekIRType* type = malloc(sizeof(GeekIRType));
    if (!type) {
        return NULL;
    }
    
    type->llvm_type = LLVMGetReturnType(LLVMGetElementType(LLVMTypeOf(function->llvm_value)));
    type->context = function->context;
    
    return type;
}

size_t geekir_function_get_param_count(GeekIRFunction* function) {
    GEEKIR_CHECK_NULL(function, NULL);
    
    return LLVMCountParams(function->llvm_value);
}

GeekIRValue* geekir_function_get_param(GeekIRFunction* function, size_t index) {
    GEEKIR_CHECK_NULL(function, NULL);
    
    if (index >= geekir_function_get_param_count(function)) {
        return NULL;
    }
    
    GeekIRValue* value = malloc(sizeof(GeekIRValue));
    if (!value) {
        return NULL;
    }
    
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
