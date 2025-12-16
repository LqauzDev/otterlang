#!/usr/bin/env sh
set -euo pipefail

# Fetch Limine prebuilt tag as a submodule if possible, otherwise clone the tag
TARGET_DIR="third_party/limine"
TAG="v10.5.0-binary"
REPO_URL="https://codeberg.org/Limine/Limine.git"

echo "==> Ensuring Limine ($TAG) is available in ${TARGET_DIR}"

if [ -d "${TARGET_DIR}/.git" ]; then
  echo "Limine already present; updating"
  git -C "${TARGET_DIR}" fetch --depth 1 origin ${TAG} || true
  git -C "${TARGET_DIR}" checkout --detach ${TAG} || true
else
  if command -v git >/dev/null 2>&1; then
    echo "Adding as submodule (recommended)"
    # Try to add as a submodule; if it fails (already used), fallback to clone
    if git submodule add -b ${TAG} ${REPO_URL} ${TARGET_DIR} 2>/dev/null; then
      git -C "${TARGET_DIR}" checkout ${TAG} || true
    else
      echo "Submodule add failed; attempting a shallow clone"
      git clone --depth 1 --branch ${TAG} ${REPO_URL} ${TARGET_DIR}
    fi
  else
    echo "git not found, trying curl to fetch archive"
    ARCHIVE_URLS=(
      "https://codeberg.org/Limine/Limine/archive/${TAG}.tar.gz"
      "https://codeberg.org/Limine/Limine/archive/refs/tags/${TAG}.tar.gz"
    )
    mkdir -p "${TARGET_DIR}.tmp"
    for url in "${ARCHIVE_URLS[@]}"; do
      echo "Trying ${url}"
      if command -v curl >/dev/null 2>&1; then
        if curl -fSL "$url" -o "${TARGET_DIR}.tar.gz"; then
          tar -xzf "${TARGET_DIR}.tar.gz" -C "${TARGET_DIR}.tmp" --strip-components=1
          mv "${TARGET_DIR}.tmp" "${TARGET_DIR}"
          rm -f "${TARGET_DIR}.tar.gz"
          break
        fi
      elif command -v wget >/dev/null 2>&1; then
        if wget -O "${TARGET_DIR}.tar.gz" "$url"; then
          tar -xzf "${TARGET_DIR}.tar.gz" -C "${TARGET_DIR}.tmp" --strip-components=1
          mv "${TARGET_DIR}.tmp" "${TARGET_DIR}"
          rm -f "${TARGET_DIR}.tar.gz"
          break
        fi
      fi
    done
    rmdir "${TARGET_DIR}.tmp" 2>/dev/null || true
  fi
fi

# Verify expected limine binaries exist
BIN1="${TARGET_DIR}/limine-cd.bin"
BIN2="${TARGET_DIR}/limine.sys"
INSTALL_SCRIPT="${TARGET_DIR}/limine-install"

if [ ! -f "$BIN1" ] || [ ! -f "$BIN2" ]; then
  echo "Warning: expected limine binaries not found in ${TARGET_DIR}."
  echo "Look for files like limine-cd.bin and limine.sys inside the folder."
  echo "If you used a shallow clone of the tag, they should be present in the release tag." 
else
  echo "Limine binaries found: $BIN1 and $BIN2"
fi

if [ -x "$INSTALL_SCRIPT" ]; then
  echo "Found executable limine-install at $INSTALL_SCRIPT"
else
  echo "Note: ${INSTALL_SCRIPT} not executable or not found; 'limine-install' may need to be run from a Linux/WSL environment."
fi

echo "Limine is ready in ${TARGET_DIR}. Run './scripts/install-limine.sh iso' to prepare an ISO dir or run 'git submodule update --init --depth 1 third_party/limine' to sync." 
