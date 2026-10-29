// Linked from the archive only when the MoonBit GUI test references it.
#include <QApplication>
#include <QTimer>
extern "C" void qpainter_test_schedule_exit() {
  QTimer::singleShot(100, [] { QApplication::quit(); });
}

#include <QKeyEvent>
#include <QMouseEvent>
#include <QWidget>
extern "C" void qpainter_test_send_events(void *raw_window) {
  auto *window = static_cast<QWidget *>(raw_window);
  QKeyEvent press(QEvent::KeyPress, Qt::Key_A, Qt::ShiftModifier);
  QKeyEvent release(QEvent::KeyRelease, Qt::Key_A, Qt::ShiftModifier);
  QApplication::sendEvent(window, &press);
  QApplication::sendEvent(window, &release);
  for (auto type : {QEvent::MouseButtonPress, QEvent::MouseButtonRelease,
                    QEvent::MouseButtonDblClick, QEvent::MouseMove}) {
    QMouseEvent event(type, QPointF(3, 4), QPointF(3, 4), QPointF(3, 4),
                      Qt::LeftButton, Qt::LeftButton, Qt::NoModifier);
    QApplication::sendEvent(window, &event);
  }
}
