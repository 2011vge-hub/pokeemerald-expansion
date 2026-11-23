#!/usr/bin/env bash
# Neo Emerald build doctor for WSL (Ubuntu) on Windows.
#   bash neo_emerald/tools/wsl_doctor.sh           # check the environment only
#   bash neo_emerald/tools/wsl_doctor.sh --build   # check, then build with a saved log
# It never installs anything; it prints the command to run instead.
# On a failed build it prints the FIRST errors from the log, ready to paste into chat.
set -uo pipefail

REPO_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"
cd "$REPO_ROOT" || exit 1
OUT=neo_emerald/out
LOG=$OUT/build.log
problems=0
ok()   { printf '  [ok]   %s\n' "$1"; }
warn() { printf '  [warn] %s\n' "$1"; }
bad()  { printf '  [FIX]  %s\n' "$1"; problems=$((problems + 1)); }

echo "Neo Emerald build doctor"
echo "Environment"
if grep -qi microsoft /proc/version 2>/dev/null; then ok "running inside WSL"; else warn "not WSL (fine on plain Linux)"; fi
echo "  machine: $(uname -m), CPUs: $(nproc)"
case "$REPO_ROOT" in
  /mnt/*) bad "project is on the Windows drive ($REPO_ROOT). Clone it into ~/ instead: builds there are much faster and avoid file-permission errors." ;;
  *) ok "project is on the Linux file system ($REPO_ROOT)" ;;
esac
free_gb=$(df -Pk "$REPO_ROOT" | awk 'NR==2 {print int($4/1048576)}')
if [ "${free_gb:-0}" -lt 3 ]; then bad "only ${free_gb} GB free; the build needs about 3 GB"; else ok "${free_gb} GB free disk"; fi
mem_mb=$(awk '/MemTotal/ {print int($2/1024)}' /proc/meminfo)
if [ "${mem_mb:-0}" -lt 2500 ]; then warn "${mem_mb} MB RAM visible to WSL; use JOBS=2 if the build gets killed"; else ok "${mem_mb} MB RAM"; fi

echo "Tools"
missing=()
for t in arm-none-eabi-gcc arm-none-eabi-as arm-none-eabi-ld make gcc g++ python3 git pkg-config; do
  if command -v "$t" >/dev/null 2>&1; then ok "$t"; else missing+=("$t"); bad "$t not found"; fi
done
if command -v arm-none-eabi-gcc >/dev/null 2>&1; then
  echo "  arm-none-eabi-gcc: $(arm-none-eabi-gcc --version | head -1)"
  libc=$(arm-none-eabi-gcc -mthumb -print-file-name=libc.a)
  if [ -f "$libc" ]; then ok "newlib libc.a found"; else bad "newlib missing (libnewlib-arm-none-eabi)"; missing+=(newlib); fi
fi
if pkg-config --exists libpng 2>/dev/null; then ok "libpng (pkg-config)"; else bad "libpng development files missing"; missing+=(libpng); fi
if [ ${#missing[@]} -gt 0 ]; then
  echo
  echo "  Install the missing tools with:"
  echo "    sudo apt update && sudo apt install -y build-essential binutils-arm-none-eabi gcc-arm-none-eabi \\"
  echo "      libnewlib-arm-none-eabi git libpng-dev pkg-config python3"
fi

echo "Source"
if git rev-parse --git-dir >/dev/null 2>&1; then
  echo "  branch: $(git rev-parse --abbrev-ref HEAD)  commit: $(git rev-parse --short HEAD)"
  [ -n "$(git status --porcelain --untracked-files=no)" ] && warn "uncommitted changes present (fine if intended)"
fi
for check in neo_emerald/tools/validate_design.py neo_emerald/tools/check_source.py neo_emerald/tools/check_rescue_once.py; do
  if python3 "$check" >/dev/null 2>&1; then ok "$(basename "$check")"; else bad "$(basename "$check") failed: run 'python3 $check' to see why"; fi
done

echo
if [ "$problems" -gt 0 ]; then
  echo "$problems problem(s) to fix before building."
  exit 1
fi
echo "Environment looks ready."
[ "${1:-}" = "--build" ] || { echo "Run again with --build to compile."; exit 0; }

mkdir -p "$OUT"
jobs="${JOBS:-$(nproc)}"
echo "Building with $jobs jobs; full log: $LOG (first build can take 15-30 minutes)"
start=$(date +%s)
report_modified() {  # a build should never rewrite tracked source files
  changed=$(git status --porcelain --untracked-files=no 2>/dev/null | grep -v " neo_emerald/out/" || true)
  [ -n "$changed" ] && { echo "Note: these tracked files changed during the build (report them; don't commit blindly):"; echo "$changed"; }
  return 0
}
if JOBS="$jobs" bash neo_emerald/tools/build.sh >"$LOG" 2>&1; then
  echo "BUILD OK in $(( $(date +%s) - start ))s"
  report_modified
  ls -l "$OUT/NeoEmerald_Prototype.gba"
  command -v sha1sum >/dev/null && sha1sum "$OUT/NeoEmerald_Prototype.gba"
  if command -v explorer.exe >/dev/null 2>&1; then
    echo "Opening the output folder in Windows Explorer..."
    (cd "$OUT" && explorer.exe . >/dev/null 2>&1 || true)
  fi
  exit 0
fi
report_modified
echo "BUILD FAILED after $(( $(date +%s) - start ))s. First errors (paste these into chat):"
echo "----------------------------------------------------------------"
grep -n -m 12 -E "error:|Error [0-9]|undefined reference|No such file|cannot find|Traceback|fatal:|\*\*\*" "$LOG" || tail -n 25 "$LOG"
echo "----------------------------------------------------------------"
echo "Full log: $LOG"
exit 1
