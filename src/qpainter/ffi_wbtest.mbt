///|
test "QString preserves UTF-16 contents" {
  for value in ["", "A", "Hello", "中文", "a\u{1F680}z", "a\u0000b"] {
    assert_eq(QString::new(value).to_string(), value)
  }
}

///|
test "geometry constructors and getters" {
  let point = QPointF::new(-1.25, 7.5)
  assert_eq(point.x(), -1.25)
  assert_eq(point.y(), 7.5)
  let size = QSizeF::new(10.5, 2.25)
  assert_eq(size.width(), 10.5)
  assert_eq(size.height(), 2.25)
  let rect = QRectF::new(-3.0, 2.0, 8.0, 9.0)
  assert_eq(rect.left(), -3.0)
  assert_eq(rect.right(), 5.0)
  assert_eq(rect.top(), 2.0)
  assert_eq(rect.bottom(), 11.0)
}

///|
extern "c" fn schedule_test_exit() -> Unit = "qpainter_test_schedule_exit"

///|
test "offscreen window retains and invokes event callbacks" {
  let argc = Ref(1)
  let argv : FixedArray[Bytes] = [b"qpainter-test"]
  let app = QApplication::new(argc, argv)
  let paints = Ref(0)
  let keys = Ref(0)
  let mouse = Ref(0)
  let resizes = Ref(0)
  let window = Window::new(
    paint=(_, painter) => {
      paints.val += 1
      painter.drawRect(0.0, 0.0, 10.0, 10.0)
    },
    key_press=(_, _, _) => keys.val += 1,
    key_release=(_, _, _) => keys.val += 1,
    mouse_press=(_, _, _, _, _) => mouse.val += 1,
    mouse_release=(_, _, _, _, _) => mouse.val += 1,
    mouse_double_click=(_, _, _, _, _) => mouse.val += 1,
    mouse_move=(_, _, _, _, _) => mouse.val += 1,
    resize=(_, _, _) => resizes.val += 1,
  )
  assert_true(window.devicePixelRatio() >= 1)
  window.show()
  send_test_events(window)
  schedule_test_exit()
  assert_eq(QApplication::exec(), 0)
  assert_true(paints.val > 0)
  assert_true(keys.val >= 2)
  assert_true(mouse.val >= 4)
  assert_true(resizes.val > 0)
  // Qt retains argc/argv; keep their owners alive until the event loop exits.
  ignore((window, app, argc, argv))
}

///|
#borrow(window)
extern "c" fn send_test_events(window : Window) -> Unit = "qpainter_test_send_events"
