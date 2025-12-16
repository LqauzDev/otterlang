#!/usr/bin/env sh
set -euo pipefail

ISO_DIR="${1:-iso}"
LIMINE_DIR="third_party/limine"

echo "==> Preparing ISO directory: ${ISO_DIR}"
mkdir -p "${ISO_DIR}"

# Copy kernel if available
if [ -f build/kernel.elf ]; then
  cp build/kernel.elf "${ISO_DIR}/kernel.elf"
else
  echo "Warning: build/kernel.elf not found; run 'make' first"
fi

# Copy limine binaries (support multiple variant names present in v10.5.0-binary)
# Prefer canonical names if present, otherwise normalize BIOS/UEFI variants into the expected names in the ISO dir
if [ -f "${LIMINE_DIR}/limine-cd.bin" ]; then
  cp "${LIMINE_DIR}/limine-cd.bin" "${ISO_DIR}/limine-cd.bin"
elif [ -f "${LIMINE_DIR}/limine-bios-cd.bin" ]; then
  cp "${LIMINE_DIR}/limine-bios-cd.bin" "${ISO_DIR}/limine-cd.bin"
elif [ -f "${LIMINE_DIR}/limine-uefi-cd.bin" ]; then
  cp "${LIMINE_DIR}/limine-uefi-cd.bin" "${ISO_DIR}/limine-cd.bin"
else
  echo "limine CD image not found in ${LIMINE_DIR}; ensure you have fetched the v10.5.0-binary tag"
fi

# limine.sys mappings
if [ -f "${LIMINE_DIR}/limine.sys" ]; then
  cp "${LIMINE_DIR}/limine.sys" "${ISO_DIR}/limine.sys"
elif [ -f "${LIMINE_DIR}/limine-bios.sys" ]; then
  cp "${LIMINE_DIR}/limine-bios.sys" "${ISO_DIR}/limine.sys"
elif [ -f "${LIMINE_DIR}/limine-uefi.sys" ]; then
  cp "${LIMINE_DIR}/limine-uefi.sys" "${ISO_DIR}/limine.sys"
else
  echo "limine .sys file not found in ${LIMINE_DIR}; continue if using UEFI-only boot (you may need BOOTX64.EFI)"
fi

# If the release contains UEFI payloads (BOOTX64.EFI) copy them too for convenience
if [ -f "${LIMINE_DIR}/BOOTX64.EFI" ]; then
  cp "${LIMINE_DIR}/BOOTX64.EFI" "${ISO_DIR}/"
fi

# If a limine-install helper exists, surface its location
INSTALL_SCRIPT="${LIMINE_DIR}/limine-install"
if [ -x "$INSTALL_SCRIPT" ]; then
  echo "Running limine-install on ${ISO_DIR}"
  (cd "${ISO_DIR}" && "../${LIMINE_DIR}/limine-install" .)
else
  echo "limine-install not executable or missing. To install Limine to the ISO dir, run on a Linux/WSL environment:"
  echo "  (cd ${LIMINE_DIR} && ./limine-install ../${ISO_DIR})"
fi

# Copy configuration
cp -f limine.cfg "${ISO_DIR}/limine.cfg"

# If limine-install is available, run it (needs to be run on Linux/WSL)
if [ -x "${LIMINE_DIR}/limine-install" ]; then
  echo "Running limine-install on ${ISO_DIR}"
  (cd "${ISO_DIR}" && "../${LIMINE_DIR}/limine-install" .)
else
  echo "limine-install not executable or missing. To install Limine to the ISO dir, run on a Linux/WSL environment:"
  echo "  (cd ${LIMINE_DIR} && ./limine-install ../${ISO_DIR})"i

# Create an ISO image if xorriso/genisoimage exists
if command -v xorriso >/dev/null 2>&1; then
  xorriso -as mkisofs -o casio.iso -b limine-cd.bin -c boot.catalog "${ISO_DIR}"
  echo "Created casio.iso"
elif command -v genisoimage >/dev/null 2>&1; then
  genisoimage -o casio.iso -b limine-cd.bin -c boot.catalog -no-emul-boot -boot-load-size 4 -boot-info-table "${ISO_DIR}"
  echo "Created casio.iso"
else
  echo "ISO tools not found; created ISO directory at ${ISO_DIR}. Install 'xorriso' or 'genisoimage' to make an ISO image."
fi
