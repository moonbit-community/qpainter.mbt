# qpainter (WIP)

a QPainter FFI binding.


https://github.com/user-attachments/assets/7bf54e83-af97-4696-811e-e9e032dcc787


## Support C++ class (partialy method)

### QtCore
* QtCore
  * QString
  * QColor
  * QStringList
  * QPointF
  * QSizeF
  * QRectF

* QtGUI
  * QApplication
  * QPainter
  * QPen
  * QBrush  
  * QFont
  * QFontMetricsF

## Entry

* Window::show

* event handler
  * paint
  * key_press
  * key_release
  * mouse_double_click
  * mouse_press
  * mouse_release
  * mouse_move

## Native build and validation

Requires Python 3, CMake, Make, pkg-config, Qt 6 Core/Gui/Widgets development
files, and a C++23 compiler supporting explicit object parameters (Clang 18+).
On Ubuntu 24.04:

```sh
sudo apt-get install clang-18 cmake make qt6-base-dev pkg-config
export MOON_CC=clang-18 CXX=clang++-18
moon build --target native src/main
QT_QPA_PLATFORM=offscreen moon test --target native
bash scripts/check-native.sh
```

On macOS, install Qt 6 and LLVM with Homebrew, expose Qt's pkg-config files,
and set `MOON_CC`/`CXX` to that LLVM installation. The build script discovers Qt
through CMake and pkg-config; `QT6_INCLUDE` is no longer required.

The regression tests cover UTF-16 conversion (including embedded NUL and
surrogate pairs), geometry getters, and an offscreen window receiving paint
callbacks. They do not verify interactive input or rendering on a real display.
`QPAINTER_SANITIZE=1` instruments the bridge and MoonBit executable with ASan
and UBSan; CI treats sanitizer diagnostics as failures.

Event callbacks use MoonBit-generated `FuncRef` adapters and an opaque managed
context. The C++ side retains callbacks while a window exists and transfers an
owned reference to each adapter; it never invokes a closure's internal code
pointer. Tests exercise paint, resize, key, and mouse callbacks under sanitizers.

Qt retains the `argc` and `argv` passed to `QApplication::new`; their MoonBit
owners must remain alive until the application has finished using them.
