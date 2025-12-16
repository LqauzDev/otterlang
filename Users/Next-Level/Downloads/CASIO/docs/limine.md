Limine integration (quick notes)

Limine is a simple modern bootloader for BIOS/UEFI. For a full install and creating a bootable ISO, follow Limine's docs: https://github.com/limine-bootloader/limine

Quick steps (summary):
1. Build `kernel.elf` (`make`).
2. Fetch Limine (recommended via submodule or the helper script):

   # Fetch via git submodule (recommended)
   git submodule update --init --depth 1 third_party/limine

   # Or run the helper script (POSIX):
   ./scripts/get-limine.sh

   # Or run the helper script on PowerShell:
   .\scripts\get-limine.ps1

3. Prepare an ISO directory and install Limine (helper scripts provided):

   # POSIX (recommended to run limine-install in WSL/Linux):
   ./scripts/install-limine.sh iso

   # PowerShell (prints instructions for WSL where needed):
   .\scripts\install-limine.ps1 -IsoDir iso

4. Create an ISO (on WSL/Linux):

   xorriso -as mkisofs -o casio.iso -b limine-cd.bin -c boot.catalog iso/

   (If you don't have xorriso, `genisoimage` can also be used with equivalent options.)

5. Test with QEMU: `qemu-system-x86_64 -cdrom casio.iso -m 1G -smp 2 -serial stdio`

Notes:
- The v10.5.0-binary tag contains prebuilt Limine binaries. The release includes BIOS and UEFI variants such as `limine-bios-cd.bin`, `limine-bios.sys`, `limine-uefi-cd.bin`, and `BOOTX64.EFI`.
- The helper scripts (`scripts/install-limine.*`) will detect available variants and normalize them into `iso/` (copying an available CD image as `limine-cd.bin` and `.sys` as `limine.sys` when possible).
- `limine-install` is typically executed in a Linux/WSL environment and may require privileges to write boot sectors to the ISO staging dir; the scripts print guidance when manual steps are required.

Notes:
- On Windows, use WSL or a Linux environment for the `limine-install` and `xorriso` steps.
- We'll later add a `scripts/` helper to automate ISO creation and limine install.
