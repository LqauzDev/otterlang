param(
    [string]$Target = "third_party/limine",
    [string]$Tag = "v10.5.0-binary",
    [string]$Repo = "https://codeberg.org/Limine/Limine.git"
)

Write-Output "==> Ensuring Limine ($Tag) is available in $Target"

if (Test-Path "$Target\.git") {
    Write-Output "Limine already present; updating"
    git -C $Target fetch --depth 1 origin $Tag | Out-Null
    git -C $Target checkout --detach $Tag | Out-Null
} else {
    if (Get-Command git -ErrorAction SilentlyContinue) {
        Write-Output "Adding as submodule (recommended)"
        try {
            git submodule add -b $Tag $Repo $Target | Out-Null
            git -C $Target checkout $Tag | Out-Null
        } catch {
            Write-Output "Submodule add failed; trying shallow clone"
            git clone --depth 1 --branch $Tag $Repo $Target
        }
    } else {
        Write-Error "Git is not available. Please install Git or run this from WSL."
    }
}

$bin1 = Join-Path $Target "limine-cd.bin"
$bin2 = Join-Path $Target "limine.sys"
$inst = Join-Path $Target "limine-install"

if (-not (Test-Path $bin1) -or -not (Test-Path $bin2)) {
    Write-Warning "Expected limine binaries not found in $Target. Ensure the tag contains binaries or download the v10.5.0-binary release." 
} else {
    Write-Output "Limine binaries found: $bin1 and $bin2"
}

if (Test-Path $inst) {
    Write-Output "Found limine-install: $inst"
} else {
    Write-Output "limine-install not found or not executable. Use WSL to run 'limine-install' if necessary."
}

Write-Output "Limine is ready in $Target. Run '.\\scripts\\install-limine.ps1 -IsoDir iso' to prepare an ISO dir or run 'git submodule update --init --depth 1 third_party/limine' to sync."