/* Khronos platform-specific types for glad */
#ifndef KHRPLATFORM_H
#define KHRPLATFORM_H

#ifdef __cplusplus
extern "C" {
#endif

/* Define basic types if not provided by the platform headers */
#if defined(_WIN32) || defined(__CYGWIN__)
typedef unsigned long khronos_uintptr_t;
#else
#include <stddef.h>
typedef unsigned long khronos_uintptr_t;
#endif

#ifdef __cplusplus
}
#endif

#endif /* KHRPLATFORM_H */
