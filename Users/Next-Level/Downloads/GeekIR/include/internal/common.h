#ifndef GEEKIR_INTERNAL_COMMON_H
#define GEEKIR_INTERNAL_COMMON_H

#include "geekir.h"
#include <llvm-c/Core.h>
#include <llvm-c/IRReader.h>
#include <llvm-c/BitReader.h>
#include <llvm-c/BitWriter.h>
#include <llvm-c/Analysis.h>
#include <llvm-c/Transforms/Scalar.h>
#include <llvm-c/Transforms/Utils.h>
#include <llvm-c/Target.h>
#include <llvm-c/TargetMachine.h>

/* Internal structure definitions */
struct GeekIRContext {
    LLVMContextRef llvm_context;
    char* error_message;
};

struct GeekIRModule {
    LLVMModuleRef llvm_module;
    GeekIRContext* context;
};

struct GeekIRType {
    LLVMTypeRef llvm_type;
    GeekIRContext* context;
};

struct GeekIRValue {
    LLVMValueRef llvm_value;
    GeekIRContext* context;
};

struct GeekIRInstruction {
    LLVMValueRef llvm_value;
    GeekIRContext* context;
};

struct GeekIRBasicBlock {
    LLVMBasicBlockRef llvm_block;
    GeekIRContext* context;
};

struct GeekIRFunction {
    LLVMValueRef llvm_value;
    GeekIRContext* context;
};

struct GeekIRBuilder {
    LLVMBuilderRef llvm_builder;
    GeekIRContext* context;
};

struct GeekIRAnalysis {
    GeekIRModule* module;
};

/* Internal utility functions */
static inline GeekIRContext* geekir_context_from_llvm(LLVMContextRef llvm_ctx) {
    return (GeekIRContext*)LLVMGetContextData(llvm_ctx);
}

static inline void geekir_set_error(GeekIRContext* context, const char* message) {
    if (context && context->error_message) {
        free(context->error_message);
    }
    if (context && message) {
        context->error_message = strdup(message);
    }
}

static inline const char* geekir_get_error(GeekIRContext* context) {
    return context ? context->error_message : NULL;
}

/* Error handling macros */
#define GEEKIR_CHECK_NULL(ptr, context) do { \
    if (!(ptr)) { \
        geekir_set_error(context, "Null pointer argument"); \
        return GEEKIR_ERROR_NULL_POINTER; \
    } \
} while(0)

#define GEEKIR_CHECK_LLVM_ERROR(context) do { \
    if (LLVMGetErrorType(LLVMGetLastError()) != LLVMNoError) { \
        geekir_set_error(context, LLVMGetErrorMessage(LLVMGetLastError())); \
        return GEEKIR_ERROR_UNKNOWN; \
    } \
} while(0)

/* Memory management helpers */
#define GEEKIR_SAFE_FREE(ptr) do { \
    if (ptr) { \
        free(ptr); \
        ptr = NULL; \
    } \
} while(0)

/* String utilities */
char* geekir_strdup(const char* str);
char* geekir_format_string(const char* format, ...);

#endif /* GEEKIR_INTERNAL_COMMON_H */
