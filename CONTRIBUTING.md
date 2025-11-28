# Contributing to OtterLang

Thanks for helping shape OtterLang! This guide covers setup, workflow expectations, and contribution tips.

## Development Setup

### Option 1: `nix develop` (recommended)

```bash
nix develop
cargo +nightly build --release
```

### Option 2: manual toolchain

1. Install prerequisites
   - Rust nightly (`rustup toolchain install nightly`)
   - LLVM 18 (set `LLVM_SYS_181_PREFIX`)

2. Platform-specific steps

   **macOS**
   ```bash
   brew install llvm@18
   export LLVM_SYS_181_PREFIX=$(brew --prefix llvm@18)
   export LLVM_SYS_180_PREFIX=$LLVM_SYS_181_PREFIX
   export PATH="$LLVM_SYS_181_PREFIX/bin:$PATH"
   cargo +nightly build --release
   ```

   **Ubuntu / Debian**
   ```bash
   sudo apt-get install -y llvm-18 llvm-18-dev clang-18
   export LLVM_SYS_181_PREFIX=/usr/lib/llvm-18
   export LLVM_SYS_180_PREFIX=$LLVM_SYS_181_PREFIX
   cargo +nightly build --release
   ```

   **Windows**
   ```powershell
   cargo install llvmenv --locked
   llvmenv install 18.1
   llvmenv global 18.1

   $llvmPath = llvmenv prefix
   $env:LLVM_SYS_181_PREFIX = $llvmPath
   $env:LLVM_SYS_180_PREFIX = $llvmPath
   $env:Path = "$llvmPath\bin;$env:Path"

   rustup toolchain install nightly
   rustup default nightly

   cargo +nightly build --release
   ```

> **Windows tip:** use the *x64 Native Tools Command Prompt for VS 2022*. It preloads the MSVC linker environment that plain PowerShell/CMD sessions lack.

## Building & Testing

```bash
cargo +nightly build --release
cargo test
```

## Workflow Expectations

### Code style
- Run `cargo fmt` before committing
- Run `cargo clippy` (nightly) and resolve warnings
- Favor expressive names and small helpers over heavy commenting

### Commit messages
Use concise prefixes:

```
feat: add array indexing support
fix: resolve type inference bug
docs: update FFI documentation
refactor: simplify lexer tokenization
```

### Pull requests
1. Keep PRs scoped to a single change
2. Add tests/docs alongside behavioral changes
3. Ensure CI is green before requesting review
4. Reference related issues when possible (`Fixes #123`)

## Areas for Contribution

- Language front-end (parser, type checker, diagnostics)
- Standard library modules and runtime utilities
- Transparent FFI bridge (type mapping, cache tooling, `bridge.yaml` configs)
- Tooling (VS Code extension, LSP, formatter, REPL/TUI)
- Documentation + runnable examples (`examples/basic`, `examples/ffi`, `examples/benchmarks`)
- Performance profiling and error-message polish

### Custom FFI bridges
Most crates work via automatic rustdoc extraction. For bespoke setups:
1. Create `ffi/<crate>/bridge.yaml`
2. Describe the dependency metadata + any overrides
3. Use `ffi/rand/bridge.yaml` as a reference

## Reporting Issues

Please include:
- Clear reproduction steps or a minimal failing example
- Expected vs actual behavior
- Environment details (OS, LLVM/clang version, Rust toolchain, `nix develop` vs manual)

## License

By contributing you agree your work will be released under the MIT License.
