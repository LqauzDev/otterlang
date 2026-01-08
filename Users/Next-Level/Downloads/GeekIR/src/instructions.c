#include "../include/internal/common.h"
#include <stdlib.h>
#include <string.h>

/* Control flow operations */
GeekIRInstruction* geekir_builder_br(GeekIRBuilder* builder, GeekIRBasicBlock* dest) {
    if (!builder || !dest) {
        return NULL;
    }
    
    GeekIRInstruction* instruction = malloc(sizeof(GeekIRInstruction));
    if (!instruction) {
        return NULL;
    }
    
    instruction->llvm_value = LLVMBuildBr(builder->llvm_builder, dest->llvm_block);
    instruction->context = builder->context;
    
    return instruction;
}

GeekIRInstruction* geekir_builder_cond_br(GeekIRBuilder* builder, GeekIRValue* condition, GeekIRBasicBlock* then_block, GeekIRBasicBlock* else_block) {
    if (!builder || !condition || !then_block || !else_block) {
        return NULL;
    }
    
    GeekIRInstruction* instruction = malloc(sizeof(GeekIRInstruction));
    if (!instruction) {
        return NULL;
    }
    
    instruction->llvm_value = LLVMBuildCondBr(builder->llvm_builder, condition->llvm_value, then_block->llvm_block, else_block->llvm_block);
    instruction->context = builder->context;
    
    return instruction;
}

GeekIRInstruction* geekir_builder_ret(GeekIRBuilder* builder, GeekIRValue* value) {
    if (!builder) {
        return NULL;
    }
    
    GeekIRInstruction* instruction = malloc(sizeof(GeekIRInstruction));
    if (!instruction) {
        return NULL;
    }
    
    instruction->llvm_value = LLVMBuildRet(builder->llvm_builder, value ? value->llvm_value : NULL);
    instruction->context = builder->context;
    
    return instruction;
}

GeekIRInstruction* geekir_builder_ret_void(GeekIRBuilder* builder) {
    if (!builder) {
        return NULL;
    }
    
    GeekIRInstruction* instruction = malloc(sizeof(GeekIRInstruction));
    if (!instruction) {
        return NULL;
    }
    
    instruction->llvm_value = LLVMBuildRetVoid(builder->llvm_builder);
    instruction->context = builder->context;
    
    return instruction;
}

GeekIRInstruction* geekir_builder_switch(GeekIRBuilder* builder, GeekIRValue* value, GeekIRBasicBlock* default_block, size_t num_cases) {
    if (!builder || !value || !default_block) {
        return NULL;
    }
    
    GeekIRInstruction* instruction = malloc(sizeof(GeekIRInstruction));
    if (!instruction) {
        return NULL;
    }
    
    instruction->llvm_value = LLVMBuildSwitch(builder->llvm_builder, value->llvm_value, default_block->llvm_block, (unsigned)num_cases);
    instruction->context = builder->context;
    
    return instruction;
}

/* Comparison operations */
GeekIRInstruction* geekir_builder_icmp_eq(GeekIRBuilder* builder, GeekIRValue* left, GeekIRValue* right, const char* name) {
    if (!builder || !left || !right) {
        return NULL;
    }
    
    GeekIRInstruction* instruction = malloc(sizeof(GeekIRInstruction));
    if (!instruction) {
        return NULL;
    }
    
    instruction->llvm_value = LLVMBuildICmp(builder->llvm_builder, LLVMIntEQ, left->llvm_value, right->llvm_value, name ? name : "");
    instruction->context = builder->context;
    
    return instruction;
}

GeekIRInstruction* geekir_builder_icmp_ne(GeekIRBuilder* builder, GeekIRValue* left, GeekIRValue* right, const char* name) {
    if (!builder || !left || !right) {
        return NULL;
    }
    
    GeekIRInstruction* instruction = malloc(sizeof(GeekIRInstruction));
    if (!instruction) {
        return NULL;
    }
    
    instruction->llvm_value = LLVMBuildICmp(builder->llvm_builder, LLVMIntNE, left->llvm_value, right->llvm_value, name ? name : "");
    instruction->context = builder->context;
    
    return instruction;
}

