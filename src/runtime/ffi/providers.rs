use once_cell::sync::OnceCell;

use crate::runtime::symbol_registry::SymbolRegistry;

#[derive(Clone, Copy)]
pub struct SymbolProvider {
    pub register: fn(&SymbolRegistry),
}

inventory::collect!(crate::runtime::ffi::providers::SymbolProvider);

fn register_builtin_symbols(registry: &SymbolRegistry) {
    for provider in inventory::iter::<SymbolProvider> {
        (provider.register)(registry);
    }
}

static STD_INIT: OnceCell<()> = OnceCell::new();

pub fn bootstrap_stdlib() -> &'static SymbolRegistry {
    let registry = SymbolRegistry::global();
    STD_INIT.get_or_init(|| {
        register_builtin_symbols(registry);
    });
    registry
}
