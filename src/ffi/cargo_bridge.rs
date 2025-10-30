use std::fs;
use std::path::{Path, PathBuf};

use anyhow::{anyhow, bail, Context, Result};
use libloading::library_filename;
use tracing::debug;

use crate::cache::path::cache_root;

use super::metadata::BridgeMetadata;
use super::rust_stubgen::{RustStubGenerator, StubSource};
use super::symbol_registry::BridgeSymbolRegistry;

/// Describes the key paths generated for a bridge crate.
#[derive(Clone, Debug)]
pub struct BridgeArtifacts {
    pub crate_root: PathBuf,
    pub manifest_path: PathBuf,
    pub library_path: PathBuf,
}

/// Coordinates stub generation, cargo builds, and symbol registration.
pub struct CargoBridge {
    root: PathBuf,
    registry: BridgeSymbolRegistry,
}

impl CargoBridge {
    /// Creates the bridge coordinator rooted under `.otter/cache/ffi`.
    pub fn new(registry: BridgeSymbolRegistry) -> Result<Self> {
        let root = cache_root()?.join("ffi");
        fs::create_dir_all(&root).context("failed to create ffi cache root")?;
        Ok(Self { root, registry })
    }

    /// Ensures a bridge crate exists and is compiled for the requested `crate_name`.
    /// Function metadata is resolved through the shared `BridgeSymbolRegistry`
    /// which in turn consults bridge manifests under `ffi/<crate>/bridge.yaml`.
    pub fn ensure_bridge(&self, crate_name: &str) -> Result<BridgeArtifacts> {
        let metadata = self.registry.ensure_metadata(crate_name)?;
        self.write_bridge(&metadata)?;
        let crate_root = self.root.join(crate_name);
        let library_path = self
            .build_bridge(crate_name, &crate_root)
            .context("failed to compile bridge crate")?;

        Ok(BridgeArtifacts {
            crate_root: crate_root.clone(),
            manifest_path: crate_root.join("Cargo.toml"),
            library_path,
        })
    }

    fn write_bridge(&self, metadata: &BridgeMetadata) -> Result<()> {
        let crate_root = self.ensure_scaffold(&metadata.crate_name)?;
        let manifest_path = crate_root.join("Cargo.toml");
        let src_dir = crate_root.join("src");
        fs::create_dir_all(&src_dir)
            .with_context(|| format!("failed to ensure ffi src dir {}", src_dir.display()))?;

        let generator =
            RustStubGenerator::new(metadata.crate_name.clone(), metadata.dependency.clone());
        let stub = generator.generate(&metadata.functions);
        self.write_manifest(&manifest_path, &stub)?;
        self.write_stub(&src_dir.join("lib.rs"), &stub)?;

        Ok(())
    }

    fn ensure_scaffold(&self, crate_name: &str) -> Result<PathBuf> {
        let crate_root = self.root.join(crate_name);
        fs::create_dir_all(&crate_root).with_context(|| {
            format!(
                "failed to create bridge crate directory {}",
                crate_root.display()
            )
        })?;
        Ok(crate_root)
    }

    fn write_manifest(&self, manifest_path: &Path, stub: &StubSource) -> Result<()> {
        debug!(path = %manifest_path.display(), "writing bridge manifest");
        fs::write(manifest_path, &stub.manifest)
            .with_context(|| format!("failed to write manifest {}", manifest_path.display()))
    }

    fn write_stub(&self, lib_path: &Path, stub: &StubSource) -> Result<()> {
        debug!(path = %lib_path.display(), "writing bridge stub");
        fs::write(lib_path, &stub.source)
            .with_context(|| format!("failed to write stub {}", lib_path.display()))
    }

    fn build_bridge(&self, crate_name: &str, crate_root: &Path) -> Result<PathBuf> {
        let package_name = format!("otterffi_{crate_name}");
        let library_filename = library_filename(&package_name);
        let target_dir = crate_root.join("target");
        let release_dir = target_dir.join("release");
        let library_path = release_dir.join(&library_filename);

        if library_path.exists() {
            return Ok(library_path);
        }

        fs::create_dir_all(&target_dir).with_context(|| {
            format!(
                "failed to create cargo target directory {}",
                target_dir.display()
            )
        })?;

        let manifest_path = crate_root.join("Cargo.toml");
        let output = duct::cmd!(
            "cargo",
            "build",
            "--release",
            "--manifest-path",
            &manifest_path
        )
        .dir(crate_root)
        .env("CARGO_TARGET_DIR", &target_dir)
        .run()
        .with_context(|| format!("failed to build bridge crate `{crate_name}`"))?;

        if !output.status.success() {
            bail!("cargo build failed for bridge crate `{crate_name}`");
        }

        if !library_path.exists() {
            Err(anyhow!(
                "expected compiled library `{}` not found",
                library_path.display()
            ))
        } else {
            Ok(library_path)
        }
    }
}
