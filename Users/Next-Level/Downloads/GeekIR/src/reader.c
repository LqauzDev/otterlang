#include "../include/internal/common.h"
#include <stdlib.h>
#include <string.h>

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
