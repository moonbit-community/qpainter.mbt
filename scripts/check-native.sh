#!/usr/bin/env bash
set -euo pipefail
export MOON_CC="${MOON_CC:-${CC:-clang}}"
export QT_QPA_PLATFORM=offscreen
export UBSAN_OPTIONS=halt_on_error=1:print_stacktrace=1
export ASAN_OPTIONS=halt_on_error=1
moon update
moon check --target native --deny-warn
moon fmt --check
moon info --target native
# Build the demo entry point, then exercise the binding test executable.
moon build --target native --deny-warn
moon test --target native --deny-warn
moon test --target native --deny-warn --release
# Validate the callback ABI and retained contexts with strict sanitizers.
QPAINTER_SANITIZE=1 moon test --target native --deny-warn --release
