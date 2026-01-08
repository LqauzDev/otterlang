#include "../include/internal/common.h"
#include <stdlib.h>
#include <string.h>

GeekIRBasicBlock* geekir_basic_block_create(GeekIRContext* context, const char* name) {
    GEEKIR_CHECK_NULL(context, NULL);
    GEEKIR_CHECK_NULL(name, NULL);
    
    GeekIRBasicBlock* block = malloc(sizeof(GeekIRBasicBlock));
    if (!block) {
        return NULL;
    }
    
    /* Note: This creates a basic block without a parent function.
     * It will need to be inserted into a function later. */
    block->llvm_block = LLVMCreateBasicBlockInContext(context->llvm_context, name);
    block->context = context;
    
    return block;
}

GeekIRBasicBlock* geekir_basic_block_get_next(GeekIRBasicBlock* block) {
    GEEKIR_CHECK_NULL(block, NULL);
    
    LLVMBasicBlockRef next_block = LLVMGetNextBasicBlock(block->llvm_block);
    if (!next_block) {
        return NULL;
    }
    
    GeekIRBasicBlock* result = malloc(sizeof(GeekIRBasicBlock));
    if (!result) {
        return NULL;
    }
    
    result->llvm_block = next_block;
    result->context = block->context;
    
    return result;
}

GeekIRBasicBlock* geekir_basic_block_get_prev(GeekIRBasicBlock* block) {
    GEEKIR_CHECK_NULL(block, NULL);
    
    LLVMBasicBlockRef prev_block = LLVMGetPreviousBasicBlock(block->llvm_block);
    if (!prev_block) {
        return NULL;
    }
    
    GeekIRBasicBlock* result = malloc(sizeof(GeekIRBasicBlock));
    if (!result) {
        return NULL;
    }
    
    result->llvm_block = prev_block;
    result->context = block->context;
    
    return result;
}

GeekIRFunction* geekir_basic_block_get_parent(GeekIRBasicBlock* block) {
    GEEKIR_CHECK_NULL(block, NULL);
    
    LLVMValueRef parent_func = LLVMGetBasicBlockParent(block->llvm_block);
    if (!parent_func) {
        return NULL;
    }
    
    GeekIRFunction* function = malloc(sizeof(GeekIRFunction));
    if (!function) {
        return NULL;
    }
    
    function->llvm_value = parent_func;
    function->context = block->context;
    
    return function;
}

GeekIRInstruction* geekir_basic_block_get_first_instr(GeekIRBasicBlock* block) {
    GEEKIR_CHECK_NULL(block, NULL);
    
    LLVMValueRef first_instr = LLVMGetFirstInstruction(block->llvm_block);
    if (!first_instr) {
        return NULL;
    }
    
    GeekIRInstruction* instruction = malloc(sizeof(GeekIRInstruction));
    if (!instruction) {
        return NULL;
    }
    
    instruction->llvm_value = first_instr;
    instruction->context = block->context;
    
    return instruction;
}

GeekIRInstruction* geekir_basic_block_get_last_instr(GeekIRBasicBlock* block) {
    GEEKIR_CHECK_NULL(block, NULL);
    
    LLVMValueRef last_instr = LLVMGetLastInstruction(block->llvm_block);
    if (!last_instr) {
        return NULL;
    }
    
    GeekIRInstruction* instruction = malloc(sizeof(GeekIRInstruction));
    if (!instruction) {
        return NULL;
    }
    
    instruction->llvm_value = last_instr;
    instruction->context = block->context;
    
    return instruction;
}
