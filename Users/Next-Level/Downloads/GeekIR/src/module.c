#include "../include/internal/common.h"
#include <stdlib.h>
#include <string.h>

GeekIRModule* geekir_module_create(GeekIRContext* context, const char* name) {
    GEEKIR_CHECK_NULL(context, NULL);
    GEEKIR_CHECK_NULL(name, NULL);
    
    GeekIRModule* module = malloc(sizeof(GeekIRModule));
    if (!module) {
        return NULL;
    }
    
    module->llvm_module = LLVMModuleCreateWithNameInContext(name, context->llvm_context);
    if (!module->llvm_module) {
        free(module);
        return NULL;
    }
    
    module->context = context;
    return module;
}

void geekir_module_dispose(GeekIRModule* module) {
    if (!module) {
        return;
    }
    
    if (module->llvm_module) {
        LLVMDisposeModule(module->llvm_module);
    }
    
    free(module);
}

GeekIRResult geekir_module_verify(GeekIRModule* module) {
    GEEKIR_CHECK_NULL(module, NULL);
    
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

GeekIRResult geekir_module_dump_to_file(GeekIRModule* module, const char* filename) {
    GEEKIR_CHECK_NULL(module, NULL);
    GEEKIR_CHECK_NULL(filename, NULL);
    
    if (LLVMPrintModuleToFile(module->llvm_module, filename, NULL)) {
        geekir_set_error(module->context, "Failed to write module to file");
        return GEEKIR_ERROR_UNKNOWN;
    }
    
    return GEEKIR_SUCCESS;
}

GeekIRResult geekir_module_dump_to_string(GeekIRModule* module, char** output) {
    GEEKIR_CHECK_NULL(module, NULL);
    GEEKIR_CHECK_NULL(output, NULL);
    
    char* llvm_output = LLVMPrintModuleToString(module->llvm_module);
    if (!llvm_output) {
        geekir_set_error(module->context, "Failed to print module to string");
        return GEEKIR_ERROR_UNKNOWN;
    }
    
    *output = geekir_strdup(llvm_output);
    LLVMDisposeMessage(llvm_output);
    
    if (!*output) {
        return GEEKIR_ERROR_OUT_OF_MEMORY;
    }
    
    return GEEKIR_SUCCESS;
}

GeekIRResult geekir_module_write_bitcode(GeekIRModule* module, const char* filename) {
    GEEKIR_CHECK_NULL(module, NULL);
    GEEKIR_CHECK_NULL(filename, NULL);
    
    if (LLVMWriteBitcodeToFile(module->llvm_module, filename)) {
        geekir_set_error(module->context, "Failed to write bitcode to file");
        return GEEKIR_ERROR_UNKNOWN;
    }
    
    return GEEKIR_SUCCESS;
}

GeekIRModule* geekir_module_read_bitcode(GeekIRContext* context, const char* filename) {
    GEEKIR_CHECK_NULL(context, NULL);
    GEEKIR_CHECK_NULL(filename, NULL);
    
    LLVMMemoryBufferRef buffer = NULL;
    if (LLVMCreateMemoryBufferWithContentsOfFile(filename, &buffer, NULL)) {
        geekir_set_error(context, "Failed to read file into memory buffer");
        return NULL;
    }
    
    GeekIRModule* module = malloc(sizeof(GeekIRModule));
    if (!module) {
        LLVMDisposeMemoryBuffer(buffer);
        return NULL;
    }
    
    if (LLVMParseBitcodeInContext(context->llvm_context, buffer, &module->llvm_module, NULL)) {
        geekir_set_error(context, "Failed to parse bitcode");
        LLVMDisposeMemoryBuffer(buffer);
        free(module);
        return NULL;
    }
    
    module->context = context;
    LLVMDisposeMemoryBuffer(buffer);
    
    return module;
}

GeekIRModule* geekir_module_parse_ir(GeekIRContext* context, const char* ir_string) {
    GEEKIR_CHECK_NULL(context, NULL);
    GEEKIR_CHECK_NULL(ir_string, NULL);
    
    LLVMMemoryBufferRef buffer = LLVMCreateMemoryBufferWithMemoryRange(
        ir_string, strlen(ir_string), "ir_string", 0);
    
    if (!buffer) {
        geekir_set_error(context, "Failed to create memory buffer from IR string");
        return NULL;
    }
    
    GeekIRModule* module = malloc(sizeof(GeekIRModule));
    if (!module) {
        LLVMDisposeMemoryBuffer(buffer);
        return NULL;
    }
    
    if (LLVMParseIRInContext(context->llvm_context, buffer, &module->llvm_module, NULL)) {
        geekir_set_error(context, "Failed to parse IR string");
        LLVMDisposeMemoryBuffer(buffer);
        free(module);
        return NULL;
    }
    
    module->context = context;
    LLVMDisposeMemoryBuffer(buffer);
    
    return module;
}
