#ifdef NONMATCHING /* 37 diffs: callee-saved registers for flag/vec/pos come out in a different order (permuter best 180); VU0 text matches */
typedef float Vec4[4] __attribute__((aligned(16)));

extern char *GetCharacterClass(int);
extern void UnlinkSecureParentInfo(void *);
extern void GetGeometryPointerPosition(void *, void *);

void charrootdyn_restoreposition(float *out, int id, float *quat, float *pos, float *vec, int flag)
{
    Vec4 delta;
    Vec4 rot;
    Vec4 cur;
    Vec4 neg;
    unsigned int **pp;
    char *cc = GetCharacterClass(id);

    pp = (unsigned int **)(cc + 0x1C0);
    if (flag == 0) {
        UnlinkSecureParentInfo(cc + 0x1020);
    }
    if (*(int *)(cc + 0x106C) != 0 && (((*pp)[0x68 / 4] >> 25) & 1) && flag != 0) {
        float negOne = -1.0f;
        __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                         "qmtc2.ni %1, vf6\n"
                         "vmulx.xyz vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0x0(%2)\n"
                         "lqc2 vf8, 0x0(%2)\n"
                         "lqc2 vf18, 0x0(%3)\n"
                         "vmove.w vf18, vf0\n"
                         "vaddw.xyz vf12, vf0, vf0w\n"
                         "lqc2 vf11, 0x0(%4)\n"
                         "vmr32.w vf14, vf0\n"
                         "vmr32.w vf15, vf0\n"
                         "vmr32.w vf16, vf0\n"
                         "vopmula.xyz ACC, vf11, vf12\n"
                         "vmadd.xyz vf11, vf0, vf0\n"
                         "vmadd.xyz vf10, vf11, vf12\n"
                         "vmul.xyz vf13, vf11, vf10\n"
                         "vopmula.xyz ACC, vf11, vf10\n"
                         "vmaddw.xyz vf15, vf10, vf11w\n"
                         "vmsubw.xyz vf16, vf10, vf11w\n"
                         "vopmula.xyz ACC, vf13, vf12\n"
                         "vmadd.xyz vf17, vf13, vf12\n"
                         "vopmula.xyz ACC, vf15, vf12\n"
                         "vmadd.xyz vf15, vf0, vf0\n"
                         "vsub.xyz vf14, vf12, vf17\n"
                         "vmove.yz vf17, vf14\n"
                         "vmove.y vf14, vf16\n"
                         "vmove.y vf16, vf15\n"
                         "vmove.y vf15, vf17\n"
                         "vmove.z vf14, vf15\n"
                         "vmove.z vf15, vf16\n"
                         "vmove.z vf16, vf17\n"
                         "vmulax.xyzw ACC, vf14, vf8x\n"
                         "vmadday.xyzw ACC, vf15, vf8y\n"
                         "vmaddaz.xyzw ACC, vf16, vf8z\n"
                         "vmaddw.xyzw vf10, vf18, vf8w\n"
                         "sqc2 vf10, 0x0(%5)\n"
                     : 
                     : "r"(vec), "r"(negOne), "r"(neg), "r"(pos), "r"(quat), "r"(rot)
                     : "memory");
        GetGeometryPointerPosition(cur, cc + 0x1020);
        __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                         "lqc2 vf6, 0x0(%1)\n"
                         "vsub.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%2)\n"
                         "lqc2 vf5, 0x0(%3)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vadd.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%4)\n"
                     : 
                     : "r"(cur), "r"(rot), "r"(delta), "r"(pos), "r"(out)
                     : "memory");
    }
}
#endif
