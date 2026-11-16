#ifdef NONMATCHING /* parked draft: 80 diffs; 0 spill-slot order f8/f20 swapped, f1 ternary lacks xori, sp-relative matrix store ok */
typedef int s128 __attribute__((mode(TI)));

extern float IdentityQuaternion[4];
extern char *iosMallocAlign(int, int, int);
extern void iosCopyMatrix(char *, float *);

int func_000743D0(int heap, char *obj, float *mat, int unused, int count, unsigned flags)
{
    float tmp[16];
    char *p;
    int size;
    int i;
    int f1 = flags & 1;
    int f2 = flags & 2;
    int f4 = flags & 4;
    int f8 = flags & 8;
    int f10 = flags & 0x10;
    int f20 = flags & 0x20;
    int f40 = flags & 0x40;
    int f80 = flags & 0x80;

    size = 0;
    if (f2)
        size += count * 64;
    if (f4)
        size += count * 64;
    if (f10)
        size += count * 64;
    if (f20)
        size += count * 64;
    if (f8)
        size += count * 64;
    if (f40)
        size += count * 64;
    if (f80)
        size += count * 64;
    if (f1)
        size += count * 16;
    p = iosMallocAlign(heap, size, 16);
    obj[0x1BC] = (char)flags;
    if (p == 0)
        return 0;
    if (f2) {
        *(char **)(obj + 0x158) = p;
        p += count * 64;
    } else {
        *(char **)(obj + 0x158) = 0;
    }
    if (f4) {
        *(char **)(obj + 0x15C) = p;
        p += count * 64;
    } else {
        *(char **)(obj + 0x15C) = 0;
    }
    if (f10) {
        *(char **)(obj + 0x164) = p;
        p += count * 64;
    } else {
        *(char **)(obj + 0x164) = 0;
    }
    if (f20) {
        *(char **)(obj + 0x168) = p;
        p += count * 64;
    } else {
        *(char **)(obj + 0x168) = 0;
    }
    if (f8) {
        *(char **)(obj + 0x160) = p;
        p += count * 64;
    } else {
        *(char **)(obj + 0x160) = 0;
    }
    if (f40) {
        *(char **)(obj + 0x16C) = p;
        p += count * 64;
    } else {
        *(char **)(obj + 0x16C) = 0;
    }
    if (f80) {
        *(char **)(obj + 0x170) = p;
        p += count * 64;
    } else {
        *(char **)(obj + 0x170) = 0;
    }
    p = f1 ? p : (char *)0;
    *(char **)(obj + 0x154) = p;
    __asm__ __volatile__("lqc2 vf24, 0x30(%0)\n"
                         "vsubw.x vf25, vf0, vf0w\n"
                         "vmulx.xyz vf28, vf24, vf25x\n"
                         "vsub.w vf28, vf28, vf28\n"
                         "lq $8, 0x0(%0)\n"
                         "lq $9, 0x10(%0)\n"
                         "lq $10, 0x20(%0)\n"
                         "qmfc2.ni $11, vf0\n"
                         "pextlw $12, $9, $8\n"
                         "pextuw $13, $9, $8\n"
                         "pextlw $14, $11, $10\n"
                         "pextuw $15, $11, $10\n"
                         "pcpyld $8, $14, $12\n"
                         "pcpyud $9, $12, $14\n"
                         "pcpyld $10, $15, $13\n"
                         "pcpyud $11, $13, $15\n"
                         "qmtc2.ni $8, vf24\n"
                         "qmtc2.ni $9, vf25\n"
                         "qmtc2.ni $10, vf26\n"
                         "vmulax.xyzw ACC, vf24, vf28x\n"
                         "vmadday.xyzw ACC, vf25, vf28y\n"
                         "vmaddaz.xyzw ACC, vf26, vf28z\n"
                         "vmaddw.xyzw vf29, vf0, vf28w\n"
                         "vsub.w vf29, vf29, vf29\n"
                         "vadd.w vf29, vf29, vf0\n"
                         "sqc2 vf24, 0x0(%0)\n"
                         "sqc2 vf25, 0x10(%0)\n"
                         "sqc2 vf26, 0x20(%0)\n"
                         "sqc2 vf29, 0x30(%0)\n"
                         : : "r"(mat), "m"(tmp[0]) : "$8", "$9", "$10", "$11", "$12", "$13", "$14", "$15", "memory");
    if (f1 && count > 0) {
        for (i = 0; i < count; i++)
            *(s128 *)(*(char **)(obj + 0x154) + i * 16) = *(s128 *)IdentityQuaternion;
    }
    if (f2 && count > 0) {
        for (i = 0; i < count; i++)
            iosCopyMatrix(*(char **)(obj + 0x158) + i * 64, mat);
    }
    return 1;
}
#endif
