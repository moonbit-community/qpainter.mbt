///|
#borrow(argc, argv)
extern "c" fn QApplication::new(
  argc : Ref[Int],
  argv : FixedArray[Bytes]
) -> QApplication = "illusory0x0_QApplication_new"

///|
extern "c" fn QApplication::exec() -> Int = "illusory0x0_QApplication_exec"
