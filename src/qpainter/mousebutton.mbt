///|
enum MouseButton {
  No = 0x00000000
  All = 0x07ffffff
  Left = 0x00000001
  Right = 0x00000002
  Middle = 0x00000004
} derive(Debug)

///|
#deprecated
pub extend MouseButton with @debug.Debug::{to_repr}

///|
pub impl Show for MouseButton with fn output(self, logger) {
  logger.write_string(@debug.to_string(self))
}

///|
pub extend MouseButton with Show::{to_string, output}
