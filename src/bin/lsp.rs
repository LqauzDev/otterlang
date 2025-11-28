use otterlang::lsp;

#[tokio::main]
async fn main() {
    lsp::run_stdio_server().await;
}

#[cfg(test)]
mod tests {
    use std::future::Future;

    use super::*;

    fn assert_future<F: Future<Output = ()>>(_fut: &F) {}

    #[test]
    fn lsp_entrypoint_exposes_async_future() {
        let future = lsp::run_stdio_server();
        assert_future(&future);
    }
}
