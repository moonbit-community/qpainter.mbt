///|
pub fn QStringList::from_builtin(xs : FixedArray[String]) -> QStringList {
  QStringList::new(xs.map(QString::from_builtin))
}
