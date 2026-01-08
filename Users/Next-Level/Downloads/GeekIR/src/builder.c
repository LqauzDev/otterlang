#include "../include/internal/common.h"
#include <stdlib.h>
#include <string.h>

GeekIRBuilder* geekir_builder_create(GeekIRContext* context) {
    GEEKIR_CHECK_NULL(context, NULL);
    
    GeekIRBuilder* builder = malloc(sizeof(GeekIRBuilder));
    if (!builder) {
        return NULL;
    }
    
    builder->llvm_builder = LLVMCreateBuilderInContext(context->llvm_context);
    if (!builder->llvm_builder) {
        free(builder);
        return NULL;
    }
    
    builder->context = context;
    return builder;
}

void geekir_builder_dispose(GeekIRBuilder* builder) {
    if (!builder) {
        return;
    }
    
    if (builder->llvm_builder) {
        LLVMDisposeBuilder(builder->llvm_builder);
    }
    
    free(builder);
}

void geekir_builder_set_position(GeekIRBuilder* builder, GeekIRBasicBlock* block) {
    if (!builder || !block) {
        return;
    }
    
    LLVMPositionBuilderAtEnd(builder->llvm_builder, block->llvm_block);
}

void geekir_builder_set_position_before(GeekIRBuilder* builder, GeekIRInstruction* instr) {
    if (!builder || !instr) {
        return;
    }
    
    LLVMPositionBuilderBefore(builder->llvm_builder, instr->llvm_value);
}

void geekir_builder_set_position_after(GeekIRBuilder* builder, GeekIRInstruction* instr) {
    if (!builder || !instr) {
        return;
    }
    
    LLVMPositionBuilderAfter(builder->llvm_builder, instr->llvm_value);
}

/* Arithmetic operations */
GeekIRInstruction* geekir_builder_add(GeekIRBuilder* builder, GeekIRValue* left, GeekIRValue* right, const char* name) {
    if (!builder || !left || !right) {
        return NULL;
    }
    
    GeekIRInstruction* instruction = malloc(sizeof(GeekIRInstruction));
    if (!instruction) {
        return NULL;
    }
    
    instruction->llvm_value = LLVMBuildAdd(builder->llvm_builder, left->llvm_value, right->llvm_value, name ? name : "");
    instruction->context = builder->context;
    
    return instruction;
}

GeekIRInstruction* geekir_builder_sub(GeekIRBuilder* builder, GeekIRValue* left, GeekIRValue* right, const char* name) {
    if (!builder || !left || !right) {
        return NULL;
    }
    
    GeekIRInstruction* instruction = malloc(sizeof(GeekIRInstruction));
    if (!instruction) {
        return NULL;
    }
    
    instruction->llvm_value = LLVMBuildSub(builder->llvm_builder, left->llvm_value, right->llvm_value, name ? name : "");
    instruction->context = builder->context;
    
    return instruction;
}

GeekIRInstruction* geekir_builder_mul(GeekIRBuilder* builder, GeekIRValue* left, GeekIRValue* right, const char* name) {
    if (!builder || !left || !right) {
        return NULL;
    }
    
    GeekIRInstruction* instruction = malloc(sizeof(GeekIRInstruction));
    if (!instruction) {
        return NULL;
    }
    
    instruction->llvm_value = LLVMBuildMul(builder->llvm_builder, left->llvm_value, right->llvm_value, name ? name : "");
    instruction->context = builder->context;
    
    return instruction;
}

GeekIRInstruction* geekir_builder_div(GeekIRBuilder* builder, GeekIRValue* left, GeekIRValue* right, const char* name) {
    if (!builder || !left || !right) {
        return NULL;
    }
    
    GeekIRInstruction* instruction = malloc(sizeof(GeekIRInstruction));
    if (!instruction) {
        return NULL;
    }
    
    instruction->llvm_value = LLVMBuildSDiv(builder->llvm_builder, left->llvm_value, right->llvm_value, name ? name : "");
    instruction->context = builder->context;
    
    return instruction;
}

