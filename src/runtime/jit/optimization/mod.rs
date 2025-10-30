// In-memory Optimization System
pub mod inliner;
pub mod reoptimizer;
pub mod call_graph;

pub use inliner::Inliner;
pub use reoptimizer::Reoptimizer;
pub use call_graph::CallGraph;

/// Optimization context for hot functions
pub struct OptimizationContext {
    pub hot_functions: Vec<String>,
    pub call_graph: CallGraph,
}

impl OptimizationContext {
    pub fn new(hot_functions: Vec<String>) -> Self {
        Self {
            hot_functions,
            call_graph: CallGraph::new(),
        }
    }
}

