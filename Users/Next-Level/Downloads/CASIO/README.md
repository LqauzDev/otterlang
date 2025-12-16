# Casio

Casio is an experimental, advanced Unix-like 64-bit kernel project targeting x86_64, licensed under the GNU GPLv3 (BloodyHell-Industries-Inc Foundation).

Goals / features (long-term):
- 64-bit higher-half kernel
- 4/5-level paging support
- Preemptive per-CPU scheduler
- Modern UEFI bootloader support (Limine allowed)
- ACPI support (IOAPIC, LAPIC)
- Symmetric Multiprocessing (SMP)
- On-demand paging (demand paging / swap)
- Unix-like userspace and a modern window manager and compositor

This repository contains a minimal scaffold and a bootstrap kernel to get the build/test loop working. Follow the roadmap and tasks in the `TODO` list to track features.

Requirements (developer machine):
- x86_64 cross toolchain (x86_64-elf-gcc, x86_64-elf-ld) or clang targeting x86_64-elf
- nasm (optional)
- GNU make
- Limine (for making bootable ISOs; see below)
- qemu-system-x86_64 (for testing)

Quick build & run (bootstrap):
1. Install a cross toolchain. On Windows, use WSL or a prebuilt cross-compiler.
2. Run `scripts/check-toolchain.sh` (or `.\\scripts\\check-toolchain.ps1` on PowerShell) to verify your toolchain.
3. Run `scripts/check-toolchain.sh` and then run `make` to build `build/kernel.elf` (ensure `build/` exists; Makefile will create it). Example using Clang:

   make CC=clang CFLAGS='-ffreestanding -O2 -Wall -Wextra -fno-pie --target=x86_64-elf' LD=ld.lld

   (Install `lld` or use `x86_64-elf-ld` if available.)

4. Fetch Limine prebuilt tag and prepare an ISO (scripts provided):

   # Preferred: use git submodule to fetch the Limine tag
   git submodule update --init --depth 1 third_party/limine

   # Or use the helper script (POSIX):
   ./scripts/get-limine.sh

   # Or use the helper script on PowerShell:
   .\scripts\get-limine.ps1

5. Prepare the ISO dir and install Limine (Linux/WSL recommended):

   # POSIX (recommended to run limine-install in WSL/Linux):
   ./scripts/install-limine.sh iso

   # PowerShell (prints instructions for WSL where needed):
   .\scripts\install-limine.ps1 -IsoDir iso

6. Create an ISO (on WSL/Linux):

   xorriso -as mkisofs -o casio.iso -b limine-cd.bin -c boot.catalog iso/

7. Boot with QEMU: `qemu-system-x86_64 -cdrom casio.iso -m 1G -smp 2`.
5. Boot with QEMU: `qemu-system-x86_64 -cdrom casio.iso -m 1G -smp 2`.

Roadmap: See `docs/ROADMAP.md` for a phased roadmap and contributing guidelines.

License: GNU GPLv3 (see `LICENSE`).
