///|
#borrow(self, x, y, w, h)
extern "c" fn QPainter::drawRect(
  self : QPainter,
  x : Double,
  y : Double,
  w : Double,
  h : Double
) -> Unit = "illusory0x0_QPainter_drawRect"

///|
#borrow(self, x, y, text)
extern "c" fn QPainter::drawText(
  self : QPainter,
  x : Double,
  y : Double,
  text : QString
) -> Unit = "illusory0x0_QPainter_drawText"

///|
#borrow(self, pen)
extern "c" fn QPainter::setPen(self : QPainter, pen : QPen) -> Unit = "illusory0x0_QPainter_setPen"

///|
#borrow(self, brush)
extern "c" fn QPainter::setBrush(self : QPainter, brush : QBrush) -> Unit = "illusory0x0_QPainter_setBrush"

///|
#borrow(self, font)
extern "c" fn QPainter::setFont(self : QPainter, font : QFont) -> Unit = "illusory0x0_QPainter_setFont"

#borrow(self, x, y, w, h,xRadius,yRadius)
extern "c" fn QPainter::drawRoundedRect(
  self : QPainter,
  x : Double,
  y : Double,
  w : Double,
  h : Double,
  xRadius : Double,
  yRadius : Double
) -> Unit = "illusory0x0_QPainter_drawRoundedRect"