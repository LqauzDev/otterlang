#include "../include/internal/common.h"
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>

char* geekir_strdup(const char* str) {
    if (!str) {
        return NULL;
    }
    
    size_t len = strlen(str);
    char* result = malloc(len + 1);
    if (result) {
        memcpy(result, str, len + 1);
    }
    return result;
}

char* geekir_format_string(const char* format, ...) {
    if (!format) {
        return NULL;
    }

    va_list args;
    va_start(args, format);
    
    /* First, determine the required buffer size */
    va_list args_copy;
    va_copy(args_copy, args);
    int size = vsnprintf(NULL, 0, format, args_copy);
    va_end(args_copy);
    
    if (size < 0) {
        va_end(args);
        return NULL;
    }
    
    /* Allocate buffer and format the string */
    char* result = malloc(size + 1);
    if (result) {
        vsnprintf(result, size + 1, format, args);
    }
    
    va_end(args);
    return result;
}

/* Library version information */
const char* geekir_get_version_string(void) {
    return "GeekIR 1.0.0";
}

uint32_t geekir_get_version_major(void) {
    return 1;
}

uint32_t geekir_get_version_minor(void) {
    return 0;
}

uint32_t geekir_get_version_patch(void) {
    return 0;
}

const char* geekir_result_to_string(GeekIRResult result) {
    switch (result) {
        case GEEKIR_SUCCESS:
            return "Success";
        case GEEKIR_ERROR_NULL_POINTER:
            return "Null pointer error";
        case GEEKIR_ERROR_INVALID_TYPE:
            return "Invalid type error";
        case GEEKIR_ERROR_OUT_OF_MEMORY:
            return "Out of memory error";
        case GEEKIR_ERROR_PARSE_FAILED:
            return "Parse failed error";
        case GEEKIR_ERROR_VERIFICATION_FAILED:
            return "Verification failed error";
        case GEEKIR_ERROR_UNKNOWN:
            return "Unknown error";
        default:
            return "Invalid error code";
    }
}

const char* geekir_type_to_string(GeekIRType* type) {
    if (!type || !type->llvm_type) {
        return "Invalid type";
    }
    
    char* result = LLVMPrintTypeToString(type->llvm_type);
    if (result) {
        char* copy = geekir_strdup(result);
        LLVMDisposeMessage(result);
        return copy;
    }
    return "Failed to get type string";
}

const char* geekir_value_to_string(GeekIRValue* value) {
    if (!value || !value->llvm_value) {
        return "Invalid value";
    }
    
    char* result = LLVMPrintValueToString(value->llvm_value);
    if (result) {
        char* copy = geekir_strdup(result);
        LLVMDisposeMessage(result);
        return copy;
    }
    return "Failed to get value string";
}

const char* geekir_instruction_to_string(GeekIRInstruction* instruction) {
    if (!instruction || !instruction->llvm_value) {
        return "Invalid instruction";
    }
    
    char* result = LLVMPrintValueToString(instruction->llvm_value);
    if (result) {
        char* copy = geekir_strdup(result);
        LLVMDisposeMessage(result);
        return copy;
    }
    return "Failed to get instruction string";
}