GeekIRInstruction* geekir_builder_rem(GeekIRBuilder* builder, GeekIRValue* left, GeekIRValue* right, const char* name) {
    if (!builder || !left || !right) {
        return NULL;
    }
    
    GeekIRInstruction* instruction = malloc(sizeof(GeekIRInstruction));
    if (!instruction) {
        return NULL;
    }
    
    instruction->llvm_value = LLVMBuildSRem(builder->llvm_builder, left->llvm_value, right->llvm_value, name ? name : "");
    instruction->context = builder->context;
    
    return instruction;
}

/* Bitwise operations */
GeekIRInstruction* geekir_builder_and(GeekIRBuilder* builder, GeekIRValue* left, GeekIRValue* right, const char* name) {
    if (!builder || !left || !right) {
        return NULL;
    }
    
    GeekIRInstruction* instruction = malloc(sizeof(GeekIRInstruction));
    if (!instruction) {
        return NULL;
    }
    
    instruction->llvm_value = LLVMBuildAnd(builder->llvm_builder, left->llvm_value, right->llvm_value, name ? name : "");
    instruction->context = builder->context;
    
    return instruction;
}

GeekIRInstruction* geekir_builder_or(GeekIRBuilder* builder, GeekIRValue* left, GeekIRValue* right, const char* name) {
    if (!builder || !left || !right) {
        return NULL;
    }
    
    GeekIRInstruction* instruction = malloc(sizeof(GeekIRInstruction));
    if (!instruction) {
        return NULL;
    }
    
    instruction->llvm_value = LLVMBuildOr(builder->llvm_builder, left->llvm_value, right->llvm_value, name ? name : "");
    instruction->context = builder->context;
    
    return instruction;
}

GeekIRInstruction* geekir_builder_xor(GeekIRBuilder* builder, GeekIRValue* left, GeekIRValue* right, const char* name) {
    if (!builder || !left || !right) {
        return NULL;
    }
    
    GeekIRInstruction* instruction = malloc(sizeof(GeekIRInstruction));
    if (!instruction) {
        return NULL;
    }
    
    instruction->llvm_value = LLVMBuildXor(builder->llvm_builder, left->llvm_value, right->llvm_value, name ? name : "");
    instruction->context = builder->context;
    
    return instruction;
}

GeekIRInstruction* geekir_builder_shl(GeekIRBuilder* builder, GeekIRValue* left, GeekIRValue* right, const char* name) {
    if (!builder || !left || !right) {
        return NULL;
    }
    
    GeekIRInstruction* instruction = malloc(sizeof(GeekIRInstruction));
    if (!instruction) {
        return NULL;
    }
    
    instruction->llvm_value = LLVMBuildShl(builder->llvm_builder, left->llvm_value, right->llvm_value, name ? name : "");
    instruction->context = builder->context;
    
    return instruction;
}

GeekIRInstruction* geekir_builder_lshr(GeekIRBuilder* builder, GeekIRValue* left, GeekIRValue* right, const char* name) {
    if (!builder || !left || !right) {
        return NULL;
    }
    
    GeekIRInstruction* instruction = malloc(sizeof(GeekIRInstruction));
    if (!instruction) {
        return NULL;
    }
    
    instruction->llvm_value = LLVMBuildLShr(builder->llvm_builder, left->llvm_value, right->llvm_value, name ? name : "");
    instruction->context = builder->context;
    
    return instruction;
}

GeekIRInstruction* geekir_builder_ashr(GeekIRBuilder* builder, GeekIRValue* left, GeekIRValue* right, const char* name) {
    if (!builder || !left || !right) {
        return NULL;
    }
    
    GeekIRInstruction* instruction = malloc(sizeof(GeekIRInstruction));
    if (!instruction) {
        return NULL;
    }
    
    instruction->llvm_value = LLVMBuildAShr(builder->llvm_builder, left->llvm_value, right->llvm_value, name ? name : "");
    instruction->context = builder->context;
    
    return instruction;
}

