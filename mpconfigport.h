#ifndef __MP_CONFIG_PORT_H__
#define __MP_CONFIG_PORT_H__

#include <stdint.h>

// GC Heap Size
#define MICOPY_HEAP_SIZE 40960

// Python internal features.
#define MICROPY_ENABLE_GC                       (1)
#define MICROPY_HELPER_REPL                     (1)
#define MICROPY_ERROR_REPORTING                 (MICROPY_ERROR_REPORTING_TERSE)
#define MICROPY_FLOAT_IMPL                      (MICROPY_FLOAT_IMPL_FLOAT)

// Fine control over Python builtins, classes, modules, etc.
#define MICROPY_PY_ASYNC_AWAIT                  (1)
#define MICROPY_PY_BUILTINS_SET                 (1)
#define MICROPY_PY_ATTRTUPLE                    (1)
#define MICROPY_PY_COLLECTIONS                  (1)
#define MICROPY_PY_MATH                         (1)
#define MICROPY_PY_IO                           (1)
#define MICROPY_PY_STRUCT                       (1)

// Type definitions for the specific machine.

typedef intptr_t mp_int_t; // pointer size
typedef uintptr_t mp_uint_t; // pointer size
typedef long mp_off_t;

// We need to provide a declaration/definition of alloca().
#include <alloca.h>

// port's name and hardware.
#define MICROPY_HW_BOARD_NAME "example-unix"
#define MICROPY_HW_MCU_NAME   "unknown-cpu"

#define MP_STATE_PORT MP_STATE_VM

#endif
