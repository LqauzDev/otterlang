// JIT Runtime System Module
pub mod adaptive;
pub mod cache;
pub mod engine;
pub mod executor;
pub mod optimization;
pub mod profiler;
pub mod specialization;

pub use engine::JitEngine;
pub use executor::JitExecutor;