/* Memory operations */
GeekIRInstruction* geekir_builder_alloca(GeekIRBuilder* builder, GeekIRType* type, const char* name) {
    if (!builder || !type) {
        return NULL;
    }
    
    GeekIRInstruction* instruction = malloc(sizeof(GeekIRInstruction));
    if (!instruction) {
        return NULL;
    }
    
    instruction->llvm_value = LLVMBuildAlloca(builder->llvm_builder, type->llvm_type, name ? name : "");
    instruction->context = builder->context;
    
    return instruction;
}

GeekIRInstruction* geekir_builder_load(GeekIRBuilder* builder, GeekIRValue* pointer, const char* name) {
    if (!builder || !pointer) {
        return NULL;
    }
    
    GeekIRInstruction* instruction = malloc(sizeof(GeekIRInstruction));
    if (!instruction) {
        return NULL;
    }
    
    instruction->llvm_value = LLVMBuildLoad(builder->llvm_builder, pointer->llvm_value, name ? name : "");
    instruction->context = builder->context;
    
    return instruction;
}

GeekIRInstruction* geekir_builder_store(GeekIRBuilder* builder, GeekIRValue* value, GeekIRValue* pointer) {
    if (!builder || !value || !pointer) {
        return NULL;
    }
    
    GeekIRInstruction* instruction = malloc(sizeof(GeekIRInstruction));
    if (!instruction) {
        return NULL;
    }
    
    instruction->llvm_value = LLVMBuildStore(builder->llvm_builder, value->llvm_value, pointer->llvm_value);
    instruction->context = builder->context;
    
    return instruction;
}

GeekIRInstruction* geekir_builder_gep(GeekIRBuilder* builder, GeekIRValue* pointer, GeekIRValue** indices, size_t index_count, const char* name) {
    if (!builder || !pointer || (!indices && index_count > 0)) {
        return NULL;
    }
    
    GeekIRInstruction* instruction = malloc(sizeof(GeekIRInstruction));
    if (!instruction) {
        return NULL;
    }
    
    LLVMValueRef* llvm_indices = NULL;
    if (index_count > 0) {
        llvm_indices = malloc(index_count * sizeof(LLVMValueRef));
        if (!llvm_indices) {
            free(instruction);
            return NULL;
        }
        
        for (size_t i = 0; i < index_count; i++) {
            if (!indices[i]) {
                free(llvm_indices);
                free(instruction);
                return NULL;
            }
            llvm_indices[i] = indices[i]->llvm_value;
        }
    }
    
    instruction->llvm_value = LLVMBuildGEP(builder->llvm_builder, pointer->llvm_value, llvm_indices, (unsigned)index_count, name ? name : "");
    instruction->context = builder->context;
    
    GEEKIR_SAFE_FREE(llvm_indices);
    return instruction;
}

GeekIRInstruction* geekir_builder_inbounds_gep(GeekIRBuilder* builder, GeekIRValue* pointer, GeekIRValue** indices, size_t index_count, const char* name) {
    if (!builder || !pointer || (!indices && index_count > 0)) {
        return NULL;
    }
    
    GeekIRInstruction* instruction = malloc(sizeof(GeekIRInstruction));
    if (!instruction) {
        return NULL;
    }
    
    LLVMValueRef* llvm_indices = NULL;
    if (index_count > 0) {
        llvm_indices = malloc(index_count * sizeof(LLVMValueRef));
        if (!llvm_indices) {
            free(instruction);
            return NULL;
        }
        
        for (size_t i = 0; i < index_count; i++) {
            if (!indices[i]) {
                free(llvm_indices);
                free(instruction);
                return NULL;
            }
            llvm_indices[i] = indices[i]->llvm_value;
        }
    }
    
    instruction->llvm_value = LLVMBuildInBoundsGEP(builder->llvm_builder, pointer->llvm_value, llvm_indices, (unsigned)index_count, name ? name : "");
    instruction->context = builder->context;
    
    GEEKIR_SAFE_FREE(llvm_indices);
    return instruction;
}
