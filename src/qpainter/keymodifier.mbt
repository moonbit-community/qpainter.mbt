///|
enum KeyModifier {
  No = 0x00000000
  Shift = 0x02000000
  Control = 0x04000000
  Alt = 0x08000000
  Meta = 0x10000000
  Keypad = 0x20000000
  GroupSwitch = 0x40000000
} derive(Debug)
// FIXME: derive show is wrong, not handle bitwise or case

///|
#deprecated
pub extend KeyModifier with @debug.Debug::{to_repr}

///|
pub impl Show for KeyModifier with fn output(self, logger) {
  logger.write_string(@debug.to_string(self))
}

///|
pub extend KeyModifier with Show::{to_string, output}
