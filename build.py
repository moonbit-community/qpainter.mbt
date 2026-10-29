#!/usr/bin/env python3
"""Build the Qt bridge and supply native linker flags to Moon."""
import hashlib
import json
import os
import platform
from pathlib import Path
import shlex
import shutil
import subprocess
import sys

json.load(sys.stdin)
root = Path(__file__).resolve().parent
build = root / "_build" / "qt-native"
cxx = os.environ.get("CXX", "clang++")
flags = "-fsanitize=address,undefined -fno-omit-frame-pointer" if os.environ.get("QPAINTER_SANITIZE") == "1" else ""
subprocess.run(["cmake", "-S", str(root / "stub"), "-B", str(build),
    "-G", "Unix Makefiles", "-DCMAKE_CXX_COMPILER=" + cxx,
    "-DMOON_HOME=" + os.environ.get("MOON_HOME", str(Path.home() / ".moon")),
    "-DQPAINTER_SANITIZE=" + ("ON" if flags else "OFF")], check=True, stdout=sys.stderr)
subprocess.run(["cmake", "--build", str(build), "-j", "2"], check=True, stdout=sys.stderr)
# Moon does not track external archive contents in free-form linker flags.
# Use a content-addressed path so a rebuilt bridge always relinks consumers.
archive = build / "libqpainter_mbt.a"
linked_archive = build / ("libqpainter_" + hashlib.sha256(archive.read_bytes()).hexdigest()[:16] + ".a")
if not linked_archive.exists():
    shutil.copyfile(archive, linked_archive)
qt_libs = subprocess.check_output(["pkg-config", "--libs", "Qt6Widgets"], text=True).strip()
cxx_lib = "-lc++" if sys.platform == "darwin" else "-lstdc++"
link_flags = shlex.quote(str(linked_archive)) + " " + qt_libs + " " + cxx_lib + " " + flags
if flags and sys.platform.startswith("linux"):
    # Moon links generated C with the C driver, which omits Clang's C++ UBSan
    # support library. Include it explicitly for virtual-pointer checks in Qt.
    runtime_name = "libclang_rt.ubsan_standalone_cxx-" + platform.machine() + ".a"
    runtime = subprocess.check_output([cxx, "-print-file-name=" + runtime_name], text=True).strip()
    if not Path(runtime).is_file():
        raise RuntimeError("Install the Clang C++ sanitizer runtime: " + runtime_name)
    link_flags += " " + shlex.quote(runtime)

json.dump({"link_configs": [{"package": "moonbit-community/qpainter/qpainter", "link_flags": link_flags}]}, sys.stdout)
