# GeekIR Integration Guide

## Quick Integration

### Option 1: Single Header (Easiest)

1. Copy `geekir.h` to your project
2. Include it in your source files
3. Link against LLVM libraries

```c
#include "geekir.h"

int main() {
    GeekIRContext* ctx = geekir_context_create();
    // Use GeekIR...
    geekir_context_dispose(ctx);
    return 0;
}
```

### Option 2: Add to Existing CMake Project

Add to your `CMakeLists.txt`:

```cmake
# Find LLVM
find_package(LLVM REQUIRED CONFIG)

# Add GeekIR header
target_include_directories(your_target PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# Link LLVM libraries
target_link_libraries(your_target PRIVATE 
    LLVMCore 
    LLVMIRReader 
    LLVMBitReader 
    LLVMBitWriter 
    LLVMAnalysis 
    LLVMPasses 
    LLVMTransformUtils 
    LLVMSupport
)
```

### Option 3: Makefile Integration

```makefile
# LLVM configuration (adjust paths as needed)
LLVM_CONFIG = llvm-config
LLVM_CFLAGS = $(shell $(LLVM_CONFIG) --cflags)
LLVM_LDFLAGS = $(shell $(LLVM_CONFIG) --ldflags --libs core irreader bitreader bitwriter analysis passes transformutils support)

# Your project
CFLAGS = -Wall -Wextra $(LLVM_CFLAGS)
LDFLAGS = $(LLVM_LDFLAGS)

your_program: your_program.o
	$(CC) -o $@ $^ $(LDFLAGS)

your_program.o: your_program.c geekir.h
	$(CC) $(CFLAGS) -c $< -o $@
```

## Required LLVM Libraries

Make sure to link these LLVM libraries:

- `LLVMCore` - Core LLVM functionality
- `LLVMIRReader` - IR parsing
- `LLVMBitReader` - Bitcode reading
- `LLVMBitWriter` - Bitcode writing
- `LLVMAnalysis` - Analysis passes
- `LLVMPasses` - Optimization passes
- `LLVMTransformUtils` - Transformation utilities
- `LLVMSupport` - Support utilities

## Minimal Example

```c
#include "geekir.h"
#include <stdio.h>

int main() {
    // Create context and module
    GeekIRContext* ctx = geekir_context_create();
    GeekIRModule* mod = geekir_module_create(ctx, "example");
    
    // Create a simple function
    GeekIRType* int32 = geekir_type_get_int32(ctx);
    GeekIRType* void_type = geekir_type_get_void(ctx);
    GeekIRType* func_type = geekir_type_get_function(void_type, &int32, 1, false);
    
    GeekIRFunction* func = geekir_function_create(mod, func_type, "add_one");
    GeekIRBasicBlock* entry = geekir_function_append_basic_block(func, "entry");
    
    // Build function body
    GeekIRBuilder* builder = geekir_builder_create(ctx);
    geekir_builder_set_position(builder, entry);
    
    GeekIRValue* param = geekir_function_get_param(func, 0);
    GeekIRValue* const_one = geekir_value_get_const_int(int32, 1, false);
    GeekIRInstruction* result = geekir_builder_add(builder, param, const_one, "result");
    geekir_builder_ret(builder, (GeekIRValue*)result);
    
    // Output IR
    char* ir;
    if (geekir_module_dump_to_string(mod, &ir) == GEEKIR_SUCCESS) {
        printf("%s\n", ir);
        free(ir);
    }
    
    // Cleanup
    geekir_builder_dispose(builder);
    geekir_module_dispose(mod);
    geekir_context_dispose(ctx);
    
    return 0;
}
```

## Compiler Requirements

- LLVM 15.0 or later
- C99 compatible compiler
- Standard library

## Platform Notes

### Linux/macOS
Use `llvm-config` to get compiler flags:
```bash
gcc -c your_program.c $(llvm-config --cflags)
gcc -o your_program your_program.o $(llvm-config --ldflags --libs core irreader bitreader bitwriter analysis passes)
```

### Windows
Add LLVM include and library directories to your project settings, then link the required .lib files.

### Existing LLVM Projects
If you already use LLVM in your project, just add `geekir.h` to your includes and you're ready to go.

## Troubleshooting

**Undefined references**: Make sure all required LLVM libraries are linked.

**LLVM not found**: Ensure LLVM development packages are installed and LLVM_CONFIG points to the correct version.

**Compilation errors**: Check that your LLVM version is 15.0 or later.
