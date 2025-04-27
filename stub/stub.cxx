#include "moonbit_cxx_borrow.h"
#include "type_holes.h"
#include <QApplication>
#include <QFont>
#include <QKeyEvent>
#include <QPainter>
#include <QWidget>

using namespace type_holes;
using namespace moonbit::types;

#define let auto

// illusory0x0_

using PaintHandler = Closure<Unit, Extern<QPainter>>;
using KeyModifier = Int;
using MouseButton = Int;
using KeyEventHandler = Closure<Unit, Int, KeyModifier>;
using MouseEventHandler =
    Closure<Unit, Double, Double, KeyModifier, MouseButton>;

struct Window : QWidget {
  PaintHandler paint;
  KeyEventHandler key_press;
  KeyEventHandler key_release;
  MouseEventHandler mouse_double_click;
  MouseEventHandler mouse_press;
  MouseEventHandler mouse_release;
  MouseEventHandler mouse_move;
  Window(PaintHandler p, KeyEventHandler kp, KeyEventHandler kr,
         MouseEventHandler mp, MouseEventHandler mr, MouseEventHandler mdc,
         MouseEventHandler mm)
      : QWidget(), paint(p), key_press(kp), key_release(kr), mouse_press(mp),
        mouse_release(mr), mouse_double_click(mdc), mouse_move(mm) {
    this->key_press.increment_strong_count();
    this->key_release.increment_strong_count();
    this->mouse_press.increment_strong_count();
    this->mouse_release.increment_strong_count();
    this->mouse_double_click.increment_strong_count();
    this->mouse_move.increment_strong_count();
    this->paint.increment_strong_count();
    this->setMouseTracking(true);
  }
  virtual void paintEvent(QPaintEvent *event) noexcept override {
    let painter = QPainter{this};
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing |
                               QPainter::SmoothPixmapTransform,
                           true);
    this->paint(Extern<QPainter>::from(&painter));
  }
  virtual void keyPressEvent(QKeyEvent *event) noexcept override {
    call_key_event(this->key_press, event);
  }
  virtual void keyReleaseEvent(QKeyEvent *event) noexcept override {
    call_key_event(this->key_release, event);
  }
  virtual void mousePressEvent(QMouseEvent *event) noexcept override {
    call_mouse_event(this->mouse_press, event);
  }
  virtual void mouseReleaseEvent(QMouseEvent *event) noexcept override {
    call_mouse_event(this->mouse_release, event);
  }
  virtual void mouseDoubleClickEvent(QMouseEvent *event) noexcept override {
    call_mouse_event(this->mouse_double_click, event);
  }
  virtual void mouseMoveEvent(QMouseEvent *event) noexcept override {
    call_mouse_event(this->mouse_move, event);
  }
  static void call_mouse_event(MouseEventHandler event_handler,
                               QMouseEvent *event) noexcept {
    let position = event->position();
    let x = Double::from(position.x());
    let y = Double::from(position.y());
    let modifiers = Int::from(event->modifiers());
    let button = Int::from(event->button());
    event_handler(x, y, modifiers, button);
  }
  static void call_key_event(KeyEventHandler event_handler, QKeyEvent *event) {
    let key = Int::from(event->key());
    let modifiers = Int::from(event->modifiers());
    event_handler(key, modifiers);
  }
  ~Window() noexcept {
    this->paint.decrement_strong_count();
    this->key_press.decrement_strong_count();
    this->key_release.decrement_strong_count();
    this->mouse_press.decrement_strong_count();
    this->mouse_release.decrement_strong_count();
    this->mouse_double_click.decrement_strong_count();
    this->mouse_move.decrement_strong_count();
  }
};

using Bytes = FixedArray<Byte>;

// use force template instantiation
// https://github.com/llvm/llvm-project/issues/137282#issue-3018926539
// This actually only need in MSVC, clang has false positive diagnostics
static void force_template_instantiation() {
  { Ref<QApplication> _; }
  { Ref<Window> _; }
  { Ref<QPainter> _; }
  { Ref<QColor> _; }
  { Ref<QFont> _; }
  { Ref<QFontMetricsF> _; }
  { Ref<QPointF> _; }
  { Ref<Int> _; }
  { Ref<QStringList> _; }
  { FixedArray<Bytes> _; }
  { FixedArray<Ref<QString>> _; }
  { FixedArray<Ref<QRectF>> _; }
  { FixedArray<Ref<QBrush>> _; }
  { FixedArray<Ref<QPen>> _; }
  { FixedArray<Ref<QSizeF>> _; }
  { FixedArray<Ref<QPointF>> _; }
}

