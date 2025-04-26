///|
#borrow(self)
pub extern "c" fn QString::to_string(self : QString) -> String = "illusory0x0_QString_to_moonbit_string"

///|
pub fn QString::from_builtin(str : String) -> QString {
  QString::new(str)
}
