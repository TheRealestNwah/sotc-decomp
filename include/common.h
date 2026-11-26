#ifndef COMMON_H
#define COMMON_H

/* Base types for the Game modules' C (ee-gcc 2.96, EE: int 4 bytes, long 8). */
typedef signed char s8;
typedef unsigned char u8;
typedef short s16;
typedef unsigned short u16;
typedef int s32;
typedef unsigned int u32;
typedef long long s64;
typedef unsigned long long u64;
typedef int s128 __attribute__((mode(TI)));
typedef unsigned int u128 __attribute__((mode(TI)));
typedef float f32;

/* The Sony SDK's names (eetypes.h) for the same widths. */
typedef unsigned long long u_long64;
typedef unsigned int u_long128 __attribute__((mode(TI)));

#ifndef NULL
#define NULL ((void *)0)
#endif

#endif /* COMMON_H */
