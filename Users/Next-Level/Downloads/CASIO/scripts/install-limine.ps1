param(
  [string]$IsoDir = "iso",
  [string]$LimineDir = "third_party/limine"
)

Write-Output "==> Preparing ISO directory: $IsoDir"
if (-not (Test-Path $IsoDir)) { New-Item -ItemType Directory -Path $IsoDir | Out-Null }

if (Test-Path build\kernel.elf) {
  Copy-Item build\kernel.elf -Destination "$IsoDir\kernel.elf" -Force
} else {
  Write-Warning "build\kernel.elf not found; run 'make' first"
}

$binCandidates = @(
    "limine-cd.bin",
    "limine-bios-cd.bin",
    "limine-uefi-cd.bin"
)
$sysCandidates = @(
    "limine.sys",
    "limine-bios.sys",
    "limine-uefi.sys"
)

$copied = $false
foreach ($b in $binCandidates) {
    $src = Join-Path $LimineDir $b
    if (Test-Path $src) { Copy-Item $src -Destination "$IsoDir\limine-cd.bin" -Force; $copied = $true; break }
}
if (-not $copied) { Write-Warning "No CD image (limine-*-cd.bin) found in $LimineDir" }

$copied = $false
foreach ($s in $sysCandidates) {
    $src = Join-Path $LimineDir $s
    if (Test-Path $src) { Copy-Item $src -Destination "$IsoDir\limine.sys" -Force; $copied = $true; break }
}
if (-not $copied) { Write-Output "No limine .sys found; if using UEFI-only, ensure BOOTX64.EFI is present." }

# Copy BOOTX64.EFI if present
if (Test-Path (Join-Path $LimineDir "BOOTX64.EFI")) {
    Copy-Item (Join-Path $LimineDir "BOOTX64.EFI") -Destination "$IsoDir\" -Force
}

Copy-Item limine.cfg -Destination "$IsoDir\" -Force

$inst = Join-Path $LimineDir "limine-install"
if (Test-Path $inst) { Write-Output "Run limine-install on WSL/Linux: (cd $LimineDir && ./limine-install ../$IsoDir)" } else { Write-Output "limine-install not present; use WSL to run limine-install if needed." }

Write-Output "To create an ISO with xorriso on WSL/Linux:"
Write-Output "  xorriso -as mkisofs -o casio.iso -b limine-cd.bin -c boot.catalog $IsoDir"
