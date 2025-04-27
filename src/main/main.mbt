///|
typealias @qpainter.(
  QPainter,
  QFont,
  QBrush,
  QPen,
  QColor,
  QApplication,
  Window,
  KeyModifier,
  MouseButton,
  QStringList,
  QString,
  QFontMetricsF
)

///|
fnalias @qpainter.(drop, key_to_string)

///|
fn main {
  let argc : Ref[Int] = Ref::new(1)
  let argv : FixedArray[Bytes] = [b"painter\x00"]
  let app = QApplication::new(argc, argv)
  let window = Window::new(
    paint~,
    key_press~,
    key_release~,
    mouse_double_click~,
    mouse_press~,
    mouse_release~,
    mouse_move~,
  )
  window.show()
  let exit_code = QApplication::exec()
  drop([window, app, exit_code])
}

///|
fn paint(win : Window, painter : QPainter) -> Unit {
  let font = QFont::new(QStringList::from_builtin(["楷体"]), 40, 320, false)
  let text = QString::from_builtin("你好")
  let brush = QBrush::new(QColor::new(255, 0, 0, 255))
  let pen = QPen::new(brush, 0)
  painter.setBrush(brush)
  painter.setPen(pen)
  painter.setFont(font)
  painter.drawRoundedRect(20, 20, 100, 100, 20, 20)
  painter.drawText(200, 150, text)
  let m = QFontMetricsF::new(font)
  println(m.height())
  println(m.horizontalAdvance(QString::from_builtin("hello")))
  println("paint")
}

///|
fn key_press(win : Window, key : Int, modifier : KeyModifier) -> Unit {
  println("key press")
  println("key: \{(key_to_string(key),modifier)}")
}

///|
fn key_release(win : Window, key : Int, modifier : KeyModifier) -> Unit {
  println("key release")
}

///|
fn mouse_double_click(
  win : Window,
  x : Double,
  y : Double,
  modifier : KeyModifier,
  button : MouseButton
) -> Unit {
  println("double click")
}

///|
fn mouse_press(
  win : Window,
  x : Double,
  y : Double,
  modifier : KeyModifier,
  button : MouseButton
) -> Unit {
  println("mouse press")
  println("click: \{(x,y,modifier,button)}")
}

///|
fn mouse_release(
  win : Window,
  x : Double,
  y : Double,
  modifier : KeyModifier,
  button : MouseButton
) -> Unit {
  println("mouse_release")
}

///|
fn mouse_move(
  win : Window,
  x : Double,
  y : Double,
  modifier : KeyModifier,
  button : MouseButton
) -> Unit {
  // println("move: \{(x,y,modifier)}")
}
