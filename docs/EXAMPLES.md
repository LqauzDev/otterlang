# Examples

This directory contains examples demonstrating various OtterLang features and use cases. Each example is designed to be self-contained and educational.

## Basic Language Features

### Core Syntax and Types

**`examples/basic/hello.ot`**
- **Purpose**: Basic "Hello, World!" program
- **Demonstrates**: Function definitions, string literals, basic output
- **Run**: `otter run examples/basic/hello.ot`

**`examples/basic/pythonic_demo.ot`**
- **Purpose**: Python-inspired programming patterns
- **Demonstrates**: List comprehensions, dynamic typing, flexible syntax
- **Run**: `otter run examples/basic/pythonic_demo.ot`

**`examples/basic/multiline_test.ot`**
- **Purpose**: Multi-line string handling
- **Demonstrates**: String concatenation, formatting, multi-line literals
- **Run**: `otter run examples/basic/multiline_test.ot`

### Data Structures

**`examples/basic/struct_demo.ot`**
- **Purpose**: Basic struct usage and manipulation
- **Demonstrates**: Struct definition, instantiation, field access
- **Run**: `otter run examples/basic/struct_demo.ot`

**`examples/basic/struct_methods_demo.ot`**
- **Purpose**: Struct methods and object-oriented patterns
- **Demonstrates**: Method definitions, self parameter, encapsulation
- **Run**: `otter run examples/basic/struct_methods_demo.ot`

### Control Flow and Algorithms

**`examples/basic/fibonacci.ot`**
- **Purpose**: Classic recursive algorithm implementation
- **Demonstrates**: Recursion, function calls, basic math operations
- **Run**: `otter run examples/basic/fibonacci.ot`

**`examples/basic/advanced_pipeline.ot`**
- **Purpose**: Complex data processing pipeline
- **Demonstrates**: Function composition, data transformation, advanced control flow
- **Run**: `otter run examples/basic/advanced_pipeline.ot`

### Error Handling

**`examples/basic/exception_basics.ot`**
- **Purpose**: Fundamental error handling with Result types
- **Demonstrates**: Result<T, E> enum, pattern matching, error recovery
- **Run**: `otter run examples/basic/exception_basics.ot`

**`examples/basic/exception_advanced.ot`**
- **Purpose**: Advanced error handling patterns
- **Demonstrates**: Nested Result handling, error chaining, error propagation
- **Run**: `otter run examples/basic/exception_advanced.ot`

**`examples/basic/exception_resource.ot`**
- **Purpose**: Resource management with error handling
- **Demonstrates**: Resource cleanup patterns, error handling with cleanup
- **Run**: `otter run examples/basic/exception_resource.ot`

**`examples/basic/exception_validation.ot`**
- **Purpose**: Data validation with error handling
- **Demonstrates**: Input validation, Result propagation, defensive programming
- **Run**: `otter run examples/basic/exception_validation.ot`

### Performance and Concurrency

**`examples/basic/task_benchmark.ot`**
- **Purpose**: Concurrent task performance benchmarking
- **Demonstrates**: Task spawning, async/await, performance measurement
- **Run**: `otter run examples/basic/task_benchmark.ot`

## Foreign Function Interface (FFI)

### Basic FFI Usage

**`examples/ffi/ffi_rand_demo.ot`**
- **Purpose**: Basic random number generation via FFI
- **Demonstrates**: Importing Rust crates, calling FFI functions, basic type conversion
- **Run**: `otter run examples/ffi/ffi_rand_demo.ot`

**`examples/ffi/ffi_rand_advanced.ot`**
- **Purpose**: Advanced FFI patterns and error handling
- **Demonstrates**: Complex FFI calls, error handling, advanced type mapping
- **Run**: `otter run examples/ffi/ffi_rand_advanced.ot`

## Running Examples

All examples can be run using the Otter CLI:

```bash
# Run directly
otter run examples/basic/hello.ot

# Build to executable first
otter build examples/basic/fibonacci.ot -o fibonacci
./fibonacci

# Build for WebAssembly
otter build examples/basic/hello.ot --target wasm32-unknown-unknown -o hello.wasm
```

## Learning Path

For new users, we recommend exploring examples in this order:

1. **Start here**: `hello.ot` → `struct_demo.ot` → `fibonacci.ot`
2. **Control flow**: `exception_basics.ot` → `advanced_pipeline.ot`
3. **Advanced features**: `task_benchmark.ot` → `pythonic_demo.ot`
4. **FFI**: `ffi_rand_demo.ot` → `ffi_rand_advanced.ot`

Each example includes comments explaining the concepts being demonstrated. For more comprehensive tutorials, see [TUTORIALS.md](TUTORIALS.md).