GeekIRInstruction* geekir_builder_icmp_slt(GeekIRBuilder* builder, GeekIRValue* left, GeekIRValue* right, const char* name) {
    if (!builder || !left || !right) {
        return NULL;
    }
    
    GeekIRInstruction* instruction = malloc(sizeof(GeekIRInstruction));
    if (!instruction) {
        return NULL;
    }
    
    instruction->llvm_value = LLVMBuildICmp(builder->llvm_builder, LLVMIntSLT, left->llvm_value, right->llvm_value, name ? name : "");
    instruction->context = builder->context;
    
    return instruction;
}

GeekIRInstruction* geekir_builder_icmp_sle(GeekIRBuilder* builder, GeekIRValue* left, GeekIRValue* right, const char* name) {
    if (!builder || !left || !right) {
        return NULL;
    }
    
    GeekIRInstruction* instruction = malloc(sizeof(GeekIRInstruction));
    if (!instruction) {
        return NULL;
    }
    
    instruction->llvm_value = LLVMBuildICmp(builder->llvm_builder, LLVMIntSLE, left->llvm_value, right->llvm_value, name ? name : "");
    instruction->context = builder->context;
    
    return instruction;
}

GeekIRInstruction* geekir_builder_icmp_sgt(GeekIRBuilder* builder, GeekIRValue* left, GeekIRValue* right, const char* name) {
    if (!builder || !left || !right) {
        return NULL;
    }
    
    GeekIRInstruction* instruction = malloc(sizeof(GeekIRInstruction));
    if (!instruction) {
        return NULL;
    }
    
    instruction->llvm_value = LLVMBuildICmp(builder->llvm_builder, LLVMIntSGT, left->llvm_value, right->llvm_value, name ? name : "");
    instruction->context = builder->context;
    
    return instruction;
}

GeekIRInstruction* geekir_builder_icmp_sge(GeekIRBuilder* builder, GeekIRValue* left, GeekIRValue* right, const char* name) {
    if (!builder || !left || !right) {
        return NULL;
    }
    
    GeekIRInstruction* instruction = malloc(sizeof(GeekIRInstruction));
    if (!instruction) {
        return NULL;
    }
    
    instruction->llvm_value = LLVMBuildICmp(builder->llvm_builder, LLVMIntSGE, left->llvm_value, right->llvm_value, name ? name : "");
    instruction->context = builder->context;
    
    return instruction;
}

GeekIRInstruction* geekir_builder_icmp_ult(GeekIRBuilder* builder, GeekIRValue* left, GeekIRValue* right, const char* name) {
    if (!builder || !left || !right) {
        return NULL;
    }
    
    GeekIRInstruction* instruction = malloc(sizeof(GeekIRInstruction));
    if (!instruction) {
        return NULL;
    }
    
    instruction->llvm_value = LLVMBuildICmp(builder->llvm_builder, LLVMIntULT, left->llvm_value, right->llvm_value, name ? name : "");
    instruction->context = builder->context;
    
    return instruction;
}

GeekIRInstruction* geekir_builder_icmp_ule(GeekIRBuilder* builder, GeekIRValue* left, GeekIRValue* right, const char* name) {
    if (!builder || !left || !right) {
        return NULL;
    }
    
    GeekIRInstruction* instruction = malloc(sizeof(GeekIRInstruction));
    if (!instruction) {
        return NULL;
    }
    
    instruction->llvm_value = LLVMBuildICmp(builder->llvm_builder, LLVMIntULE, left->llvm_value, right->llvm_value, name ? name : "");
    instruction->context = builder->context;
    
    return instruction;
}

