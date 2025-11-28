use otterlang::cli;

fn main() -> anyhow::Result<()> {
    cli::run()
}

#[cfg(test)]
mod tests {
    use clap::Parser;
    use otterlang::cli::{Command, OtterCli};

    #[test]
    fn build_command_honors_output_flag() {
        let cli = OtterCli::parse_from([
            "otter",
            "build",
            "examples/app.ot",
            "--output",
            "target/app",
        ]);
        match cli.command() {
            Command::Build { path, output } => {
                assert_eq!(path.to_string_lossy(), "examples/app.ot");
                assert_eq!(
                    output.as_ref().map(|p| p.to_string_lossy().into_owned()),
                    Some("target/app".into())
                );
            }
            other => panic!("expected build command, got {other:?}"),
        }
    }
}
