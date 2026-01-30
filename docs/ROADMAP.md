# OtterLang Roadmap

Remaining work for v0.1 release.

## High Priority

### Language & Type System
- **`await` grammar**: Support awaiting stored handles (currently only direct calls)
- **Traits/polymorphism**: Implement trait system
- **Iterator abstraction**: Add iterator trait for custom collections

## Recent Additions

- **Function-level generics**: `fn` declarations now accept generic parameters; generics participate in type checking and inference across the compiler and standard library.

### Runtime & Codegen
- **`await` return values**: Currently returns Unit, should return task result
- **`spawn` context cleanup**: Free captured variables when tasks complete
- **Hot JIT optimization**: Implement function recompilation or remove unused code
- **FFI expansion**: Better binding support for complex Rust crates
- **Task runtime**: Add cancellation, timeouts, structured concurrency

### Memory Management
- **GC cycle detection**: Reference counting lacks cycle detection
- **Generational promotion**: Promotion logic incomplete

## Medium Priority

### Language & Type System
- **Type checker workspace**: Integrate into CLI/LSP for cross-file diagnostics
- **Pattern matching guards**: Add `case Foo if cond` support
- **Map iteration**: Currently not supported in `for` loops

### Runtime & Codegen
- **Iterator coverage**: Enable user-defined collections in `for` loops

### Tooling
- **LSP improvements**: Module-aware index, workspace symbols, go-to-definition
