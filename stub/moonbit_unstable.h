#pragma once

#ifdef moonbit_h_INCLUDED
#error "moonbit.h included multiple times"
#endif 

#include <cstdint>
extern "C" {
  #include <moonbit.h>
  // from ~/.moon/lib/runtime.c
  MOONBIT_EXPORT void *moonbit_malloc_array(enum moonbit_block_kind kind, int elem_size_shift, int32_t len);
}

using moonbit_char_t = int32_t;

using moonbit_bool_t = int;