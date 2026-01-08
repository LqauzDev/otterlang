#include "../include/internal/common.h"
#include <stdlib.h>
#include <string.h>

GeekIRResult geekir_module_write_bitcode(GeekIRModule* module, const char* filename) {
    GEEKIR_CHECK_NULL(module, NULL);
    GEEKIR_CHECK_NULL(filename, NULL);
    
    if (LLVMWriteBitcodeToFile(module->llvm_module, filename)) {
        geekir_set_error(module->context, "Failed to write bitcode to file");
        return GEEKIR_ERROR_UNKNOWN;
    }
    
    return GEEKIR_SUCCESS;
}
