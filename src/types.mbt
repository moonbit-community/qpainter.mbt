///|
type QApplication

///|



///|
type Window

///| Don't store QPainter in other place, only use it in paintEvent
extern type QPainter

///|
type QColor

///|
type QString

///|
type QPen

///|
type QBrush

///|
type QStringList

///|
type QPointF

///|
type QSizeF

///|
type QRectF


type QFont 


type QFontMetricsF 


trait Drop { }

fn drop(xs : FixedArray[&Drop]) -> Unit {

}