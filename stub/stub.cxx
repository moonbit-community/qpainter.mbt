#include "QtCore/qdebug.h"
#include "QtCore/qglobal.h"
#include "QtGui/qpainter.h"
#include "QtWidgets/qapplication.h"
#include "moonbit_unstable.h"
#include <QtGui/QtGui>
#include <QtWidgets/QtWidgets>
#include <cstdint>
#include <cstring>
#include <cstring>
#include <string>
#include <vector>

// illusory0x0_

using CodePoint = uint32_t;

template <typename T> void finalize(void *obj) {
  auto self = (T *)obj;
  self->~T();
}

template <typename T> T *make_external_object() {
  return (T *)moonbit_make_external_object(finalize<T>, sizeof(T));
}


using paint_handler = void (*)(QPainter *painter);


struct Window : QWidget {
  paint_handler paint;
  Window(void (*paint)(QPainter *painter)) : QWidget(), paint(paint) {}
  virtual void paintEvent(QPaintEvent *event) {
    QPainter p{this};
    this->paint(&p);
  }
  ~Window() = default;
};

extern "C" {
// constructors
QApplication *illusory0x0_QApplication_new(int32_t *argc, char **argv) {
  auto self = make_external_object<QApplication>();
  return new (self) QApplication(*argc, argv);
}

Window *illusory0x0_Window_new(paint_handler paint) {
  auto self = make_external_object<Window>();
  return new (self) Window(paint);
}

QPainter *illusory0x0_QPainter_new(QPaintDevice *device) {
  auto self = make_external_object<QPainter>();
  return new (self) QPainter(device);
}
QColor *illusory0x0_QColor_new(int32_t r, int32_t g, int32_t b, int32_t a) {
  auto self = make_external_object<QColor>();
  return new (self) QColor(r, g, b, a);
}
QString *illusory0x0_QString_new(uint16_t *utf16) {
  int32_t len = Moonbit_array_length(utf16);
  auto self = make_external_object<QString>();
  new (self) QString((QChar *)utf16, len);
  return self;
}
std::u16string* illusory0x0_std_u16string_new(uint16_t *utf16) {
  int32_t len = Moonbit_array_length(utf16);
  auto self = make_external_object<QString>();
  return new (self) std::u16string((char16_t*)utf16,len);
}


QBrush *illusory0x0_QBrush_new(QColor *color) {
  auto self = make_external_object<QBrush>();
  return new (self) QBrush(*color);
}
QPen *illusory0x0_QPen_new(QBrush *brush, double width) {
  auto self = make_external_object<QPen>();
  return new (self) QPen(*brush, width);
}
QFontMetricsF *illusory0x0_QFontMetricsF_new(QFont *font) {
  auto self = make_external_object<QFontMetrics>();
  return new (self) QFontMetricsF(*font);
}

QStringList *illusory0x0_QStringList_new(QString** src) {
  auto len = Moonbit_array_length(src);
  auto self = make_external_object<QStringList>();

  new (self) QStringList(len);
  for (int i = 0; i < len; i++) {
    (*self)[i] = *src[i];
  }
  return self;
}

std::vector<std::u16string> *illusory0x0_std_vector_std_u16string_new(std::u16string** src) {
  auto len = Moonbit_array_length(src);
  auto self = make_external_object<std::vector<std::u16string>>();
  new (self) std::vector<std::u16string>(len);
  for (int i = 0; i < len; i++) {
    (*self)[i] = *src[i];
  }
  return self;
}
QFont *illusory0x0_QFont_new(QStringList *families, int32_t size,
                             int32_t weight, moonbit_bool_t italic) {
  auto self = make_external_object<QFont>();
  new (self) QFont(*families, size, weight, italic);
  qDebug() << *self;
  return self;
}
QRectF *illusory0x0_QRectF_new(double x, double y, double w, double h) {
  auto self = make_external_object<QRectF>();
  return new (self) QRectF(x, y, w, h);
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
moonbit_string_t illusory0x0_QString_to_moonbit_string(QString *self) {
  auto len = self->size();
  uint16_t *dest =
      (uint16_t *)moonbit_malloc_array(moonbit_BLOCK_KIND_VAL_ARRAY, 1, len);
  memcpy(dest, self->data(), len);
  return dest;
}

// methods
void illusory0x0_QPainter_setBrush(QPainter *self, QBrush *brush) {
  self->setBrush(*brush);
}

void illusory0x0_QPainter_setPen(QPainter *self, QPen *pen) {
  self->setPen(*pen);
}

void illusory0x0_QPainter_setFont(QPainter *self, QFont *font) {
  self->setFont(*font);
}

void illusory0x0_QPainter_drawRect(QPainter *self, double x, double y, double w,
                                   double h) {
  self->drawRect(QRectF(x, y, w, h));
}

void illusory0x0_QPainter_eraseRect(QPainter *self, double x, double y,
                                    double w, double h) {
  self->eraseRect(QRectF(x, y, w, h));
}

void illusory0x0_QPainter_drawText(QPainter *self, double x, double y,
                                   QString *text) {
  self->drawText(QPointF(x, y), *text);
}

void illusory0x0_QPainter_save(QPainter *self) { self->save(); }
void illusory0x0_QPainter_restore(QPainter *self) { self->restore(); }

void illusory0x0_QPainter_setOpacity(QPainter *self, double opacity) {
  self->setOpacity(opacity);
}
void illusory0x0_Window_show(Window *self) { self->show(); }
int32_t illusory0x0_Window_width(Window *self) { return self->width(); }
int32_t illusory0x0_Window_height(Window *self) { return self->height(); }

moonbit_bool_t illusory0x0_QFontMetricsF_inFontUcs4(QFontMetricsF *self,
                                                    moonbit_char_t codepoint) {
  return self->inFontUcs4(codepoint);
}

QRectF *illusory0x0_QFontMetricsF_boundingRect(QFontMetricsF *self,
                                               QString *text) {
  auto res = make_external_object<QRectF>();
  new (res) QRectF(self->boundingRect(*text));
  return res;
}

double illusory0x0_QFontMetricsF_horizontalAdvance(QFontMetricsF *self,
                                                   QString *text) {
  return self->horizontalAdvance(*text);
}
double illusory0x0_QFontMetricsF_height(QFontMetricsF *self) {
  return self->height();
}

double illusory0x0_QRectF_left(QRectF *self) { return self->left(); }
double illusory0x0_QRectF_right(QRectF *self) { return self->right(); }
double illusory0x0_QRectF_top(QRectF *self) { return self->top(); }
double illusory0x0_QRectF_bottom(QRectF *self) { return self->bottom(); }

double illusory0x0_QSizeF_width(QSizeF *self) { return self->width(); }
double illusory0x0_QSizeF_height(QSizeF *self) { return self->height(); }

double illusory0x0_QPointF_x(QPointF *self) { return self->x(); }
double illusory0x0_QPointF_y(QPointF *self) { return self->y(); }
double illusory0x0_Window_devicePixelRatioF(Window *self) {
  return self->devicePixelRatioF();
}
int32_t illusory0x0_QApplication_exec() {
  return QApplication::exec();
}

} // namespace end