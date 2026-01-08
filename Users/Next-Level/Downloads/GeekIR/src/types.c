#include "../include/internal/common.h"
#include <stdlib.h>
#include <string.h>

GeekIRType* geekir_type_get_void(GeekIRContext* context) {
    GEEKIR_CHECK_NULL(context, NULL);
    
    GeekIRType* type = malloc(sizeof(GeekIRType));
    if (!type) {
        return NULL;
    }
    
    type->llvm_type = LLVMVoidTypeInContext(context->llvm_context);
    type->context = context;
    return type;
}

GeekIRType* geekir_type_get_int1(GeekIRContext* context) {
    GEEKIR_CHECK_NULL(context, NULL);
    
    GeekIRType* type = malloc(sizeof(GeekIRType));
    if (!type) {
        return NULL;
    }
    
    type->llvm_type = LLVMInt1TypeInContext(context->llvm_context);
    type->context = context;
    return type;
}

GeekIRType* geekir_type_get_int8(GeekIRContext* context) {
    GEEKIR_CHECK_NULL(context, NULL);
    
    GeekIRType* type = malloc(sizeof(GeekIRType));
    if (!type) {
        return NULL;
    }
    
    type->llvm_type = LLVMInt8TypeInContext(context->llvm_context);
    type->context = context;
    return type;
}

GeekIRType* geekir_type_get_int16(GeekIRContext* context) {
    GEEKIR_CHECK_NULL(context, NULL);
    
    GeekIRType* type = malloc(sizeof(GeekIRType));
    if (!type) {
        return NULL;
    }
    
    type->llvm_type = LLVMInt16TypeInContext(context->llvm_context);
    type->context = context;
    return type;
}

GeekIRType* geekir_type_get_int32(GeekIRContext* context) {
    GEEKIR_CHECK_NULL(context, NULL);
    
    GeekIRType* type = malloc(sizeof(GeekIRType));
    if (!type) {
        return NULL;
    }
    
    type->llvm_type = LLVMInt32TypeInContext(context->llvm_context);
    type->context = context;
    return type;
}

GeekIRType* geekir_type_get_int64(GeekIRContext* context) {
    GEEKIR_CHECK_NULL(context, NULL);
    
    GeekIRType* type = malloc(sizeof(GeekIRType));
    if (!type) {
        return NULL;
    }
    
    type->llvm_type = LLVMInt64TypeInContext(context->llvm_context);
    type->context = context;
    return type;
}

GeekIRType* geekir_type_get_float(GeekIRContext* context) {
    GEEKIR_CHECK_NULL(context, NULL);
    
    GeekIRType* type = malloc(sizeof(GeekIRType));
    if (!type) {
        return NULL;
    }
    
    type->llvm_type = LLVMFloatTypeInContext(context->llvm_context);
    type->context = context;
    return type;
}

GeekIRType* geekir_type_get_double(GeekIRContext* context) {
    GEEKIR_CHECK_NULL(context, NULL);
    
    GeekIRType* type = malloc(sizeof(GeekIRType));
    if (!type) {
        return NULL;
    }
    
    type->llvm_type = LLVMDoubleTypeInContext(context->llvm_context);
    type->context = context;
    return type;
}

GeekIRType* geekir_type_get_pointer(GeekIRType* element_type) {
    GEEKIR_CHECK_NULL(element_type, NULL);
    
    GeekIRType* type = malloc(sizeof(GeekIRType));
    if (!type) {
        return NULL;
    }
    
    type->llvm_type = LLVMPointerType(element_type->llvm_type, 0);
    type->context = element_type->context;
    return type;
}

GeekIRType* geekir_type_get_array(GeekIRType* element_type, size_t size) {
    GEEKIR_CHECK_NULL(element_type, NULL);
    
    GeekIRType* type = malloc(sizeof(GeekIRType));
    if (!type) {
        return NULL;
    }
    
    type->llvm_type = LLVMArrayType(element_type->llvm_type, (unsigned)size);
    type->context = element_type->context;
    return type;
}

GeekIRType* geekir_type_get_vector(GeekIRType* element_type, size_t size) {
    GEEKIR_CHECK_NULL(element_type, NULL);
    
    GeekIRType* type = malloc(sizeof(GeekIRType));
    if (!type) {
        return NULL;
    }
    
    type->llvm_type = LLVMVectorType(element_type->llvm_type, (unsigned)size);
    type->context = element_type->context;
    return type;
}

GeekIRType* geekir_type_get_function(GeekIRType* return_type, GeekIRType** param_types, size_t param_count, bool is_var_args) {
    GEEKIR_CHECK_NULL(return_type, NULL);
    
    GeekIRType* type = malloc(sizeof(GeekIRType));
    if (!type) {
        return NULL;
    }
    
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
    
    GEEKIR_SAFE_FREE(llvm_param_types);
    return type;
}

GeekIRType* geekir_type_get_struct(GeekIRContext* context, GeekIRType** element_types, size_t element_count, bool packed) {
    GEEKIR_CHECK_NULL(context, NULL);
    
    GeekIRType* type = malloc(sizeof(GeekIRType));
    if (!type) {
        return NULL;
    }
    
    LLVMTypeRef* llvm_element_types = NULL;
    if (element_count > 0 && element_types) {
        llvm_element_types = malloc(element_count * sizeof(LLVMTypeRef));
        if (!llvm_element_types) {
            free(type);
            return NULL;
        }
        
        for (size_t i = 0; i < element_count; i++) {
            if (!element_types[i]) {
                free(llvm_element_types);
                free(type);
                return NULL;
            }
            llvm_element_types[i] = element_types[i]->llvm_type;
        }
    }
    
    type->llvm_type = LLVMStructTypeInContext(context->llvm_context, llvm_element_types, (unsigned)element_count, packed ? 1 : 0);
    type->context = context;
    
    GEEKIR_SAFE_FREE(llvm_element_types);
    return type;
}
