#include "../include/geekir.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

int test_values(void) {
    GeekIRContext* context = geekir_context_create();
    ASSERT(context != NULL, "Context creation should succeed");
    
    // Test integer constants
    GeekIRType* int32_type = geekir_type_get_int32(context);
    GeekIRValue* int_const = geekir_value_get_const_int(int32_type, 42, false);
    ASSERT(int_const != NULL, "Integer constant creation should succeed");
    
    GeekIRValue* signed_int_const = geekir_value_get_const_int(int32_type, -42, true);
    ASSERT(signed_int_const != NULL, "Signed integer constant creation should succeed");
    
    // Test floating point constants
    GeekIRType* double_type = geekir_type_get_double(context);
    GeekIRValue* float_const = geekir_value_get_const_float(double_type, 3.14159);
    ASSERT(float_const != NULL, "Float constant creation should succeed");
    
    // Test special constants
    GeekIRValue* null_const = geekir_value_get_const_null(int32_type);
    ASSERT(null_const != NULL, "Null constant creation should succeed");
    
    GeekIRValue* undef_const = geekir_value_get_const_undef(int32_type);
    ASSERT(undef_const != NULL, "Undef constant creation should succeed");
    
    GeekIRValue* zero_const = geekir_value_get_const_zero(int32_type);
    ASSERT(zero_const != NULL, "Zero constant creation should succeed");
    
    // Test string constant
    GeekIRValue* string_const = geekir_value_get_const_string(context, "Hello, World!", 13);
    ASSERT(string_const != NULL, "String constant creation should succeed");
    
    // Test GEP constant
    GeekIRType* int32_ptr_type = geekir_type_get_pointer(int32_type);
    GeekIRValue* pointer_const = geekir_value_get_const_null(int32_ptr_type);
    GeekIRValue* index_const = geekir_value_get_const_int(int32_type, 0, false);
    GeekIRValue* indices[] = { index_const };
    
    GeekIRValue* gep_const = geekir_value_get_const_gep(pointer_const, indices, 1);
    ASSERT(gep_const != NULL, "GEP constant creation should succeed");
    
    // Test value type
    GeekIRType* value_type = geekir_value_get_type(int_const);
    ASSERT(value_type != NULL, "Getting value type should succeed");
    
    // Test constant check
    bool is_const = geekir_value_is_const(int_const);
    ASSERT(is_const == true, "Integer constant should be constant");
    
    // Test null pointer handling
    GeekIRValue* null_int_const = geekir_value_get_const_int(NULL, 42, false);
    ASSERT(null_int_const == NULL, "Null type should return NULL");
    
    GeekIRType* null_type = geekir_value_get_type(NULL);
    ASSERT(null_type == NULL, "Null value should return NULL");
    
    bool null_is_const = geekir_value_is_const(NULL);
    ASSERT(null_is_const == false, "Null value should not be constant");
    
    // Test value to string
    const char* value_string = geekir_value_to_string(int_const);
    ASSERT(value_string != NULL, "Value to string should succeed");
    ASSERT(strlen(value_string) > 0, "Value string should not be empty");
    
    geekir_context_dispose(context);
    
    return 1;
}
