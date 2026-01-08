#include "../include/internal/common.h"
#include <stdlib.h>
#include <string.h>

GeekIRResult geekir_transform_constant_folding(GeekIRModule* module) {
    GEEKIR_CHECK_NULL(module, NULL);
    
    /* Create a pass manager */
    LLVMPassManagerRef pass_manager = LLVMCreatePassManager();
    if (!pass_manager) {
        return GEEKIR_ERROR_OUT_OF_MEMORY;
    }
    
    /* Add constant folding pass */
    LLVMAddConstantPropagationPass(pass_manager);
    
    /* Run the pass */
    LLVMRunPassManager(pass_manager, module->llvm_module);
    
    /* Clean up */
    LLVMDisposePassManager(pass_manager);
    
    return GEEKIR_SUCCESS;
}

GeekIRResult geekir_transform_dead_code_elimination(GeekIRModule* module) {
    GEEKIR_CHECK_NULL(module, NULL);
    
    LLVMPassManagerRef pass_manager = LLVMCreatePassManager();
    if (!pass_manager) {
        return GEEKIR_ERROR_OUT_OF_MEMORY;
    }
    
    LLVMAddDCEPass(pass_manager);
    LLVMRunPassManager(pass_manager, module->llvm_module);
    LLVMDisposePassManager(pass_manager);
    
    return GEEKIR_SUCCESS;
}

GeekIRResult geekir_transform_instruction_combining(GeekIRModule* module) {
    GEEKIR_CHECK_NULL(module, NULL);
    
    LLVMPassManagerRef pass_manager = LLVMCreatePassManager();
    if (!pass_manager) {
        return GEEKIR_ERROR_OUT_OF_MEMORY;
    }
    
    LLVMAddInstructionCombiningPass(pass_manager);
    LLVMRunPassManager(pass_manager, module->llvm_module);
    LLVMDisposePassManager(pass_manager);
    
    return GEEKIR_SUCCESS;
}

GeekIRResult geekir_transform_reassociate(GeekIRModule* module) {
    GEEKIR_CHECK_NULL(module, NULL);
    
    LLVMPassManagerRef pass_manager = LLVMCreatePassManager();
    if (!pass_manager) {
        return GEEKIR_ERROR_OUT_OF_MEMORY;
    }
    
    LLVMAddReassociatePass(pass_manager);
    LLVMRunPassManager(pass_manager, module->llvm_module);
    LLVMDisposePassManager(pass_manager);
    
    return GEEKIR_SUCCESS;
}

GeekIRResult geekir_transform_gvn(GeekIRModule* module) {
    GEEKIR_CHECK_NULL(module, NULL);
    
    LLVMPassManagerRef pass_manager = LLVMCreatePassManager();
    if (!pass_manager) {
        return GEEKIR_ERROR_OUT_OF_MEMORY;
    }
    
    LLVMAddGVNPass(pass_manager);
    LLVMRunPassManager(pass_manager, module->llvm_module);
    LLVMDisposePassManager(pass_manager);
    
    return GEEKIR_SUCCESS;
}

GeekIRResult geekir_transform_cfg_simplification(GeekIRModule* module) {
    GEEKIR_CHECK_NULL(module, NULL);
    
    LLVMPassManagerRef pass_manager = LLVMCreatePassManager();
    if (!pass_manager) {
        return GEEKIR_ERROR_OUT_OF_MEMORY;
    }
    
    LLVMAddCFGSimplificationPass(pass_manager);
    LLVMRunPassManager(pass_manager, module->llvm_module);
    LLVMDisposePassManager(pass_manager);
    
    return GEEKIR_SUCCESS;
}

GeekIRResult geekir_transform_licm(GeekIRModule* module) {
    GEEKIR_CHECK_NULL(module, NULL);
    
    LLVMPassManagerRef pass_manager = LLVMCreatePassManager();
    if (!pass_manager) {
        return GEEKIR_ERROR_OUT_OF_MEMORY;
    }
    
    LLVMAddLICMPass(pass_manager);
    LLVMRunPassManager(pass_manager, module->llvm_module);
    LLVMDisposePassManager(pass_manager);
    
    return GEEKIR_SUCCESS;
}

GeekIRResult geekir_transform_loop_unroll(GeekIRModule* module) {
    GEEKIR_CHECK_NULL(module, NULL);
    
    LLVMPassManagerRef pass_manager = LLVMCreatePassManager();
    if (!pass_manager) {
        return GEEKIR_ERROR_OUT_OF_MEMORY;
    }
    
    LLVMAddLoopUnrollPass(pass_manager);
    LLVMRunPassManager(pass_manager, module->llvm_module);
    LLVMDisposePassManager(pass_manager);
    
    return GEEKIR_SUCCESS;
}

GeekIRResult geekir_transform_mem2reg(GeekIRModule* module) {
    GEEKIR_CHECK_NULL(module, NULL);
    
    LLVMPassManagerRef pass_manager = LLVMCreatePassManager();
    if (!pass_manager) {
        return GEEKIR_ERROR_OUT_OF_MEMORY;
    }
    
    LLVMAddPromoteMemoryToRegisterPass(pass_manager);
    LLVMRunPassManager(pass_manager, module->llvm_module);
    LLVMDisposePassManager(pass_manager);
    
    return GEEKIR_SUCCESS;
}

GeekIRResult geekir_transform_sccp(GeekIRModule* module) {
    GEEKIR_CHECK_NULL(module, NULL);
    
    LLVMPassManagerRef pass_manager = LLVMCreatePassManager();
    if (!pass_manager) {
        return GEEKIR_ERROR_OUT_OF_MEMORY;
    }
    
    LLVMAddSCCPPass(pass_manager);
    LLVMRunPassManager(pass_manager, module->llvm_module);
    LLVMDisposePassManager(pass_manager);
    
    return GEEKIR_SUCCESS;
}

GeekIRResult geekir_transform_optimize_aggressive(GeekIRModule* module) {
    GEEKIR_CHECK_NULL(module, NULL);
    
    LLVMPassManagerRef pass_manager = LLVMCreatePassManager();
    if (!pass_manager) {
        return GEEKIR_ERROR_OUT_OF_MEMORY;
    }
    
    /* Create an aggressive optimization pipeline */
    LLVMAddCFGSimplificationPass(pass_manager);
    LLVMAddSCCPPass(pass_manager);
    LLVMAddInstructionCombiningPass(pass_manager);
    LLVMAddReassociatePass(pass_manager);
    LLVMAddConstantPropagationPass(pass_manager);
    LLVMAddPromoteMemoryToRegisterPass(pass_manager);
    LLVMAddInstructionCombiningPass(pass_manager);
    LLVMAddGVNPass(pass_manager);
    LLVMAddCFGSimplificationPass(pass_manager);
    LLVMAddLICMPass(pass_manager);
    LLVMAddAggressiveDCEPass(pass_manager);
    LLVMAddCFGSimplificationPass(pass_manager);
    LLVMAddInstructionCombiningPass(pass_manager);
    
    LLVMRunPassManager(pass_manager, module->llvm_module);
    LLVMDisposePassManager(pass_manager);
    
    return GEEKIR_SUCCESS;
}
