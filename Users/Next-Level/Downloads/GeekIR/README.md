# GeekIR

A C library for LLVM IR manipulation.

GeekIR provides a C interface for creating, modifying, and analyzing LLVM Intermediate Representation. It wraps the LLVM C API to simplify common operations while maintaining access to LLVM's full capabilities.

## Integration

### Easy Integration (Recommended)

Copy `geekir.h` to your project and include it:

```c
#include "geekir.h"
```

Link against LLVM libraries:
```bash
gcc your_program.c $(llvm-config --cflags) $(llvm-config --ldflags --libs core irreader bitreader bitwriter analysis passes)
```

### CMake Integration

```cmake
find_package(LLVM REQUIRED)
target_link_libraries(your_target PRIVATE LLVMCore LLVMIRReader LLVMBitReader LLVMBitWriter LLVMAnalysis LLVMPasses LLVMTransformUtils LLVMSupport)
```

See `INTEGRATION.md` for detailed instructions.

## Quick Start

```c
#include "geekir.h"
#include <stdio.h>

int main() {
    // Create context and module
    GeekIRContext* context = geekir_context_create();
    GeekIRModule* module = geekir_module_create(context, "example");
    
    // Create types
    GeekIRType* int32_type = geekir_type_get_int32(context);
    GeekIRType* void_type = geekir_type_get_void(context);
    GeekIRType* function_type = geekir_type_get_function(void_type, &int32_type, 1, false);
    
    // Create function
    GeekIRFunction* function = geekir_function_create(module, function_type, "add_one");
    GeekIRBasicBlock* entry = geekir_function_append_basic_block(function, "entry");
    
    // Build function body
    GeekIRBuilder* builder = geekir_builder_create(context);
    geekir_builder_set_position(builder, entry);
    
    GeekIRValue* param = geekir_function_get_param(function, 0);
    GeekIRValue* const_1 = geekir_value_get_const_int(int32_type, 1, false);
    GeekIRInstruction* result = geekir_builder_add(builder, param, const_1, "result");
    geekir_builder_ret(builder, (GeekIRValue*)result);
    
    // Verify and output
    if (geekir_module_verify(module) == GEEKIR_SUCCESS) {
        char* ir_output;
        geekir_module_dump_to_string(module, &ir_output);
        printf("%s\n", ir_output);
        free(ir_output);
    }
    
    // Cleanup
    geekir_builder_dispose(builder);
    geekir_module_dispose(module);
    geekir_context_dispose(context);
    
    return 0;
}
```

## Building

### Prerequisites

- LLVM 15.0 or later
- CMake 3.15 or later
- C compiler (GCC, Clang, or MSVC)

### Build Instructions

```bash
# Clone and build
mkdir build && cd build
cmake ..
make -j$(nproc)

# Run tests
make test

# Install
sudo make install
```

### Windows Build

```cmd
mkdir build && cd build
cmake .. -G "Visual Studio 16 2019"
cmake --build . --config Release
```

## API Reference

### Core Objects

- Context: LLVM context and global state
- Module: Container for functions and globals
- Type: LLVM types (int, float, struct, etc.)
- Value: Constants and variables
- Function: Functions with parameters and basic blocks
- BasicBlock: Container for instructions
- Builder: Interface for creating instructions
- Instruction: Individual IR operations

### Key APIs

#### Context Management
```c
GeekIRContext* geekir_context_create(void);
void geekir_context_dispose(GeekIRContext* context);
```

#### Module Operations
```c
GeekIRModule* geekir_module_create(GeekIRContext* context, const char* name);
GeekIRResult geekir_module_verify(GeekIRModule* module);
GeekIRResult geekir_module_dump_to_string(GeekIRModule* module, char** output);
GeekIRResult geekir_module_write_bitcode(GeekIRModule* module, const char* filename);
```

#### Type System
```c
GeekIRType* geekir_type_get_int32(GeekIRContext* context);
GeekIRType* geekir_type_get_pointer(GeekIRType* element_type);
GeekIRType* geekir_type_get_function(GeekIRType* return_type, GeekIRType** param_types, size_t param_count, bool is_var_args);
```

#### Instruction Building
```c
GeekIRInstruction* geekir_builder_add(GeekIRBuilder* builder, GeekIRValue* left, GeekIRValue* right, const char* name);
GeekIRInstruction* geekir_builder_br(GeekIRBuilder* builder, GeekIRBasicBlock* dest);
GeekIRInstruction* geekir_builder_call(GeekIRBuilder* builder, GeekIRValue* function, GeekIRValue** args, size_t arg_count, const char* name);
```

#### Optimization
```c
GeekIRResult geekir_transform_constant_folding(GeekIRModule* module);
GeekIRResult geekir_transform_dead_code_elimination(GeekIRModule* module);
GeekIRResult geekir_transform_optimize_aggressive(GeekIRModule* module);
```

## Examples

Examples are in the `examples/` directory:

- basic_example.c: Simple IR creation
- function_example.c: Functions with control flow
- optimization_example.c: Optimization passes
- serialization_example.c: IR and bitcode I/O
- control_flow_example.c: Control flow patterns

Build examples:

```bash
cd build
make basic_example
./examples/basic_example
```

## Testing

Run tests:

```bash
cd build
make test
```

Or run tests directly:

```bash
./tests/test_runner
```

## Error Handling

All functions return `GeekIRResult` for error reporting:

```c
typedef enum {
    GEEKIR_SUCCESS = 0,
    GEEKIR_ERROR_NULL_POINTER,
    GEEKIR_ERROR_INVALID_TYPE,
    GEEKIR_ERROR_OUT_OF_MEMORY,
    GEEKIR_ERROR_PARSE_FAILED,
    GEEKIR_ERROR_VERIFICATION_FAILED,
    GEEKIR_ERROR_UNKNOWN
} GeekIRResult;
```

## Memory Management

- Create functions return owned pointers
- Dispose functions free resources
- String outputs must be freed by caller
- Objects are reference-counted internally

## Thread Safety

- Context objects are not thread-safe
- Use separate contexts per thread
- Module objects require synchronization for sharing

## License

MIT License. See LICENSE file.

## Contributing

1. Fork repository
2. Create feature branch
3. Add tests
4. Ensure tests pass
5. Submit pull request

## Version

1.0.0
