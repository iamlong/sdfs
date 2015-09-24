#ifndef stdtype_h
#define stdtype_h
  /* TYPE DEFINITIONS */
typedef signed char sd_int8_t;
typedef short sd_int16_t;

typedef int sd_int32_t;
typedef long long sd_int64_t;

typedef unsigned char sd_uint8_t;
typedef unsigned short sd_uint16_t;

typedef unsigned int sd_uint32_t;
typedef unsigned long long sd_uint64_t;

typedef signed char sd_int_least8_t;
typedef short sd_int_least16_t;
typedef long sd_int_least32_t;
typedef long long sd_int_least64_t;

typedef unsigned char sd_uint_least8_t;
typedef unsigned short sd_uint_least16_t;
typedef unsigned long sd_uint_least32_t;
typedef unsigned long long sd_uint_least64_t;

typedef signed char sd_int_fast8_t;
typedef short sd_int_fast16_t;
typedef long sd_int_fast32_t;
typedef long long sd_int_fast64_t;

typedef unsigned char sd_uint_fast8_t;
typedef unsigned short sd_uint_fast16_t;
typedef unsigned long sd_uint_fast32_t;
typedef unsigned long long sd_uint_fast64_t;

typedef long sd_intptr_t;
typedef unsigned long sd_uintptr_t;


typedef long long sd_intmax_t;
typedef unsigned long long sd_uintmax_t;

        /* LIMIT MACROS */
#define SD_INT8_MIN    (-0x7f - 1)
#define SD_INT16_MIN   (-0x7fff - 1)
#define SD_INT32_MIN   (-0x7fffffff - 1)
#define SD_INT64_MIN   (-0x7fffffffffffffff - 1)

#define SD_INT8_MAX    0x7f [exact]
#define SD_INT16_MAX   0x7fff [exact]
#define SD_INT32_MAX   0x7fffffff [exact]
#define SD_INT64_MAX   0x7fffffffffffffff [exact]

#define SD_UINT8_MAX   0xff [exact]
#define SD_UINT16_MAX  0xffff [exact]
#define SD_UINT32_MAX  0xffffffff [exact]
#define SD_UINT64_MAX  0xffffffffffffffff [exact]

#define SD_INT_LEAST8_MIN    (-0x7f - 1)
#define SD_INT_LEAST16_MIN   (-0x7fff - 1)
#define SD_INT_LEAST32_MIN   (-0x7fffffff - 1)
#define SD_INT_LEAST64_MIN   (-0x7fffffffffffffff - 1)

#define SD_INT_LEAST8_MAX    0x7f
#define SD_INT_LEAST16_MAX   0x7fff
#define SD_INT_LEAST32_MAX   0x7fffffff
#define SD_INT_LEAST64_MAX   0x7fffffffffffffff

#define SD_UINT_LEAST8_MAX   0xff
#define SD_UINT_LEAST16_MAX  0xffff
#define SD_UINT_LEAST32_MAX  0xffffffff
#define SD_UINT_LEAST64_MAX  0xffffffffffffffff

#define SD_INT_FAST8_MIN     (-0x7f - 1)
#define SD_INT_FAST16_MIN    (-0x7fff - 1)
#define SD_INT_FAST32_MIN    (-0x7fffffff - 1)
#define SD_INT_FAST64_MIN    (-0x7fffffffffffffff - 1)

#define SD_INT_FAST8_MAX     0x7f
#define SD_INT_FAST16_MAX    0x7fff
#define SD_INT_FAST32_MAX    0x7fffffff
#define SD_INT_FAST64_MAX    0x7fffffffffffffff

#define SD_UINT_FAST8_MAX    0xff
#define SD_UINT_FAST16_MAX   0xffff
#define SD_UINT_FAST32_MAX   0xffffffff
#define SD_UINT_FAST64_MAX   0xffffffffffffffff

#define SD_INTPTR_MIN        (-0x7fffffff - 1)
#define SD_INTPTR_MAX        0x7fffffff
#define SD_UINTPTR_MAX       0xffffffff

#define SD_INT8_C(x)    (x)
#define SD_INT16_C(x)   (x)
#define SD_INT32_C(x)   ((x) + (SD_INT32_MAX - SD_INT32_MAX))
#define SD_INT64_C(x)   ((x) + (SD_INT64_MAX - SD_INT64_MAX))

#define SD_UINT8_C(x)   (x)
#define SD_UINT16_C(x)  (x)
#define SD_UINT32_C(x)  ((x) + (SD_UINT32_MAX - SD_UINT32_MAX))
#define SD_UINT64_C(x)  ((x) + (SD_UINT64_MAX - SD_UINT64_MAX))

#define SD_INTMAX_C(x)  ((x) + (SD_INT64_MAX - SD_INT64_MAX))
#define SD_UINTMAX_C(x) ((x) + (SD_UINT64_MAX - SD_UINT64_MAX))

#define SD_PTRDIFF_MIN  SD_INT32_MIN
#define SD_PTRDIFF_MAX  SD_INT32_MAX

#define SD_SIG_ATOMIC_MIN    SD_INT32_MIN
#define SD_SIG_ATOMIC_MAX    SD_INT32_MAX

#define SD_SIZE_MAX     SD_UINT32_MAX

#define SD_WCHAR_MIN    0
#define SD_WCHAR_MAX    SD_UINT16_MAX

#define SD_WINT_MIN     0
#define SD_WINT_MAX     SD_UINT16_MAX

#define SD_INTMAX_MIN        (-0x7fffffffffffffff - 1)
#define SD_INTMAX_MAX        0x7fffffffffffffff
#define SD_UINTMAX_MAX       0xffffffffffffffff

#endif
