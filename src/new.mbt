///|
/// 640 * 480 excluded title bar.
#borrow(paint)
extern "c" fn Window::new(paint : (QPainter) -> Unit) -> Window = "illusory0x0_Window_new"

///|
#borrow(r,g,b,a)
extern "c" fn QColor::new(r : Int, g : Int, b : Int, a : Int) -> QColor = "illusory0x0_QColor_new"

///|
#borrow(str)
extern "c" fn QString::new(str : String) -> QString = "illusory0x0_QString_new"

///|
#borrow(brush,width)
extern "c" fn QPen::new(brush : QBrush, width : Double) -> QPen = "illusory0x0_QPen_new"

///|
#borrow(color)
extern "c" fn QBrush::new(color : QColor) -> QBrush = "illusory0x0_QBrush_new"

///| shadow copy
#borrow(xs)
extern "c" fn QStringList::new(xs : FixedArray[QString]) -> QStringList = "illusory0x0_QStringList_new"



#borrow(width,height)
extern "c" fn QSizeF::new(width : Double, height  : Double) -> QSizeF = "illusory0x0_QSizeF_new"

#borrow(x,y)
extern "c" fn QPointF::new(x : Double, y : Double) -> QPointF = "illusory0x0_QPointF_new"

#borrow(x,y,width,height)
extern "c" fn QRectF::new(x : Double, y : Double, width : Double, height : Double) -> QRectF = "illusory0x0_QRectF_new"

#borrow(families,size,weight,italic)
extern "c" fn QFont::new(
  families : QStringList,
  size : Int, 
  weight : Int, 
  italic : Bool
) -> QFont = "illusory0x0_QFont_new"



type StdString 
type StdVector_StdString


#borrow(str)
extern "c" fn StdString::new(str : String) -> StdString = "illusory0x0_QString_new"
#borrow(xs)
extern "c" fn StdVector_StdString::new(xs : FixedArray[StdString]) -> StdVector_StdString = "illusory0x0_QStringList_new"