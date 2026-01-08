#include "../include/internal/common.h"
#include <stdlib.h>
#include <string.h>

GeekIRValue* geekir_value_get_const_int(GeekIRType* type, uint64_t value, bool sign_extend) {
    GEEKIR_CHECK_NULL(type, NULL);
    
    GeekIRValue* val = malloc(sizeof(GeekIRValue));
    if (!val) {
        return NULL;
    }
    
    val->llvm_value = LLVMConstInt(type->llvm_type, value, sign_extend ? 1 : 0);
    val->context = type->context;
    return val;
}

GeekIRValue* geekir_value_get_const_float(GeekIRType* type, double value) {
    GEEKIR_CHECK_NULL(type, NULL);
    
    GeekIRValue* val = malloc(sizeof(GeekIRValue));
    if (!val) {
        return NULL;
    }
    
    val->llvm_value = LLVMConstReal(type->llvm_type, value);
    val->context = type->context;
    return val;
}

GeekIRValue* geekir_value_get_const_null(GeekIRType* type) {
    GEEKIR_CHECK_NULL(type, NULL);
    
    GeekIRValue* val = malloc(sizeof(GeekIRValue));
    if (!val) {
        return NULL;
    }
    
    val->llvm_value = LLVMConstNull(type->llvm_type);
    val->context = type->context;
    return val;
}

GeekIRValue* geekir_value_get_const_undef(GeekIRType* type) {
    GEEKIR_CHECK_NULL(type, NULL);
    
    GeekIRValue* val = malloc(sizeof(GeekIRValue));
    if (!val) {
        return NULL;
    }
    
    val->llvm_value = LLVMGetUndef(type->llvm_type);
    val->context = type->context;
    return val;
}

GeekIRValue* geekir_value_get_const_zero(GeekIRType* type) {
    GEEKIR_CHECK_NULL(type, NULL);
    
    GeekIRValue* val = malloc(sizeof(GeekIRValue));
    if (!val) {
        return NULL;
    }
    
    val->llvm_value = LLVMConstNull(type->llvm_type);
    val->context = type->context;
    return val;
}

GeekIRValue* geekir_value_get_const_string(GeekIRContext* context, const char* string, size_t length) {
    GEEKIR_CHECK_NULL(context, NULL);
    GEEKIR_CHECK_NULL(string, NULL);
    
    GeekIRValue* val = malloc(sizeof(GeekIRValue));
    if (!val) {
        return NULL;
    }
    
    /* Create a constant string as an array of i8 */
    GeekIRType* i8_type = geekir_type_get_int8(context);
    if (!i8_type) {
        free(val);
        return NULL;
    }
    
    GeekIRType* array_type = geekir_type_get_array(i8_type, length + 1); /* +1 for null terminator */
    if (!array_type) {
        free(val);
        free(i8_type);
        return NULL;
    }
    
    val->llvm_value = LLVMConstStringInContext(context->llvm_context, string, (unsigned)length, 0);
    val->context = context;
    
    free(i8_type);
    free(array_type);
    return val;
}

GeekIRValue* geekir_value_get_const_gep(GeekIRValue* pointer, GeekIRValue** indices, size_t index_count) {
    GEEKIR_CHECK_NULL(pointer, NULL);
    
    GeekIRValue* val = malloc(sizeof(GeekIRValue));
    if (!val) {
        return NULL;
    }
    
    LLVMValueRef* llvm_indices = NULL;
    if (index_count > 0 && indices) {
        llvm_indices = malloc(index_count * sizeof(LLVMValueRef));
        if (!llvm_indices) {
            free(val);
            return NULL;
        }
        
        for (size_t i = 0; i < index_count; i++) {
            if (!indices[i]) {
                free(llvm_indices);
                free(val);
                return NULL;
            }
            llvm_indices[i] = indices[i]->llvm_value;
        }
    }
    
    val->llvm_value = LLVMConstGEP(pointer->llvm_value, llvm_indices, (unsigned)index_count);
    val->context = pointer->context;
    
    GEEKIR_SAFE_FREE(llvm_indices);
    return val;
}

GeekIRType* geekir_value_get_type(GeekIRValue* value) {
    GEEKIR_CHECK_NULL(value, NULL);
    
    GeekIRType* type = malloc(sizeof(GeekIRType));
    if (!type) {
        return NULL;
    }
    
    type->llvm_type = LLVMTypeOf(value->llvm_value);
    type->context = value->context;
    return type;
}

bool geekir_value_is_const(GeekIRValue* value) {
    if (!value || !value->llvm_value) {
        return false;
    }
    
    return LLVMIsConstant(value->llvm_value) != 0;
}
