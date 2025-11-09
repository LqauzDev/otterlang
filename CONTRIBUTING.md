# Contributing to OtterLang

## Development Setup

### Option 1: Using Nix (Recommended)

```bash
nix develop
cargo +nightly build --release
```

### Option 2: Manual Setup

1. **Install prerequisites**:
   - Rust (via rustup) - nightly required for FFI features
   - LLVM 18

2. **Setup**:

   **macOS:**
   ```bash
   brew install llvm@18
   export LLVM_SYS_181_PREFIX=$(brew --prefix llvm@18)
   export LLVM_SYS_180_PREFIX=$LLVM_SYS_181_PREFIX
   export PATH="$LLVM_SYS_181_PREFIX/bin:$PATH"
   rustup toolchain install nightly
   cargo +nightly build --release
   ```

   **Ubuntu/Debian:**
   ```bash
   sudo apt-get install -y llvm-18 llvm-18-dev clang-18
   export LLVM_SYS_181_PREFIX=/usr/lib/llvm-18
   export LLVM_SYS_180_PREFIX=$LLVM_SYS_181_PREFIX
   rustup toolchain install nightly
   cargo +nightly build --release
   ```

   **Windows:**
   ```powershell
   # Install LLVM 18.1 using llvmenv (recommended)
   cargo install llvmenv --locked
   llvmenv install 18.1
   llvmenv global 18.1

   # Set environment variables
   $llvmPath = llvmenv prefix
   $env:LLVM_SYS_181_PREFIX = $llvmPath
   $env:LLVM_SYS_180_PREFIX = $llvmPath
   $env:Path = "$llvmPath\bin;$env:Path"

   # Alternative: Install using winget or Chocolatey
   # winget install --id LLVM.LLVM --silent --accept-package-agreements --accept-source-agreements
   # choco install llvm -y
   # $env:LLVM_SYS_181_PREFIX = "C:\Program Files\LLVM"
   # $env:LLVM_SYS_180_PREFIX = $env:LLVM_SYS_181_PREFIX
   # $env:Path = "$env:LLVM_SYS_181_PREFIX\bin;$env:Path"

   # Install Rust nightly
   rustup toolchain install nightly
   rustup default nightly

   # Build
   cargo +nightly build --release
   ```

   **Important:** On Windows, you must use the **x64 Native Tools Command Prompt for VS 2022** to build. The MSVC linker requires environment variables that are automatically set in the Developer Command Prompt. Open it from the Start menu, then navigate to your project directory and run the build commands. Regular PowerShell/CMD will not have the MSVC environment configured.

### Building

```bash
cargo +nightly build --release
```

### Testing

```bash
cargo test
```

## Code Style

- Run `cargo fmt` before committing
- Run `cargo clippy` to check for issues
- Write clear, self-documenting code

## Commit Messages

Use clear, descriptive messages:

```
feat: Add support for array indexing
fix: Resolve type inference bug
docs: Update FFI documentation
refactor: Simplify lexer tokenization
```

## Pull Requests

1. Keep PRs focused: one feature or fix per PR
2. Add tests for new functionality
3. Update documentation as needed
4. Ensure CI passes before requesting review

## Areas for Contribution

- Language features (Pythonic style preferred)
- Standard library modules
- FFI bridges (transparent FFI auto-extracts from rustdoc, or use bridge.yaml for custom config)
- Documentation improvements
- Examples (organized in `examples/basic/`, `examples/ffi/`, `examples/benchmarks/`)
- Performance optimizations
- Error message improvements

## FFI Development

Transparent FFI automatically extracts APIs from Rust crates via rustdoc. No `bridge.yaml` needed unless you want custom configuration.

To add custom bridge configuration:
1. Create `ffi/<crate-name>/bridge.yaml`
2. See `ffi/rand/bridge.yaml` for examples

## Reporting Issues

Include:
- Clear description and reproduction steps
- Expected vs actual behavior
- Environment: OS, LLVM version, Rust version

## License

By contributing, you agree that your contributions will be licensed under the MIT License.
