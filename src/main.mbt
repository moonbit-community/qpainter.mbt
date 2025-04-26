///|
fn main {
  let argc : Ref[Int] = Ref::new(1)
  let argv : FixedArray[Bytes] = [b"painter\x00"]
  let app = QApplication::new(argc, argv)
  let window = Window::new(fn(painter) {
    let font = QFont::new(QStringList::from_builtin(["楷体"]), 40, 320, false)
    let text = QString::from_builtin("你好")
    let brush = QBrush::new(QColor::new(255, 0, 0, 255))
    let pen = QPen::new(brush, 0)
    painter.setBrush(brush)
    painter.setPen(pen)
    painter.setFont(font)
    painter.drawRect(20, 20, 100, 100)
    painter.drawText(200, 150, text)
  })
  window.show()
  let exit_code = QApplication::exec()
  drop([window, app, exit_code])
}
