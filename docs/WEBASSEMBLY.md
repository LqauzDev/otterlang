# WebAssembly Support

OtterLang can compile programs to WebAssembly (WASM) for running in web browsers or other WASM runtimes.

## Quick Start

Compile any OtterLang program to WebAssembly:

```bash
# Basic WebAssembly (no WASI)
otter build program.ot --target wasm32-unknown-unknown -o program.wasm

# WebAssembly with WASI support
otter build program.ot --target wasm32-wasi -o program.wasm
```

## Requirements

- **LLVM 18** with WebAssembly target support
- **`clang`** and **`wasm-ld`** in your PATH (included with LLVM installations)
- For development, ensure your LLVM build includes WebAssembly backends

## Target Differences

### `wasm32-wasi` - WebAssembly System Interface

**Best for**: Server-side WASM, command-line tools, WASI-compatible runtimes

- **Full WASI support**: Direct access to stdio, filesystem, networking, and other system APIs
- **Self-contained**: No external host imports required
- **Runtime compatibility**: Works in any WASI-compatible runtime (wasmtime, WasmEdge, etc.)
- **Size**: Slightly larger binaries due to WASI runtime

### `wasm32-unknown-unknown` - Bare WebAssembly

**Best for**: Web browsers, embedded systems, custom host environments

- **Minimal imports**: Only requires a few host functions for I/O
- **Smaller binaries**: No WASI runtime overhead
- **Flexible**: Host can implement I/O however it wants
- **Browser compatible**: Can run directly in web browsers with appropriate host

- `env.otter_write_stdout(ptr: i32, len: i32)` – write UTF-8 data to stdout
- `env.otter_write_stderr(ptr: i32, len: i32)` – write UTF-8 data to stderr
- `env.otter_time_now_ms() -> i64` – optional wall-clock timestamp in ms

## JavaScript Host Example

A tiny JavaScript host that wires these up under Node.js looks like:

```js
import fs from 'node:fs';

const memory = new WebAssembly.Memory({ initial: 8 });
const decoder = new TextDecoder();

const env = {
  memory,
  otter_write_stdout(ptr, len) {
    const bytes = new Uint8Array(memory.buffer, ptr, len);
    process.stdout.write(decoder.decode(bytes));
  },
  otter_write_stderr(ptr, len) {
    const bytes = new Uint8Array(memory.buffer, ptr, len);
    process.stderr.write(decoder.decode(bytes));
  },
  otter_time_now_ms() {
    return BigInt(Date.now());
  },
};

const { instance } = await WebAssembly.instantiate(fs.readFileSync('program.wasm'), { env });
instance.exports.main?.();
```

## Runtime Compatibility

### WASI Runtimes (`wasm32-wasi`)

- **wasmtime**: Fast runtime with CLI tools
- **WasmEdge**: High-performance runtime
- **Wasmer**: Universal WASM runtime
- **Node.js (experimental)**: With WASI support

### Custom Host Runtimes (`wasm32-unknown-unknown`)

- **Web browsers**: Chrome, Firefox, Safari, Edge
- **Node.js**: With custom host interface
- **Deno**: With WebAssembly support
- **Custom applications**: Any WASM runtime with host functions

## Limitations

- **Garbage Collection**: WASM modules use OtterLang's built-in GC, which may have different performance characteristics than native execution
- **FFI**: Foreign function interface is limited in WASM environments
- **File I/O**: Direct filesystem access requires WASI or host-provided APIs
- **Concurrency**: Task spawning works but may have limitations in constrained environments

## Examples

See the examples directory for WebAssembly-specific demos:

```bash
# Build examples for WebAssembly
otter build examples/basic/hello.ot --target wasm32-unknown-unknown -o hello.wasm
otter build examples/basic/fibonacci.ot --target wasm32-wasi -o fibonacci.wasm

# Run with wasmtime (WASI)
wasmtime fibonacci.wasm
```