extern "C" {

// constructors
Ref<QApplication> illusory0x0_QApplication_new(Ref<Int> argc,
                                               FixedArray<Bytes> argv) {
  return Ref<QApplication>::from_cxx_ref(argc->repr,
                                         ::std::bit_cast<char **>(argv));
}

Ref<Window> illusory0x0_Window_new(PaintHandler p, KeyEventHandler kp,
                                   KeyEventHandler kr, MouseEventHandler mp,
                                   MouseEventHandler mr, MouseEventHandler mdc,
                                   MouseEventHandler mm) {
  return Ref<Window>::from_cxx_ref(p, kp, kr, mp, mr, mdc, mm);
}

Ref<QPainter> illusory0x0_QPainter_new(QPaintDevice *device) {
  return Ref<QPainter>::from_cxx_ref(device);
}

Ref<QColor> illusory0x0_QColor_new(Int r, Int g, Int b, Int a) {
  return Ref<QColor>::from(r, g, b, a);
}

Ref<QString> illusory0x0_QString_new(String str) {
  return Ref<QString>::from_cxx_ref(::std::bit_cast<QChar *>(str),
                                    str.length().repr);
}

Ref<QBrush> illusory0x0_QBrush_new(Ref<QColor> color) {
  return Ref<QBrush>::from_cxx_ref(*color.repr);
}
Ref<QPen> illusory0x0_QPen_new(Ref<QBrush> brush, Double width) {
  return Ref<QPen>::from_cxx_ref(*brush.repr, width.repr);
}
Ref<QFontMetricsF> illusory0x0_QFontMetricsF_new(Ref<QFont> font) {
  return Ref<QFontMetricsF>::from_cxx_ref(*font.repr);
}

Ref<QStringList> illusory0x0_QStringList_new(FixedArray<Ref<QString>> xs) {
  using namespace moonbit::operators;
  let res = Ref<QStringList>::from(xs.length());
  let len = xs.length();
  for (let i = Int::from(0); i < len; i = i + Int::from(1)) {
    (*res)[i.repr] = *xs[i];
  }
  return res;
}

Ref<QFont> illusory0x0_QFont_new(Ref<QStringList> families, Int size,
                                 Int weight, Bool italic) {

  return Ref<QFont>::from_cxx_ref(*families.repr, size.repr, weight.repr,
                                  (bool)italic.repr);
}
Ref<QRectF> illusory0x0_QRectF_new(Double x, Double y, Double w, Double h) {
  return Ref<QRectF>::from(x, y, w, h);
}
Ref<QSizeF> illusory0x0_QSizeF_new(Double w, Double h) {
  return Ref<QSizeF>::from(w, h);
  // return Ref
}
Ref<QPointF> illusory0x0_QPointF_new(Double x, Double y) {
  return Ref<QPointF>::from(x, y);
}
// conversion
moonbit_string_t illusory0x0_QString_to_moonbit_string(Ref<QString> self) {
  auto len = self->size();
  uint16_t *dest =
      (uint16_t *)moonbit_malloc_array(moonbit_BLOCK_KIND_VAL_ARRAY, 1, len);
  memcpy(dest, self->data(), len);
  return dest;
}

// methods
void illusory0x0_QPainter_setBrush(Ref<QPainter> self, Ref<QBrush> brush) {
  self->setBrush(*brush);
}

void illusory0x0_QPainter_setPen(Ref<QPainter> self, Ref<QPen> pen) {
  self->setPen(*pen);
}

void illusory0x0_QPainter_setFont(Ref<QPainter> self, Ref<QFont> font) {
  self->setFont(*font);
}

void illusory0x0_QPainter_drawRect(Ref<QPainter> self, double x, double y,
                                   double w, double h) {
  self->drawRect(QRectF(x, y, w, h));
}

void illusory0x0_QPainter_eraseRect(Ref<QPainter> self, double x, double y,
                                    double w, double h) {
  self->eraseRect(QRectF(x, y, w, h));
}

void illusory0x0_QPainter_drawText(Ref<QPainter> self, double x, double y,
                                   Ref<QString> text) {
  self->drawText(QPointF(x, y), *text);
}
void illusory0x0_QPainter_drawRoundedRect(Ref<QPainter> self, double x,
                                          double y, double w, double h,
                                          double xRadius, double yRadius) {
  self->drawRoundedRect(QRectF(x, y, w, h), xRadius, yRadius);
}

void illusory0x0_QPainter_save(Ref<QPainter> self) { self->save(); }
void illusory0x0_QPainter_restore(Ref<QPainter> self) { self->restore(); }

void illusory0x0_QPainter_setOpacity(Ref<QPainter> self, double opacity) {
  self->setOpacity(opacity);
}
void illusory0x0_Window_show(Ref<Window> self) { self->show(); }
int32_t illusory0x0_Window_width(Ref<Window> self) { return self->width(); }
int32_t illusory0x0_Window_height(Ref<Window> self) { return self->height(); }

Bool illusory0x0_QFontMetricsF_inFontUcs4(Ref<QFontMetricsF> self,
                                          Char codepoint) {
  return Bool::from(self->inFontUcs4(codepoint.repr));
}

Ref<QRectF> illusory0x0_QFontMetricsF_boundingRect(Ref<QFontMetrics> self,
                                                   Ref<QString> text) {
  return Ref<QRectF>::from_cxx_ref(self->boundingRect(*text));
}

double illusory0x0_QFontMetricsF_horizontalAdvance(Ref<QFontMetrics> self,
                                                   Ref<QString> text) {
  return self->horizontalAdvance(*text);
}
double illusory0x0_QFontMetricsF_height(Ref<QFontMetrics> self) {
  return self->height();
}

double illusory0x0_QRectF_left(Ref<QRectF> self) { return self->left(); }
double illusory0x0_QRectF_right(Ref<QRectF> self) { return self->right(); }
double illusory0x0_QRectF_top(Ref<QRectF> self) { return self->top(); }
double illusory0x0_QRectF_bottom(Ref<QRectF> self) { return self->bottom(); }

double illusory0x0_QSizeF_width(Ref<QSizeF> self) { return self->width(); }
double illusory0x0_QSizeF_height(Ref<QSizeF> self) { return self->height(); }

double illusory0x0_QPointF_x(Ref<QPointF> self) { return self->x(); }
double illusory0x0_QPointF_y(Ref<QPointF> self) { return self->y(); }
double illusory0x0_Window_devicePixelRatioF(Ref<Window> self) {
  return self->devicePixelRatioF();
}
int32_t illusory0x0_QApplication_exec() { return QApplication::exec(); }
void illusory0x0_Window_update(Ref<Window> self) { self->update(); }

} // namespace end