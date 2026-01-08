#include "../include/geekir.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

int test_function(void) {
    GeekIRContext* context = geekir_context_create();
    ASSERT(context != NULL, "Context creation should succeed");
    
    GeekIRModule* module = geekir_module_create(context, "test_module");
    ASSERT(module != NULL, "Module creation should succeed");
    
    // Create function type
    GeekIRType* int32_type = geekir_type_get_int32(context);
    GeekIRType* void_type = geekir_type_get_void(context);
    GeekIRType* function_type = geekir_type_get_function(int32_type, &int32_type, 1, false);
    ASSERT(function_type != NULL, "Function type creation should succeed");
    
    // Test function creation
    GeekIRFunction* function = geekir_function_create(module, function_type, "test_function");
    ASSERT(function != NULL, "Function creation should succeed");
    
    // Test function retrieval
    GeekIRFunction* retrieved_function = geekir_function_get(module, "test_function");
    ASSERT(retrieved_function != NULL, "Function retrieval should succeed");
    ASSERT(retrieved_function == function, "Retrieved function should match original");
    
    // Test non-existent function retrieval
    GeekIRFunction* non_existent = geekir_function_get(module, "non_existent");
    ASSERT(non_existent == NULL, "Non-existent function retrieval should return NULL");
    
    // Test basic block creation
    GeekIRBasicBlock* entry_block = geekir_function_append_basic_block(function, "entry");
    ASSERT(entry_block != NULL, "Basic block creation should succeed");
    
    GeekIRBasicBlock* second_block = geekir_function_append_basic_block(function, "second");
    ASSERT(second_block != NULL, "Second basic block creation should succeed");
    
    // Test entry block retrieval
    GeekIRBasicBlock* entry_retrieved = geekir_function_get_entry_block(function);
    ASSERT(entry_retrieved != NULL, "Entry block retrieval should succeed");
    ASSERT(entry_retrieved == entry_block, "Retrieved entry block should match original");
    
    // Test function return type
    GeekIRType* return_type = geekir_function_get_return_type(function);
    ASSERT(return_type != NULL, "Return type retrieval should succeed");
    
    // Test parameter count
    size_t param_count = geekir_function_get_param_count(function);
    ASSERT(param_count == 1, "Parameter count should be 1");
    
    // Test parameter retrieval
    GeekIRValue* param = geekir_function_get_param(function, 0);
    ASSERT(param != NULL, "Parameter retrieval should succeed");
    
    // Test invalid parameter index
    GeekIRValue* invalid_param = geekir_function_get_param(function, 10);
    ASSERT(invalid_param == NULL, "Invalid parameter index should return NULL");
    
    // Test null pointer handling
    GeekIRFunction* null_function = geekir_function_create(NULL, function_type, "test");
    ASSERT(null_function == NULL, "Null module should return NULL");
    
    GeekIRFunction* null_type_function = geekir_function_create(module, NULL, "test");
    ASSERT(null_type_function == NULL, "Null type should return NULL");
    
    GeekIRFunction* null_name_function = geekir_function_create(module, function_type, NULL);
    ASSERT(null_name_function == NULL, "Null name should return NULL");
    
    GeekIRFunction* null_get_function = geekir_function_get(NULL, "test");
    ASSERT(null_get_function == NULL, "Null module get should return NULL");
    
    GeekIRFunction* null_name_get = geekir_function_get(module, NULL);
    ASSERT(null_name_get == NULL, "Null name get should return NULL");
    
    GeekIRBasicBlock* null_block = geekir_function_append_basic_block(NULL, "test");
    ASSERT(null_block == NULL, "Null function append block should return NULL");
    
    GeekIRBasicBlock* null_name_block = geekir_function_append_basic_block(function, NULL);
    ASSERT(null_name_block == NULL, "Null name append block should return NULL");
    
    GeekIRBasicBlock* null_entry_block = geekir_function_get_entry_block(NULL);
    ASSERT(null_entry_block == NULL, "Null function entry block should return NULL");
    
    GeekIRType* null_return_type = geekir_function_get_return_type(NULL);
    ASSERT(null_return_type == NULL, "Null function return type should return NULL");
    
    size_t null_param_count = geekir_function_get_param_count(NULL);
    ASSERT(null_param_count == 0, "Null function param count should return 0");
    
    GeekIRValue* null_param = geekir_function_get_param(NULL, 0);
    ASSERT(null_param == NULL, "Null function get param should return NULL");
    
    geekir_module_dispose(module);
    geekir_context_dispose(context);
    
    return 1;
}