GeekIRInstruction* geekir_builder_icmp_ugt(GeekIRBuilder* builder, GeekIRValue* left, GeekIRValue* right, const char* name) {
    if (!builder || !left || !right) {
        return NULL;
    }
    
    GeekIRInstruction* instruction = malloc(sizeof(GeekIRInstruction));
    if (!instruction) {
        return NULL;
    }
    
    instruction->llvm_value = LLVMBuildICmp(builder->llvm_builder, LLVMIntUGT, left->llvm_value, right->llvm_value, name ? name : "");
    instruction->context = builder->context;
    
    return instruction;
}

GeekIRInstruction* geekir_builder_icmp_uge(GeekIRBuilder* builder, GeekIRValue* left, GeekIRValue* right, const char* name) {
    if (!builder || !left || !right) {
        return NULL;
    }
    
    GeekIRInstruction* instruction = malloc(sizeof(GeekIRInstruction));
    if (!instruction) {
        return NULL;
    }
    
    instruction->llvm_value = LLVMBuildICmp(builder->llvm_builder, LLVMIntUGE, left->llvm_value, right->llvm_value, name ? name : "");
    instruction->context = builder->context;
    
    return instruction;
}

/* Conversion operations */
GeekIRInstruction* geekir_builder_trunc(GeekIRBuilder* builder, GeekIRValue* value, GeekIRType* dest_type, const char* name) {
    if (!builder || !value || !dest_type) {
        return NULL;
    }
    
    GeekIRInstruction* instruction = malloc(sizeof(GeekIRInstruction));
    if (!instruction) {
        return NULL;
    }
    
    instruction->llvm_value = LLVMBuildTrunc(builder->llvm_builder, value->llvm_value, dest_type->llvm_type, name ? name : "");
    instruction->context = builder->context;
    
    return instruction;
}

GeekIRInstruction* geekir_builder_zext(GeekIRBuilder* builder, GeekIRValue* value, GeekIRType* dest_type, const char* name) {
    if (!builder || !value || !dest_type) {
        return NULL;
    }
    
    GeekIRInstruction* instruction = malloc(sizeof(GeekIRInstruction));
    if (!instruction) {
        return NULL;
    }
    
    instruction->llvm_value = LLVMBuildZExt(builder->llvm_builder, value->llvm_value, dest_type->llvm_type, name ? name : "");
    instruction->context = builder->context;
    
    return instruction;
}

GeekIRInstruction* geekir_builder_sext(GeekIRBuilder* builder, GeekIRValue* value, GeekIRType* dest_type, const char* name) {
    if (!builder || !value || !dest_type) {
        return NULL;
    }
    
    GeekIRInstruction* instruction = malloc(sizeof(GeekIRInstruction));
    if (!instruction) {
        return NULL;
    }
    
    instruction->llvm_value = LLVMBuildSExt(builder->llvm_builder, value->llvm_value, dest_type->llvm_type, name ? name : "");
    instruction->context = builder->context;
    
    return instruction;
}

GeekIRInstruction* geekir_builder_fptoui(GeekIRBuilder* builder, GeekIRValue* value, GeekIRType* dest_type, const char* name) {
    if (!builder || !value || !dest_type) {
        return NULL;
    }
    
    GeekIRInstruction* instruction = malloc(sizeof(GeekIRInstruction));
    if (!instruction) {
        return NULL;
    }
    
    instruction->llvm_value = LLVMBuildFPToUI(builder->llvm_builder, value->llvm_value, dest_type->llvm_type, name ? name : "");
    instruction->context = builder->context;
    
    return instruction;
}

