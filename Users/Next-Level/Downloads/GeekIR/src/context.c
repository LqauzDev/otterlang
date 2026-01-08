#include "../include/internal/common.h"
#include <stdlib.h>
#include <string.h>

GeekIRContext* geekir_context_create(void) {
    GeekIRContext* context = calloc(1, sizeof(GeekIRContext));
    if (!context) {
        return NULL;
    }

    context->llvm_context = LLVMContextCreate();
    if (!context->llvm_context) {
        free(context);
        return NULL;
    }

    LLVMSetContextData(context->llvm_context, context);
    return context;
}

void geekir_context_dispose(GeekIRContext* context) {
    if (!context) {
        return;
    }

    if (context->llvm_context) {
        LLVMContextDispose(context->llvm_context);
    }

    GEEKIR_SAFE_FREE(context->error_message);
    free(context);
}

GeekIRResult geekir_context_set_target_triple(GeekIRContext* context, const char* triple) {
    GEEKIR_CHECK_NULL(context, NULL);
    GEEKIR_CHECK_NULL(triple, context);

    /* This will be used when creating modules */
    /* Store in context for later use */
    return GEEKIR_SUCCESS;
}

GeekIRResult geekir_context_set_data_layout(GeekIRContext* context, const char* layout) {
    GEEKIR_CHECK_NULL(context, NULL);
    GEEKIR_CHECK_NULL(layout, context);

    /* This will be used when creating modules */
    /* Store in context for later use */
    return GEEKIR_SUCCESS;
}
