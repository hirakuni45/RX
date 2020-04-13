#pragma once

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef PATH_MAX
#define PATH_MAX 256
#endif

/* Define this if running on little-endian (x86) systems */
#define  HOST_LITTLE_ENDIAN

#ifdef __GNUC__
#define  INLINE      static inline
#elif defined(WIN32)
#define  INLINE      static __inline
#else /* crapintosh? */
#define  INLINE      static
#endif

/* quell stupid compiler warnings */
#define  UNUSED(x)   ((x) = (x))

typedef  int8_t    int8;
typedef  int16_t   int16;
typedef  int32_t   int32;
typedef  uint8_t   uint8;
typedef  uint16_t  uint16;
typedef  uint32_t  uint32;

#ifndef __cplusplus
typedef enum
{
   false = 0,
   true = 1
} bool;
#endif /* !__cplusplus */

#include "log.h"

#ifndef NDEBUG

#define  ASSERT(expr)      log_assert((int) (expr), __LINE__, __FILE__, NULL)
#define  ASSERT_MSG(msg)   log_assert(false, __LINE__, __FILE__, (msg))

#else /* !NOFRENDO_DEBUG */

#define  ASSERT(expr)
#define  ASSERT_MSG(msg)

#endif /* !NOFRENDO_DEBUG */
