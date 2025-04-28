///|
pub typealias PaintEventHandler = (Window, QPainter) -> Unit

///|
pub typealias KeyEventHandler = (Window, Int, KeyModifier) -> Unit

///|
pub typealias MouseEventHandler = (
  Window,
  Double,
  Double,
  KeyModifier,
  MouseButton,
) -> Unit

///|
pub typealias ResizeEventHandler = (Window, Int, Int) -> Unit

///|
/// 640 * 480 excluded title bar.
#borrow(paint, key_press, key_release, mouse_double_click, mouse_press, mouse_release, mouse_move, resize)
pub extern "c" fn Window::new(
  paint~ : PaintEventHandler,
  key_press~ : KeyEventHandler,
  key_release~ : KeyEventHandler,
  mouse_press~ : MouseEventHandler,
  mouse_release~ : MouseEventHandler,
  mouse_double_click~ : MouseEventHandler,
  mouse_move~ : MouseEventHandler,
  resize~ : ResizeEventHandler
) -> Window = "illusory0x0_Window_new"

///|
#borrow(r, g, b, a)
pub extern "c" fn QColor::new(r : Int, g : Int, b : Int, a : Int) -> QColor = "illusory0x0_QColor_new"

///|
#borrow(str)
pub extern "c" fn QString::new(str : String) -> QString = "illusory0x0_QString_new"

///|
#borrow(brush, width)
pub extern "c" fn QPen::new(brush : QBrush, width : Double) -> QPen = "illusory0x0_QPen_new"

///|
#borrow(color)
pub extern "c" fn QBrush::new(color : QColor) -> QBrush = "illusory0x0_QBrush_new"

///| shadow copy
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
  height : Double
) -> QRectF = "illusory0x0_QRectF_new"

///|
#borrow(families, size, weight, italic)
pub extern "c" fn QFont::new(
  families : QStringList,
  size : Int,
  weight : Int,
  italic : Bool
) -> QFont = "illusory0x0_QFont_new"

///|
#borrow(font)
pub extern "c" fn QFontMetricsF::new(font : QFont) -> QFontMetricsF = "illusory0x0_QFontMetricsF_new"
