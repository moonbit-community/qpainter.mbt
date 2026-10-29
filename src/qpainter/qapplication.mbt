///|
#borrow(argc, argv)
pub extern "c" fn QApplication::new(
  argc : Ref[Int32],
  argv : FixedArray[Bytes],
) -> QApplication = "illusory0x0_QApplication_new"

///|
pub extern "c" fn QApplication::exec() -> Int32 = "illusory0x0_QApplication_exec"
