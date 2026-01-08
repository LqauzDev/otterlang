#include "../include/geekir.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

int test_types(void) {
    GeekIRContext* context = geekir_context_create();
    ASSERT(context != NULL, "Context creation should succeed");
    
    // Test primitive types
    GeekIRType* void_type = geekir_type_get_void(context);
    ASSERT(void_type != NULL, "Void type creation should succeed");
    
    GeekIRType* int1_type = geekir_type_get_int1(context);
    ASSERT(int1_type != NULL, "Int1 type creation should succeed");
    
    GeekIRType* int8_type = geekir_type_get_int8(context);
    ASSERT(int8_type != NULL, "Int8 type creation should succeed");
    
    GeekIRType* int16_type = geekir_type_get_int16(context);
    ASSERT(int16_type != NULL, "Int16 type creation should succeed");
    
    GeekIRType* int32_type = geekir_type_get_int32(context);
    ASSERT(int32_type != NULL, "Int32 type creation should succeed");
    
    GeekIRType* int64_type = geekir_type_get_int64(context);
    ASSERT(int64_type != NULL, "Int64 type creation should succeed");
    
    GeekIRType* float_type = geekir_type_get_float(context);
    ASSERT(float_type != NULL, "Float type creation should succeed");
    
    GeekIRType* double_type = geekir_type_get_double(context);
    ASSERT(double_type != NULL, "Double type creation should succeed");
    
    // Test pointer type
    GeekIRType* int32_ptr_type = geekir_type_get_pointer(int32_type);
    ASSERT(int32_ptr_type != NULL, "Pointer type creation should succeed");
    
    // Test array type
    GeekIRType* array_type = geekir_type_get_array(int32_type, 10);
    ASSERT(array_type != NULL, "Array type creation should succeed");
    
    // Test vector type
    GeekIRType* vector_type = geekir_type_get_vector(int32_type, 4);
    ASSERT(vector_type != NULL, "Vector type creation should succeed");
    
    // Test function type
    GeekIRType* param_types[] = { int32_type, int64_type };
    GeekIRType* function_type = geekir_type_get_function(int32_type, param_types, 2, false);
    ASSERT(function_type != NULL, "Function type creation should succeed");
    
    // Test varargs function type
    GeekIRType* varargs_function_type = geekir_type_get_function(void_type, param_types, 2, true);
    ASSERT(varargs_function_type != NULL, "Varargs function type creation should succeed");
    
    // Test struct type
    GeekIRType* struct_types[] = { int32_type, float_type, double_type };
    GeekIRType* struct_type = geekir_type_get_struct(context, struct_types, 3, false);
    ASSERT(struct_type != NULL, "Struct type creation should succeed");
    
    // Test packed struct type
    GeekIRType* packed_struct_type = geekir_type_get_struct(context, struct_types, 3, true);
    ASSERT(packed_struct_type != NULL, "Packed struct type creation should succeed");
    
    // Test null pointer handling
    GeekIRType* null_ptr_type = geekir_type_get_pointer(NULL);
    ASSERT(null_ptr_type == NULL, "Null pointer type should return NULL");
    
    GeekIRType* null_array_type = geekir_type_get_array(NULL, 10);
    ASSERT(null_array_type == NULL, "Null array type should return NULL");
    
    GeekIRType* null_function_type = geekir_type_get_function(NULL, NULL, 0, false);
    ASSERT(null_function_type == NULL, "Null function type should return NULL");
    
    GeekIRType* null_struct_type = geekir_type_get_struct(NULL, NULL, 0, false);
    ASSERT(null_struct_type == NULL, "Null struct type should return NULL");
    
    // Test type to string
    const char* type_string = geekir_type_to_string(int32_type);
    ASSERT(type_string != NULL, "Type to string should succeed");
    ASSERT(strlen(type_string) > 0, "Type string should not be empty");
    
    geekir_context_dispose(context);
    
    return 1;
}
