// Linked from the archive only when the MoonBit GUI test references it.
#include <QApplication>
#include <QTimer>
extern "C" void qpainter_test_schedule_exit() {
  QTimer::singleShot(100, [] { QApplication::quit(); });
}
