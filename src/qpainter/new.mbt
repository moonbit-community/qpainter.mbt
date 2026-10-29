///|
pub type PaintEventHandler = (Window, QPainter) -> Unit

///|
pub type KeyEventHandler = (Window, Int32, KeyModifier) -> Unit

///|
pub type MouseEventHandler = (Window, Double, Double, KeyModifier, MouseButton) -> Unit

///|
pub type ResizeEventHandler = (Window, Int32, Int32) -> Unit

///|
/// This constructor is very unstable.
/// We will redesign it in the future.
/// 640 * 480 excluded title bar.
pub fn Window::new(
  paint~ : PaintEventHandler,
  key_press~ : KeyEventHandler,
  key_release~ : KeyEventHandler,
  mouse_press~ : MouseEventHandler,
  mouse_release~ : MouseEventHandler,
  mouse_double_click~ : MouseEventHandler,
  mouse_move~ : MouseEventHandler,
  resize~ : ResizeEventHandler,
) -> Window {
  window_new_ffi(
    paint,
    key_press,
    key_release,
    mouse_press,
    mouse_release,
    mouse_double_click,
    mouse_move,
    resize,
    (ctx, window, painter) => paint_callback(ctx)(window, painter),
    (ctx, window, key, modifier) => key_callback(ctx)(window, key, modifier),
    (ctx, window, x, y, modifier, button) => {
      mouse_callback(ctx)(window, x, y, modifier, button)
    },
    (ctx, window, width, height) => resize_callback(ctx)(window, width, height),
  )
}

///|
#borrow(paint, key_press, key_release, mouse_press, mouse_release, mouse_double_click, mouse_move, resize)
extern "c" fn window_new_ffi(
  paint : PaintEventHandler,
  key_press : KeyEventHandler,
  key_release : KeyEventHandler,
  mouse_press : MouseEventHandler,
  mouse_release : MouseEventHandler,
  mouse_double_click : MouseEventHandler,
  mouse_move : MouseEventHandler,
  resize : ResizeEventHandler,
  invoke_paint : FuncRef[(CallbackContext, Window, QPainter) -> Unit],
  invoke_key : FuncRef[(CallbackContext, Window, Int32, KeyModifier) -> Unit],
  invoke_mouse : FuncRef[
    (CallbackContext, Window, Double, Double, KeyModifier, MouseButton) -> Unit,
  ],
  invoke_resize : FuncRef[(CallbackContext, Window, Int32, Int32) -> Unit],
) -> Window = "illusory0x0_Window_new"

///|
#borrow(r, g, b, a)
pub extern "c" fn QColor::new(
  r : Int32,
  g : Int32,
  b : Int32,
  a : Int32,
) -> QColor = "illusory0x0_QColor_new"

///|
#borrow(str)
pub extern "c" fn QString::new(str : String) -> QString = "illusory0x0_QString_new"

///|
#borrow(brush, width)
pub extern "c" fn QPen::new(brush : QBrush, width : Double) -> QPen = "illusory0x0_QPen_new"

///|
#borrow(color)
pub extern "c" fn QBrush::new(color : QColor) -> QBrush = "illusory0x0_QBrush_new"

///|
/// shadow copy
#borrow(xs)
pub extern "c" fn QStringList::new(xs : FixedArray[QString]) -> QStringList = "illusory0x0_QStringList_new"

///|
#borrow(width, height)
pub extern "c" fn QSizeF::new(width : Double, height : Double) -> QSizeF = "illusory0x0_QSizeF_new"

///|
#borrow(x, y)
pub extern "c" fn QPointF::new(x : Double, y : Double) -> QPointF = "illusory0x0_QPointF_new"

///|
#borrow(x, y, width, height)
pub extern "c" fn QRectF::new(
  x : Double,
  y : Double,
  width : Double,
  height : Double,
) -> QRectF = "illusory0x0_QRectF_new"

///|
#borrow(families, size, weight, italic)
pub extern "c" fn QFont::new(
  families : QStringList,
  size : Int32,
  weight : Int32,
  italic : Bool,
) -> QFont = "illusory0x0_QFont_new"

///|
#borrow(font)
pub extern "c" fn QFontMetricsF::new(font : QFont) -> QFontMetricsF = "illusory0x0_QFontMetricsF_new"

///|
// Opaque managed callback data has the C ABI void* representation. The C++
// window retains the original closure; each adapter borrows its context and
// obtains an owned closure reference for a normal, compiler-generated call.
priv type CallbackContext

///|
#borrow(ctx)
extern "c" fn paint_callback(ctx : CallbackContext) -> PaintEventHandler = "qpainter_retain_paint_callback"

///|
#borrow(ctx)
extern "c" fn key_callback(ctx : CallbackContext) -> KeyEventHandler = "qpainter_retain_key_callback"

///|
#borrow(ctx)
extern "c" fn mouse_callback(ctx : CallbackContext) -> MouseEventHandler = "qpainter_retain_mouse_callback"

///|
#borrow(ctx)
extern "c" fn resize_callback(ctx : CallbackContext) -> ResizeEventHandler = "qpainter_retain_resize_callback"
