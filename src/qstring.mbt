///|
#borrow(self)
extern "c" fn QString::to_string(self : QString) -> String = "illusory0x0_QString_to_moonbit_string"

///|
fn QString::from_builtin(str : String) -> QString {
  QString::new(str)
}
