# OtterLang Project Structure

## Overview
OtterLang is an experimental indentation-sensitive programming language with a hybrid runtime system that combines static compilation and JIT execution for optimal performance.

## Directory Structure

```
otterlang/
├── src/
│   ├── main.rs                 # Entry point
│   ├── lib.rs                  # Library root
│   ├── cli.rs                  # CLI command handling
│   │
│   ├── lexer/                  # Lexical analysis
│   │   ├── mod.rs
│   │   ├── token.rs           # Token definitions
│   │   └── tokenizer.rs       # Tokenizer implementation
│   │
│   ├── parser/                 # Syntax parsing
│   │   ├── mod.rs
│   │   └── grammar.rs         # Chumsky-based grammar
│   │
│   ├── ast/                    # Abstract Syntax Tree
│   │   ├── mod.rs
│   │   └── nodes.rs           # AST node definitions
│   │
│   ├── codegen/                # Code generation
│   │   ├── mod.rs
│   │   ├── llvm.rs            # LLVM static codegen
│   │   └── symbols.rs         # Symbol management
│   │
│   ├── runtime/                # Runtime system
│   │   ├── mod.rs
│   │   ├── ffi.rs             # FFI support
│   │   ├── ffi_api.rs         # FFI API definitions
│   │   ├── symbol_registry.rs # Runtime symbol registry
│   │   ├── strings.rs         # String runtime
│   │   │
│   │   ├── jit/               # ⭐ NEW: JIT Runtime System
│   │   │   ├── mod.rs         # JIT runtime module root
│   │   │   ├── engine.rs      # LLVM ORC JIT engine
│   │   │   ├── compiler.rs    # JIT compiler
│   │   │   ├── executor.rs    # Code executor
│   │   │   │
│   │   │   ├── profiler/      # Runtime profiling
│   │   │   │   ├── mod.rs
│   │   │   │   ├── call_profiler.rs    # Function call profiling
│   │   │   │   ├── hot_detector.rs     # Hot function detection
│   │   │   │   └── sampler.rs          # Sampling profiler
│   │   │   │
│   │   │   ├── specialization/ # JIT specialization
│   │   │   │   ├── mod.rs
│   │   │   │   ├── key.rs             # Specialization keys
│   │   │   │   ├── type_tracker.rs    # Runtime type tracking
│   │   │   │   ├── constant_prop.rs   # Constant propagation
│   │   │   │   └── specializer.rs     # Specialization engine
│   │   │   │
│   │   │   ├── optimization/  # In-memory optimization
│   │   │   │   ├── mod.rs
│   │   │   │   ├── inliner.rs         # Function inlining
│   │   │   │   ├── reoptimizer.rs     # Re-optimization passes
│   │   │   │   └── call_graph.rs      # Call graph analysis
│   │   │   │
│   │   │   ├── cache/         # Function caching
│   │   │   │   ├── mod.rs
│   │   │   │   ├── function_cache.rs  # Compiled function cache
│   │   │   │   ├── eviction.rs        # Cache eviction policies
│   │   │   │   └── metadata.rs        # Cache metadata
│   │   │   │
│   │   │   └── adaptive/      # Adaptive management
│   │   │       ├── mod.rs
│   │   │       ├── memory.rs          # Adaptive memory management
│   │   │       └── concurrency.rs    # Adaptive concurrency
│   │   │
│   │   └── stdlib/            # Standard library
│   │       ├── mod.rs
│   │       ├── io.rs
│   │       ├── math.rs
│   │       ├── sys.rs
│   │       └── time.rs
│   │
│   ├── cache/                  # Compilation cache
│   │   ├── mod.rs
│   │   ├── manager.rs         # Cache manager
│   │   ├── metadata.rs        # Cache metadata
│   │   └── path.rs            # Cache path utilities
│   │
│   ├── ffi/                    # Foreign Function Interface
│   │   ├── mod.rs
│   │   ├── cargo_bridge.rs    # Cargo bridge generation
│   │   ├── dynamic_loader.rs  # Dynamic library loading
│   │   ├── metadata.rs        # FFI metadata
│   │   ├── rust_stubgen.rs    # Rust stub generation
│   │   └── symbol_registry.rs # FFI symbol registry
│   │
│   └── utils/                  # Utilities
│       ├── mod.rs
│       ├── bench.rs           # Benchmarking utilities
│       ├── errors.rs          # Error handling
│       ├── logger.rs          # Logging
│       ├── profiler.rs        # Compilation profiler
│       └── timer.rs           # Timing utilities
│
├── examples/                   # Example programs
├── tests/                     # Test suite
├── ffi/                       # FFI bridge definitions
│
├── plan.md                    # Implementation plan
├── structure.md               # This file
├── README.md                  # Project readme
├── PROGRESS.md                # Development progress
├── IMPROVEMENTS.md            # Improvement ideas
└── Cargo.toml                 # Cargo manifest

```

## Module Relationships

### Compilation Pipeline
1. **lexer** → Tokenizes source code
2. **parser** → Builds AST from tokens
3. **codegen** → Generates LLVM IR (static) or JIT code (runtime)
4. **runtime/jit** → Executes JIT-compiled code

### Runtime System
- **runtime/jit/engine**: Core JIT execution engine
- **runtime/jit/profiler**: Profiles execution to detect hot functions
- **runtime/jit/specialization**: Specializes functions based on runtime data
- **runtime/jit/optimization**: Optimizes hot paths through inlining
- **runtime/jit/cache**: Caches compiled function code
- **runtime/jit/adaptive**: Adapts memory and concurrency usage

### Cache System
- **cache**: Static compilation cache (file-based)
- **runtime/jit/cache**: Runtime function cache (in-memory)

## Key Design Decisions

### JIT vs Static Compilation
- **Static**: Full program compilation to binary (existing)
- **JIT**: On-demand compilation and execution (new)
- **Hybrid**: Start with JIT, compile hot paths statically (future)

### Hot Function Detection
- Call counter threshold (configurable, default: 1000 calls)
- Time-based threshold (default: 5% of total execution time)
- Sampling interval (default: every 100 calls)

### Specialization Strategy
- Type specialization: per-call-site type combinations
- Constant specialization: propagate known constants
- Limited specialization: avoid code bloat (max 10 versions per function)

### Caching Strategy
- In-memory cache: for runtime reuse
- Persistent cache: for cross-run reuse (future)
- LRU eviction: when memory limit reached
- Size limit: configurable (default: 256MB)

### Memory Management
- Profile-driven allocation: track per-function allocations
- Adaptive pooling: pool common allocation sizes
- Pressure-based cleanup: trigger cleanup under memory pressure

### Concurrency
- Work-stealing scheduler: for parallel execution
- Adaptive thread pool: size based on workload
- Profile-guided parallelism: identify parallel opportunities

## Extension Points

### Adding New Profiling Metrics
Extend `runtime/jit/profiler` modules with new metric types.

### Adding New Specialization Strategies
Extend `runtime/jit/specialization/specializer.rs` with new strategies.

### Adding New Optimization Passes
Extend `runtime/jit/optimization/reoptimizer.rs` with new passes.

### Adding New Cache Policies
Extend `runtime/jit/cache/eviction.rs` with new eviction policies.

