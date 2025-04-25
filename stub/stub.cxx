#include <QApplication>
#include <QFont>
#include <QPainter>
#include <QWidget>

#include "moonbit_cxx_borrow.h"
#include "type_holes.h"

using namespace type_holes;
using namespace moonbit::types;

#define let auto

// illusory0x0_

template <typename T> void finalize(void *obj) {
  auto self = (T *)obj;
  self->~T();
}

template <typename T> T *make_external_object() {
  return (T *)moonbit_make_external_object(finalize<T>, sizeof(T));
}

using PaintHandler = Closure<Unit, Ref<QPainter>>;

struct Window : QWidget {
  PaintHandler paint;
  Window(PaintHandler p) : QWidget(), paint(p) {}
  virtual void paintEvent(QPaintEvent *event) noexcept override {
    let painter = Ref<QPainter>::from_cxx_ref(this);
    this->paint(painter);
    painter.decrement_strong_count();
  }
  ~Window() = default;
};

using Bytes = FixedArray<Byte>;

// // use explicit template instantiation
// // https://github.com/llvm/llvm-project/issues/137282#issue-3018926539
// namespace moonbit {
// namespace basic_types {
// extern template struct Ref<QApplication>;
// extern template struct Ref<Window>;
// extern template struct Ref<Window>;
// extern template struct Ref<QPainter>;
// extern template struct Ref<QColor>;
// extern template struct Ref<QFont>;
// extern template struct Ref<QFontMetricsF>;
// extern template struct Ref<QPointF>;
// extern template struct Ref<QRectF>;
// extern template struct Ref<Int>;
// extern template struct Ref<QStringList>;
// } // namespace basic_types
// namespace compound_types {
// extern template struct FixedArray<Bytes>;
// extern template struct FixedArray<Ref<QString>>;

// } // namespace compound_types
// } // namespace moonbit

extern "C" {

// constructors
Ref<QApplication> illusory0x0_QApplication_new(Ref<Int> argc,
                                               FixedArray<Bytes> argv) {
  return Ref<QApplication>::from_cxx_ref(argc->repr,
                                         ::std::bit_cast<char **>(argv));
}

Ref<Window> illusory0x0_Window_new(PaintHandler paint) {
  return Ref<Window>::from_cxx_ref(paint);
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

QBrush *illusory0x0_QBrush_new(Ref<QColor> color) {
  auto self = make_external_object<QBrush>();
  return new (self) QBrush(*color);
}
QPen *illusory0x0_QPen_new(QBrush *brush, double width) {
  auto self = make_external_object<QPen>();
  return new (self) QPen(*brush, width);
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
QSizeF *illusory0x0_QSizeF_new(double w, double h) {
  auto self = make_external_object<QSizeF>();
  return new (self) QSizeF(w, h);
}
QPointF *illusory0x0_QPointF_new(double x, double y) {
  auto self = make_external_object<QPointF>();
  return new (self) QPointF(x, y);
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
void illusory0x0_QPainter_setBrush(Ref<QPainter> self, QBrush *brush) {
  self->setBrush(*brush);
}

void illusory0x0_QPainter_setPen(Ref<QPainter> self, QPen *pen) {
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

double illusory0x0_QSizeF_width(QSizeF *self) { return self->width(); }
double illusory0x0_QSizeF_height(QSizeF *self) { return self->height(); }

double illusory0x0_QPointF_x(QPointF *self) { return self->x(); }
double illusory0x0_QPointF_y(QPointF *self) { return self->y(); }
double illusory0x0_Window_devicePixelRatioF(Ref<Window> self) {
  return self->devicePixelRatioF();
}
int32_t illusory0x0_QApplication_exec() { return QApplication::exec(); }

} // namespace end