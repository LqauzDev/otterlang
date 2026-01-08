#include "../include/internal/common.h"
#include <stdlib.h>
#include <string.h>

GeekIRAnalysis* geekir_analysis_create(GeekIRModule* module) {
    GEEKIR_CHECK_NULL(module, NULL);
    
    GeekIRAnalysis* analysis = malloc(sizeof(GeekIRAnalysis));
    if (!analysis) {
        return NULL;
    }
    
    analysis->module = module;
    return analysis;
}

void geekir_analysis_dispose(GeekIRAnalysis* analysis) {
    if (!analysis) {
        return;
    }
    
    free(analysis);
}

bool geekir_analysis_verify_function(GeekIRAnalysis* analysis, GeekIRFunction* function) {
    if (!analysis || !function) {
        return false;
    }
    
    char* error = NULL;
    bool result = LLVMVerifyFunction(function->llvm_value, LLVMReturnStatusAction, &error) == 0;
    
    if (error) {
        LLVMDisposeMessage(error);
    }
    
    return result;
}

bool geekir_analysis_verify_module(GeekIRAnalysis* analysis, GeekIRModule* module) {
    if (!analysis || !module) {
        return false;
    }
    
    char* error = NULL;
    bool result = LLVMVerifyModule(module->llvm_module, LLVMReturnStatusAction, &error) == 0;
    
    if (error) {
        LLVMDisposeMessage(error);
    }
    
    return result;
}

size_t geekir_analysis_count_instructions(GeekIRAnalysis* analysis, GeekIRFunction* function) {
    if (!analysis || !function) {
        return 0;
    }
    
    size_t count = 0;
    LLVMBasicBlockRef block = LLVMGetFirstBasicBlock(function->llvm_value);
    
    while (block) {
        LLVMValueRef instruction = LLVMGetFirstInstruction(block);
        while (instruction) {
            count++;
            instruction = LLVMGetNextInstruction(instruction);
        }
        block = LLVMGetNextBasicBlock(block);
    }
    
    return count;
}

size_t geekir_analysis_count_basic_blocks(GeekIRAnalysis* analysis, GeekIRFunction* function) {
    if (!analysis || !function) {
        return 0;
    }
    
    return LLVMCountBasicBlocks(function->llvm_value);
}

bool geekir_analysis_is_critical_edge(GeekIRAnalysis* analysis, GeekIRBasicBlock* src, GeekIRBasicBlock* dest) {
    if (!analysis || !src || !dest) {
        return false;
    }
    
    /* An edge is critical if the source block has multiple successors
     * and the destination block has multiple predecessors */
    
    /* Check if source has multiple successors */
    LLVMValueRef src_term = LLVMGetBasicBlockTerminator(src->llvm_block);
    if (!src_term) {
        return false;
    }
    
    unsigned num_successors = LLVMGetNumSuccessors(src_term);
    if (num_successors <= 1) {
        return false;
    }
    
    /* Check if destination has multiple predecessors */
    size_t num_predecessors = 0;
    LLVMUseRef use = LLVMGetFirstUse(dest->llvm_block);
    while (use) {
        LLVMValueRef user = LLVMGetUser(use);
        if (LLVMIsABasicBlock(user)) {
            num_predecessors++;
        }
        use = LLVMGetNextUse(use);
    }
    
    return num_predecessors > 1;
}
