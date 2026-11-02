typedef int s128 __attribute__((mode(TI)));
typedef struct {
    float x, y, z, w;
} __attribute__((aligned(16))) Vec4;

extern Vec4 YUnitVector;
extern char *GetLayoutClass(void *);
extern char *GetCharacterClass(void *);
extern void CharaCtrlSetScriptCtrlStatus(void *, int);

void _SCRRequestDamageReaction(void *obj, int *status, float x, float y, float z, float deg)
{
    char *l = GetLayoutClass(obj);
    char *c;
    char *v;
    union {
        Vec4 v;
        s128 q;
    } dir;

    dir.v.x = x;
    dir.v.y = y;
    dir.v.z = z;
    dir.v.w = 0.0f;
    *(s128 *)(l + 0x30) = dir.q;
    c = GetCharacterClass(obj);
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vopmula.xyz ACC, vf5, vf6\n"
                         "vopmsub.xyz vf7, vf6, vf5\n"
                         "vsub.w vf7, vf7, vf7\n"
                         "sqc2 vf7, 0x0(%0)\n"
                         : : "r"(*(char **)(l + 0x19C) + 0x40), "r"(l + 0x30), "r"(&YUnitVector) : "memory");
    v = *(char **)(l + 0x19C) + 0x40;
    __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                         "vmul.xyz vf7, vf5, vf5\n"
                         "vmulax.w ACC, vf0, vf7x\n"
                         "vmadday.w ACC, vf0, vf7y\n"
                         "vmaddz.w vf7, vf0, vf7z\n"
                         "vrsqrt Q, vf0w, vf7w\n"
                         "vwaitq\n"
                         "vmulq.xyz vf5, vf5, Q\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(v) : "memory");
    *(float *)(*(char **)(l + 0x19C) + 0x50) = deg * 0.017453293f;
    __asm__ __volatile__("sqc2 vf0, 0x0(%0)\n" : : "r"(c + 0x4B0) : "memory");
    c[0x529] = 1;
    if (status != 0)
        CharaCtrlSetScriptCtrlStatus(obj, status[1]);
}