GeekIRInstruction* geekir_builder_fptosi(GeekIRBuilder* builder, GeekIRValue* value, GeekIRType* dest_type, const char* name) {
    if (!builder || !value || !dest_type) {
        return NULL;
    }
    
    GeekIRInstruction* instruction = malloc(sizeof(GeekIRInstruction));
    if (!instruction) {
        return NULL;
    }
    
    instruction->llvm_value = LLVMBuildFPToSI(builder->llvm_builder, value->llvm_value, dest_type->llvm_type, name ? name : "");
    instruction->context = builder->context;
    
    return instruction;
}

GeekIRInstruction* geekir_builder_uitofp(GeekIRBuilder* builder, GeekIRValue* value, GeekIRType* dest_type, const char* name) {
    if (!builder || !value || !dest_type) {
        return NULL;
    }
    
    GeekIRInstruction* instruction = malloc(sizeof(GeekIRInstruction));
    if (!instruction) {
        return NULL;
    }
    
    instruction->llvm_value = LLVMBuildUIToFP(builder->llvm_builder, value->llvm_value, dest_type->llvm_type, name ? name : "");
    instruction->context = builder->context;
    
    return instruction;
}

GeekIRInstruction* geekir_builder_sitofp(GeekIRBuilder* builder, GeekIRValue* value, GeekIRType* dest_type, const char* name) {
    if (!builder || !value || !dest_type) {
        return NULL;
    }
    
    GeekIRInstruction* instruction = malloc(sizeof(GeekIRInstruction));
    if (!instruction) {
        return NULL;
    }
    
    instruction->llvm_value = LLVMBuildSIToFP(builder->llvm_builder, value->llvm_value, dest_type->llvm_type, name ? name : "");
    instruction->context = builder->context;
    
    return instruction;
}

GeekIRInstruction* geekir_builder_fptrunc(GeekIRBuilder* builder, GeekIRValue* value, GeekIRType* dest_type, const char* name) {
    if (!builder || !value || !dest_type) {
        return NULL;
    }
    
    GeekIRInstruction* instruction = malloc(sizeof(GeekIRInstruction));
    if (!instruction) {
        return NULL;
    }
    
    instruction->llvm_value = LLVMBuildFPTrunc(builder->llvm_builder, value->llvm_value, dest_type->llvm_type, name ? name : "");
    instruction->context = builder->context;
    
    return instruction;
}

GeekIRInstruction* geekir_builder_fpext(GeekIRBuilder* builder, GeekIRValue* value, GeekIRType* dest_type, const char* name) {
    if (!builder || !value || !dest_type) {
        return NULL;
    }
    
    GeekIRInstruction* instruction = malloc(sizeof(GeekIRInstruction));
    if (!instruction) {
        return NULL;
    }
    
    instruction->llvm_value = LLVMBuildFPExt(builder->llvm_builder, value->llvm_value, dest_type->llvm_type, name ? name : "");
    instruction->context = builder->context;
    
    return instruction;
}

/* Function call operations */
GeekIRInstruction* geekir_builder_call(GeekIRBuilder* builder, GeekIRValue* function, GeekIRValue** args, size_t arg_count, const char* name) {
    if (!builder || !function || (!args && arg_count > 0)) {
        return NULL;
    }
    
    GeekIRInstruction* instruction = malloc(sizeof(GeekIRInstruction));
    if (!instruction) {
        return NULL;
    }
    
    LLVMValueRef* llvm_args = NULL;
    if (arg_count > 0) {
        llvm_args = malloc(arg_count * sizeof(LLVMValueRef));
        if (!llvm_args) {
            free(instruction);
            return NULL;
        }
        
        for (size_t i = 0; i < arg_count; i++) {
            if (!args[i]) {
                free(llvm_args);
                free(instruction);
                return NULL;
            }
            llvm_args[i] = args[i]->llvm_value;
        }
    }
    
    instruction->llvm_value = LLVMBuildCall(builder->llvm_builder, function->llvm_value, llvm_args, (unsigned)arg_count, name ? name : "");
    instruction->context = builder->context;
    
    GEEKIR_SAFE_FREE(llvm_args);
    return instruction;
}
