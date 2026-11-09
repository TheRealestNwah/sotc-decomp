typedef int s128 __attribute__((mode(TI)));
typedef struct { long long x, y; } Pair;
typedef float Vec4[4] __attribute__((aligned(16)));

extern s128 IdentityQuaternion;
extern Pair RO_00118A30;
extern void **isysGroupForFirst(void *, int);
extern void isysAddGroupWithLinkParam(void *, void *, int, int);
extern void _isysDeleteGroup(void *, void *, int);
extern void isysGroupForExit(void *, int);
extern void gluGetLookAtPosition(void *, long long, int, float);

/* Parked: ~83 words differ (scheduling of the flags|0x2401 arg and store, constant materialization order, byte stores). Structure and size are close (132 vs 130 words). */
#ifdef NONMATCHING
int NewCreateFogColClass(char *obj, int flags, int arg)
{
    struct { Pair p; s128 pos; Vec4 ext; } L;
    char *fog = 0;
    char *grp = 0;
    int ret = 0;
    void **first;

    first = isysGroupForFirst(obj + 0x98, 0);
    if (first != 0) {
        grp = (char *)*first;
        fog = ((*(unsigned char *)(grp + 8) ^ 0x18) == 0) ? grp + 0x20 : 0;
        isysAddGroupWithLinkParam(grp, obj + 0xA0, 0, 0);
        _isysDeleteGroup(grp, obj + 0x98, 0);
        *(int *)(obj + 0x90) |= 1;
    }
    if (grp != 0)
        isysGroupForExit(grp, 0);
    if (fog != 0) {
        float m;
        int f2 = flags | 0x2401;

        L.p = RO_00118A30;
        *(int *)(fog + 0x40) = f2;
        gluGetLookAtPosition(&L.pos, RO_00118A30.y, f2, 8.0f);
        *(s128 *)fog = L.pos;
        *(s128 *)(fog + 0x10) = IdentityQuaternion;
        *(s128 *)(fog + 0x20) = *(s128 *)&L.p;
        __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                             "qmtc2.ni %2, vf6\n"
                             "vmulx.xyzw vf5, vf5, vf6x\n"
                             "sqc2 vf5, 0x0(%0)\n"
                             : : "r"(fog + 0x30), "r"(fog + 0x20), "r"(1.3f) : "memory");
        *(float *)(fog + 0x64) = 255.0f;
        *(signed char *)(fog + 0x53) = -1;
        *(float *)(fog + 0x58) = 35.0f;
        *(float *)(fog + 0x5C) = 65000.0f;
        *(float *)(fog + 0x68) = 62.0f;
        *(float *)(fog + 0x6C) = 0.5f;
        *(signed char *)(fog + 0x4E) = -1;
        *(signed char *)(fog + 0x4F) = 0;
        *(signed char *)(fog + 0x50) = 0;
        *(signed char *)(fog + 0x51) = 0;
        *(signed char *)(fog + 0x52) = 0;
        *(int *)(fog + 0x60) = 0;
        *(int *)(fog + 0x54) = 0;
        m = *(float *)(fog + 0x30);
        if (m < *(float *)(fog + 0x34))
            m = *(float *)(fog + 0x34);
        if (m < *(float *)(fog + 0x38))
            m = *(float *)(fog + 0x38);
        L.ext[2] = m;
        L.ext[0] = m;
        L.ext[1] = m;
        __asm__ __volatile__("lqc2 vf7, 0x0(%1)\n"
                             "vmul.xyz vf7, vf7, vf7\n"
                             "vaddy.x vf7, vf7, vf7y\n"
                             "vaddz.x vf7, vf7, vf7z\n"
                             "qmfc2.ni %0, vf7\n"
                             : "=r"(m) : "r"(L.ext));
        *(int *)(fog + 0x44) = arg;
        ret = 1;
        *(float *)(fog + 0x48) = m;
    }
    return ret;
}
#else
extern int NewCreateFogColClass(char *obj, int flags, int arg);
#endif
