#!/usr/bin/env python3
"""Build the Qt bridge and supply native linker flags to Moon."""
import hashlib
import json
import os
from pathlib import Path
import shlex
import shutil
import subprocess
import sys

json.load(sys.stdin)
root = Path(__file__).resolve().parent
build = root / "_build" / "qt-native"
cc = os.environ.get("CC", "clang")
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
json.dump({"vars": {"CC": cc, "CC_FLAGS": flags,
    "CC_LINK_FLAGS": shlex.quote(str(linked_archive)) + " " + qt_libs + " " + cxx_lib + " " + flags}}, sys.stdout)
