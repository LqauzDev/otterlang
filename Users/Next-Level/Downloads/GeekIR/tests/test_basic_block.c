#include "../include/geekir.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

int test_basic_block(void) {
    GeekIRContext* context = geekir_context_create();
    ASSERT(context != NULL, "Context creation should succeed");
    
    GeekIRModule* module = geekir_module_create(context, "test_module");
    ASSERT(module != NULL, "Module creation should succeed");
    
    // Create function
    GeekIRType* int32_type = geekir_type_get_int32(context);
    GeekIRType* void_type = geekir_type_get_void(context);
    GeekIRType* function_type = geekir_type_get_function(void_type, NULL, 0, false);
    
    GeekIRFunction* function = geekir_function_create(module, function_type, "test_function");
    ASSERT(function != NULL, "Function creation should succeed");
    
    // Test basic block creation
    GeekIRBasicBlock* block1 = geekir_function_append_basic_block(function, "block1");
    ASSERT(block1 != NULL, "Basic block creation should succeed");
    
    GeekIRBasicBlock* block2 = geekir_function_append_basic_block(function, "block2");
    ASSERT(block2 != NULL, "Second basic block creation should succeed");
    
    GeekIRBasicBlock* block3 = geekir_function_append_basic_block(function, "block3");
    ASSERT(block3 != NULL, "Third basic block creation should succeed");
    
    // Test standalone basic block creation
    GeekIRBasicBlock* standalone_block = geekir_basic_block_create(context, "standalone");
    ASSERT(standalone_block != NULL, "Standalone basic block creation should succeed");
    
    // Test basic block navigation
    GeekIRBasicBlock* next_block = geekir_basic_block_get_next(block1);
    ASSERT(next_block != NULL, "Getting next block should succeed");
    
    GeekIRBasicBlock* prev_block = geekir_basic_block_get_prev(block2);
    ASSERT(prev_block != NULL, "Getting previous block should succeed");
    ASSERT(prev_block == block1, "Previous block should match");
    
    // Test first/last block
    GeekIRBasicBlock* first_block = geekir_basic_block_get_prev(block1);
    ASSERT(first_block == NULL, "First block should have no previous");
    
    GeekIRBasicBlock* last_block = geekir_basic_block_get_next(block3);
    ASSERT(last_block == NULL, "Last block should have no next");
    
    // Test parent function
    GeekIRFunction* parent = geekir_basic_block_get_parent(block1);
    ASSERT(parent != NULL, "Getting parent function should succeed");
    ASSERT(parent == function, "Parent function should match");
    
    // Test instruction retrieval (empty blocks should return NULL)
    GeekIRInstruction* first_instr = geekir_basic_block_get_first_instr(block1);
    ASSERT(first_instr == NULL, "Empty block should have no first instruction");
    
    GeekIRInstruction* last_instr = geekir_basic_block_get_last_instr(block1);
    ASSERT(last_instr == NULL, "Empty block should have no last instruction");
    
    // Test null pointer handling
    GeekIRBasicBlock* null_block = geekir_basic_block_create(NULL, "test");
    ASSERT(null_block == NULL, "Null context block creation should return NULL");
    
    GeekIRBasicBlock* null_name_block = geekir_basic_block_create(context, NULL);
    ASSERT(null_name_block == NULL, "Null name block creation should return NULL");
    
    GeekIRBasicBlock* null_next = geekir_basic_block_get_next(NULL);
    ASSERT(null_next == NULL, "Null block get next should return NULL");
    
    GeekIRBasicBlock* null_prev = geekir_basic_block_get_prev(NULL);
    ASSERT(null_prev == NULL, "Null block get prev should return NULL");
    
    GeekIRFunction* null_parent = geekir_basic_block_get_parent(NULL);
    ASSERT(null_parent == NULL, "Null block get parent should return NULL");
    
    GeekIRInstruction* null_first = geekir_basic_block_get_first_instr(NULL);
    ASSERT(null_first == NULL, "Null block get first instruction should return NULL");
    
    GeekIRInstruction* null_last = geekir_basic_block_get_last_instr(NULL);
    ASSERT(null_last == NULL, "Null block get last instruction should return NULL");
    
    geekir_module_dispose(module);
    geekir_context_dispose(context);
    
    return 1;
}
