#ifdef NONMATCHING /* 141 diffs (166 vs 168 words): draft with all VU0 runs; switch body groups from the jump table (48 entries); frame 0xC0 vs 0xB0 (union temps), saved-reg numbering */
typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; int i[4]; } Vec4;

extern void GetTRS_Onake_From_ObjectAnimation(int *, Vec4 *, Vec4 *, Vec4 *, Vec4 *);

void InterPOrObjectAnimation(int *obj, Vec4 *v1, Vec4 *v2, Vec4 *v3, Vec4 *v4, float t)
{
    Vec4 buf[6];
    union { float f; int i; } ti, ng;
    float dot;

    GetTRS_Onake_From_ObjectAnimation(obj, &buf[0], &buf[1], &buf[2], &buf[3]);
    ti.f = t;
    __asm__ __volatile__("qmtc2.ni %0, vf7\n"
                         "lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsubx.w vf8, vf0, vf7x\n"
                         "vmulax.xyzw ACC, vf5, vf7x\n"
                         "vmaddw.xyzw vf9, vf6, vf8w\n"
                         "sqc2 vf9, 0x0(%3)\n"
                         : : "r"(ti.i), "r"(v1), "r"(&buf[0]), "r"(&buf[0]) : "memory");
    buf[4].q = buf[1].q;
    __asm__ __volatile__("lqc2 vf14, 0x0(%1)\n"
                         "lqc2 vf15, 0x0(%2)\n"
                         "vmul.xyzw vf15, vf14, vf15\n"
                         "vaddy.x vf15, vf15, vf15y\n"
                         "vaddz.x vf15, vf15, vf15z\n"
                         "vaddw.x vf15, vf15, vf15w\n"
                         "qmfc2.ni $2, vf15\n"
                         "mtc1 $2, %0\n"
                         : "=f"(dot) : "r"(v2), "r"(&buf[4]) : "$2", "memory");
    buf[5].f[0] = dot;
    if (buf[5].i[0] < 0) {
        ng.f = -1.0f;
        __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                         "qmtc2.ni %1, vf6\n"
                         "vmulx.xyzw vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0x0(%0)\n"
                             : : "r"(&buf[4]), "r"(ng.i) : "memory");
    }
    __asm__ __volatile__("qmtc2.ni %0, vf7\n"
                         "lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsubx.w vf8, vf0, vf7x\n"
                         "vmulax.xyzw ACC, vf5, vf7x\n"
                         "vmaddw.xyzw vf9, vf6, vf8w\n"
                         "sqc2 vf9, 0x0(%3)\n"
                         : : "r"(ti.i), "r"(v2), "r"(&buf[4]), "r"(&buf[1]) : "memory");
    __asm__ __volatile__("qmtc2.ni %0, vf7\n"
                         "lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsubx.w vf8, vf0, vf7x\n"
                         "vmulax.xyzw ACC, vf5, vf7x\n"
                         "vmaddw.xyzw vf9, vf6, vf8w\n"
                         "sqc2 vf9, 0x0(%3)\n"
                         : : "r"(ti.i), "r"(v3), "r"(&buf[2]), "r"(&buf[2]) : "memory");
    __asm__ __volatile__("qmtc2.ni %0, vf7\n"
                         "lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsubx.w vf8, vf0, vf7x\n"
                         "vmulax.xyzw ACC, vf5, vf7x\n"
                         "vmaddw.xyzw vf9, vf6, vf8w\n"
                         "sqc2 vf9, 0x0(%3)\n"
                         : : "r"(ti.i), "r"(v4), "r"(&buf[3]), "r"(&buf[3]) : "memory");
    switch (*obj - 1) {
    case 0: case 4:
        *(s128 *)(obj + 4) = buf[0].q;
        obj[16] = buf[3].i[0];
        *(s128 *)(obj + 8) = buf[1].q;
        *(s128 *)(obj + 12) = buf[2].q;
        break;
    case 44:
        *(s128 *)(obj + 4) = buf[0].q;
        obj[20] = buf[3].i[0];
        *(s128 *)(obj + 8) = buf[1].q;
        break;
    case 1: case 6: case 8: case 10: case 37:
        *(s128 *)(obj + 4) = buf[0].q;
        *(s128 *)(obj + 8) = buf[1].q;
        break;
    case 2:
        *(s128 *)(obj + 4) = buf[0].q;
        *(s128 *)(obj + 8) = buf[2].q;
        break;
    case 11:
        *(s128 *)(obj + 4) = buf[0].q;
        break;
    case 3: case 9: case 13: case 14: case 15: case 16: case 17: case 18: case 19: case 20:
    case 21: case 22: case 23: case 24: case 31: case 47:
        *(s128 *)(obj + 4) = buf[0].q;
        *(s128 *)(obj + 12) = buf[2].q;
        *(s128 *)(obj + 8) = buf[1].q;
        break;
    case 25:
        *(s128 *)(obj + 4) = buf[1].q;
        obj[12] = buf[3].i[1];
        obj[8] = buf[2].i[1];
        obj[10] = buf[2].i[3];
        obj[11] = buf[3].i[0];
        break;
    case 5: case 26: case 27: case 32: case 33: case 34:
        *(s128 *)(obj + 4) = buf[0].q;
        obj[16] = buf[3].i[1];
        *(s128 *)(obj + 8) = buf[1].q;
        obj[13] = buf[2].i[0];
        obj[12] = buf[2].i[1];
        obj[14] = buf[2].i[3];
        obj[15] = buf[3].i[0];
        break;
    default:
        break;
    }
}
#endif
