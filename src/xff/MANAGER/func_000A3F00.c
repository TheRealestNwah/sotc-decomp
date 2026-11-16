#ifdef NONMATCHING /* parked draft: 155 diffs, VU0 runs in place (roughly wired) */
extern int ClipCollisionDB(int, int, int, int *);
extern void *GetLayoutClass(int);
extern void func_000999E0(int *, int *, void *, int, int);
extern void func_0009AE78(int *, int *, int, int, int, int, int, int);
extern void EntryModifiedManager(void *, int);

int func_000A3F00(int a0, int a1, int a2, int a3, int *key)
{
    int hit;
    int *s0p;
    int idx, kind, packed;
    char *cls;
    char *entry;
    char *rec;
    float *dst;
    int p1[4];
    int p2[4];
    int *v0p, *v1p, *v2p;

    hit = ClipCollisionDB(a0, a2, a3, key);
    if (hit == 0)
        return 0;
    packed = key[1];
    cls = (char *)GetLayoutClass(key[0]);
    idx = (packed >> 24) & 0x7F;
    kind = packed & 0xFFFFFF;
    if (key[1] >= 0) {
        entry = (char *)*(int *)(*(int *)(cls + 0x174) + 0x24) + idx * 96 + 0x30;
        rec = (char *)*(int *)(entry + 0x14);
        if (*(unsigned char *)(*(int *)(entry + 8) + kind) != 0)
            return hit;
        dst = (float *)(rec + kind * 16);
        func_000999E0(p1, p2, cls, idx, kind);
        v0p = (int *)p1[0];
        v1p = (int *)p1[1];
        v2p = (int *)p2[0];
        __asm__ __volatile__("lqc2 vf29, 0x0(%0)\n"
                         : : "r"(v0p) : "memory");
        __asm__ __volatile__("lqc2 vf30, 0x0(%0)\n"
                         "vsub.xyzw vf31, vf29, vf30\n"
                         "vmove.xyzw vf18, vf31\n"
                         "vmove.xyzw vf29, vf30\n"
                         : : "r"(v1p) : "memory");
        __asm__ __volatile__("lqc2 vf30, 0x0(%0)\n"
                         "vsub.xyzw vf31, vf29, vf30\n"
                         "vmove.xyzw vf29, vf18\n"
                         "vmove.xyzw vf30, vf31\n"
                         "vopmula.xyz ACC, vf29, vf30\n"
                         "vopmsub.xyz vf31, vf30, vf29\n"
                         "vsub.w vf31, vf31, vf31\n"
                         "vmove.xyzw vf29, vf31\n"
                         "vmul.xyz vf7, vf29, vf29\n"
                         "vmulax.w ACC, vf0, vf7x\n"
                         "vmadday.w ACC, vf0, vf7y\n"
                         "vmaddz.w vf7, vf0, vf7z\n"
                         "vrsqrt Q, vf0w, vf7w\n"
                         "vwaitq\n"
                         "vmulq.xyz vf29, vf29, Q\n"
                         "vmove.xyzw vf31, vf29\n"
                         "sqc2 vf31, 0x0(%1)\n"
                         : : "r"(v2p), "r"(dst) : "memory");
        __asm__ __volatile__("lqc2 vf4, 0x0(%0)\n"
                         "lqc2 vf5, 0x0(%1)\n"
                         "vmul.xyz vf5, vf4, vf5\n"
                         "vaddy.x vf5, vf5, vf5y\n"
                         "vaddz.x vf5, vf5, vf5z\n"
                         "vsubw.xyzw vf6, vf0, vf0w\n"
                         "vsubx.w vf4, vf6, vf5x\n"
                         "sqc2 vf4, 0x0(%0)\n"
                         : : "r"(dst), "r"(v0p) : "memory");
        EntryModifiedManager(entry, kind);
    } else {
        entry = (char *)*(int *)(cls + 0x174) + 0x58;
        idx = *(int *)(*(int *)(*(int *)(*(int *)(cls + 0x184) + 0x20) + 8) + idx * 144 + 0x54 + kind * 4);
        if (*(unsigned char *)(*(int *)(entry + 8) + idx) != 0)
            return hit;
        dst = (float *)(*(char **)(entry + 0x14) + idx * 16);
        func_0009AE78(p1, p2, 0, 0, 0, 0, 0, 0);
        v0p = (int *)p1[0];
        v1p = (int *)p1[1];
        v2p = (int *)p2[0];
        __asm__ __volatile__("lqc2 vf29, 0x0(%0)\n"
                         : : "r"(v0p) : "memory");
        __asm__ __volatile__("lqc2 vf30, 0x0(%0)\n"
                         "vsub.xyzw vf31, vf29, vf30\n"
                         "vmove.xyzw vf18, vf31\n"
                         "vmove.xyzw vf29, vf30\n"
                         : : "r"(v1p) : "memory");
        __asm__ __volatile__("lqc2 vf30, 0x0(%0)\n"
                         "vsub.xyzw vf31, vf29, vf30\n"
                         "vmove.xyzw vf29, vf18\n"
                         "vmove.xyzw vf30, vf31\n"
                         "vopmula.xyz ACC, vf29, vf30\n"
                         "vopmsub.xyz vf31, vf30, vf29\n"
                         "vsub.w vf31, vf31, vf31\n"
                         "vmove.xyzw vf29, vf31\n"
                         "vmul.xyz vf7, vf29, vf29\n"
                         "vmulax.w ACC, vf0, vf7x\n"
                         "vmadday.w ACC, vf0, vf7y\n"
                         "vmaddz.w vf7, vf0, vf7z\n"
                         "vrsqrt Q, vf0w, vf7w\n"
                         "vwaitq\n"
                         "vmulq.xyz vf29, vf29, Q\n"
                         "vmove.xyzw vf31, vf29\n"
                         "sqc2 vf31, 0x0(%1)\n"
                         : : "r"(v2p), "r"(dst) : "memory");
        __asm__ __volatile__("lqc2 vf4, 0x0(%0)\n"
                         "lqc2 vf5, 0x0(%1)\n"
                         "vmul.xyz vf5, vf4, vf5\n"
                         "vaddy.x vf5, vf5, vf5y\n"
                         "vaddz.x vf5, vf5, vf5z\n"
                         "vsubw.xyzw vf6, vf0, vf0w\n"
                         "vsubx.w vf4, vf6, vf5x\n"
                         "sqc2 vf4, 0x0(%0)\n"
                         : : "r"(dst), "r"(v0p) : "memory");
        EntryModifiedManager(entry, idx);
    }
    return hit;
}
#endif
