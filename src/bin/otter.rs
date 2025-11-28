use otterlang::cli;

fn main() -> anyhow::Result<()> {
    cli::run()
}

#[cfg(test)]
mod tests {
    use clap::Parser;
    use otterlang::cli::{Command, OtterCli};

    #[test]
    fn run_command_parses_path_argument() {
        let cli = OtterCli::parse_from(["otter", "run", "tests/demo.ot"]); // no filesystem access
        match cli.command() {
            Command::Run { path } => assert_eq!(path.to_string_lossy(), "tests/demo.ot"),
            other => panic!("expected run command, got {other:?}"),
        }
    }
}
