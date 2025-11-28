# OtterLang VSCode Extension

Beautiful, feature-rich VSCode extension for the OtterLang programming language! 🦦

## Features

### Syntax Highlighting
- Full syntax highlighting for OtterLang
- Support for all language constructs (functions, classes, control flow, etc.)
- Semantic token highlighting

### IntelliSense & Auto-completion
- Smart code completion
- Parameter hints
- Signature help
- Hover documentation

### Code Editing
- **Auto-indentation**: Proper indentation for control flow blocks
- **Auto-closing**: Brackets, quotes, and parentheses
- **Code folding**: Fold functions, classes, and regions
- **Word selection**: Smart word boundaries

### Snippets
20+ built-in code snippets for common patterns (type the prefix and press Tab):
- `def` - Function definition (`fn`)
- `if`, `ife`, `ifel` - If statements
- `for`, `forr` - For loops
- `while` - While loop
- `resfn` - Function returning Result type
- `resmat` - Match Result with Ok/Err cases
- `optmat` - Match Option with Some/None cases
- `resunw` - Unwrap Result or panic
- `resch` - Chain multiple Result operations
- `result` - Result enum definition
- `option` - Option enum definition
- `match` - Match statement
- `struct` - Struct definition
- `enum` - Enum definition
- `use` - Import a module
- And more!

### ⌨️ Keyboard Shortcuts
- `Cmd/Ctrl + Shift + R` - Run current file
- `Cmd/Ctrl + Shift + F` - Format document
- `Cmd/Ctrl + Shift + P` - Restart language server

### Language Server Features
- Real-time diagnostics
- Go to definition
- Find references
- Rename symbol
- Code formatting
- Document symbols

### File Icons
- Custom OtterLang file icons
- Cute otter icon for `.ot` files

## Configuration

### LSP Server Path
Set the path to your OtterLang LSP server:
```json
{
  "otterlang.lsp.serverPath": "/path/to/otterlang-lsp"
}
```

### Formatting
Configure indentation and formatting:
```json
{
  "otterlang.formatting.indentSize": 4,
  "otterlang.formatting.insertSpaces": true
}
```

### Linting
Enable/disable linting:
```json
{
  "otterlang.linting.enabled": true
}
```

### Debug Tracing
Enable LSP trace for debugging:
```json
{
  "otterlang.lsp.trace": "verbose"
}
```

## Commands

Access these commands via the Command Palette (`Cmd/Ctrl + Shift + P`):

- **OtterLang: Start Language Server** - Start the LSP server
- **OtterLang: Stop Language Server** - Stop the LSP server
- **OtterLang: Restart Language Server** - Restart the LSP server
- **OtterLang: Toggle LSP Logs** - Show/hide LSP logs
- **OtterLang: Show Output** - Show extension output
- **OtterLang: Run Current File** - Execute the current file
- **OtterLang: Format Document** - Format the current document

## Indentation Rules

The extension automatically handles indentation for:
- Function definitions (`def`)
- Class definitions (`class`)
- Control flow (`if`, `elif`, `else`, `for`, `while`)
- Error handling with Result types (`Result.Ok`, `Result.Err`)
- Match statements (`match`, `case`)

Dedenting works automatically for:
- `elif`, `else`
- `case` (in match expressions)

## Code Folding

Use `# region` and `# endregion` comments to create foldable regions:

```otterlang
# region Helper Functions
def helper1():
    pass

def helper2():
    pass
# endregion
```

## Requirements

- VSCode 1.75.0 or higher
- OtterLang LSP server (optional, for advanced features)

## Installation

1. Install from VSCode Marketplace (coming soon!)
2. Or build from source:
   ```bash
   cd vscode-extension
   npm install
   npm install -g vsce
   npm run package
   # This creates otterlang-*.vsix file which is the installable extension
   code --install-extension otterlang-*.vsix
   ```

## Contributing

We love contributions! Here's how you can help:

### Ways to Contribute
- **Bug Reports**: Found an issue? [Open an issue](https://github.com/jonathanmagambo/otterlang/issues)
- **Feature Requests**: Have an idea? [Suggest it](https://github.com/jonathanmagambo/otterlang/discussions)
- **Code Contributions**: Fix bugs or add features
- **Documentation**: Improve docs or examples
- **Testing**: Help test new features

### Getting Started
1. Read our [Contributing Guide](CONTRIBUTING.md)
2. Fork the repository
3. Create a feature branch
4. Make your changes
5. Test thoroughly
6. Submit a pull request

### Development Setup
```bash
cd vscode-extension
npm install
npm run compile

# Install vsce globally if you haven't already
npm install -g vsce

# Package the extension (creates installable .vsix file)
npm run package

# Install the extension locally
code --install-extension otterlang-*.vsix

# For active development with hot reload
code --extensionDevelopmentPath=.
```

---

**Enjoy coding in OtterLang!** 
