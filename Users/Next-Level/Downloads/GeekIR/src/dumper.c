#include "../include/internal/common.h"
#include <stdlib.h>
#include <string.h>

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
