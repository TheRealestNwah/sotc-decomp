#ifndef KERNEL_SG2SEP_H
#define KERNEL_SG2SEP_H

/* KERNEL Sg2 sequences (src/xff/KERNEL/Sg2Sep*.c, debug_sep_config.c): the 32
 * sequence entries in B_000DD700, 0x50 bytes each. xNN fields are not
 * understood yet. */

/* Soft-float double, also read as its raw 64-bit pattern. */
typedef union {
    long l;
    double d;
} SepTime;

typedef struct Sep {
    int status; /* 0 free, 2 stopped */
    int previous;
    int serial;
    int vab;
    int mod;
    int seq;
    int flags;
    int x1C;
    SepTime tick;  /* 0x20 */
    SepTime time;  /* 0x28 */
    SepTime count; /* 0x30 */
    int x38;
    int data;
    unsigned char *ptr;
    unsigned char skip;
    char pad45[3];
    unsigned int cmd;
    int x4C;
} Sep;

extern Sep B_000DD700[32];

#endif /* KERNEL_SG2SEP_H */
