typedef struct {
    float x, y, z, w;
} __attribute__((aligned(16))) Vec4;

extern char *GetCharacterClass();
extern char *GetLayoutClass(void *);
extern unsigned long *GetCollisionDBAttributeAdr(void *);
extern void MakeGeometryPointerCollisionInfo(void *, void *, void *, float, float);
extern void SendCharaAttackMsg(void *, int, void *, int, float);
extern float iosGetCosf(float);

#ifdef NONMATCHING
/* Parked: ~80 words differ (callee-saved register assignment of character class/collision/mask/match). */
int SCRConditionSendDamageToCollisionObject(void *obj, int u1, int u2, int u3, long mask, long match, float angle)
{
    char *cc = GetCharacterClass();
    char *coll;
    long attr;
    int ok;
    char *layout;
    Vec4 up;
    Vec4 dir;
    char info[0x40] __attribute__((aligned(16)));
    float c;
    char *pos;
    float len;

    coll = cc + 0xFF8;
    if (*(int *)(cc + 0xFF0) != 0) {
        attr = *GetCollisionDBAttributeAdr(coll);
        ok = 1;
        if (mask != -1) {
            long m = attr & mask;
            if (match != -1)
                ok = (match == m);
            else
                ok = (m != 0);
        }
        if (ok != 0) {
            layout = GetLayoutClass(obj);
            __asm__ __volatile__("lqc2 vf4, 0x0(%1)\n"
                                 "vmul.xyzw vf5, vf4, vf4\n"
                                 "vmr32.xyzw vf6, vf4\n"
                                 "vmul.xyzw vf7, vf6, vf4\n"
                                 "vmr32.xyzw vf6, vf6\n"
                                 "vmul.xyzw vf8, vf6, vf4\n"
                                 "vsubx.z vf6, vf0, vf5x\n"
                                 "vsuby.z vf6, vf6, vf5y\n"
                                 "vaddw.y vf6, vf7, vf7w\n"
                                 "vsuby.x vf6, vf8, vf8y\n"
                                 "vsub.w vf6, vf0, vf0\n"
                                 "vadd.w vf5, vf0, vf0\n"
                                 "vmulw.xyz vf6, vf6, vf5w\n"
                                 "vaddw.z vf6, vf6, vf0w\n"
                                 "sqc2 vf6, 0x0(%0)\n"
                                 : : "r"(&up), "r"(*(void **)(layout + 0x13C)) : "memory");
            pos = cc + 0x1000;
            __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                                 "lqc2 vf6, 0x0(%1)\n"
                                 "vsub.xyzw vf7, vf5, vf6\n"
                                 "sqc2 vf7, 0x0(%2)\n"
                                 : : "r"(pos), "r"(*(void **)(layout + 0x134)), "r"(&dir) : "memory");
            __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                                 "vmul.xyz vf7, vf5, vf5\n"
                                 "vmulax.w ACC, vf0, vf7x\n"
                                 "vmadday.w ACC, vf0, vf7y\n"
                                 "vmaddz.w vf7, vf0, vf7z\n"
                                 "vrsqrt Q, vf0w, vf7w\n"
                                 "vwaitq\n"
                                 "vmulq.xyz vf5, vf5, Q\n"
                                 "sqc2 vf5, 0x0(%0)\n"
                                 : : "r"(&dir) : "memory");
            c = iosGetCosf(angle * 0.017453292f);
            __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                                 "lqc2 vf6, 0x0(%2)\n"
                                 "vaddw.x vf7, vf0, vf0w\n"
                                 "vmul.xyz vf6, vf5, vf6\n"
                                 "vaddax.x ACC, vf0, vf6x\n"
                                 "vmadday.x ACC, vf7, vf6y\n"
                                 "vmaddz.x vf6, vf7, vf6z\n"
                                 "qmfc2.ni $2, vf6\n"
                                 "mtc1 $2, %0\n"
                                 : "=f"(len) : "r"(&up), "r"(&dir) : "$2", "memory");
            if (c < len) {
                MakeGeometryPointerCollisionInfo(info, pos, coll, 0.0f, 0.0f);
                SendCharaAttackMsg(obj, *(int *)coll, info, -1, 0.0f);
                return 1;
            }
        }
    }
    return 0;
}
#else
int SCRConditionSendDamageToCollisionObject(void *obj, int u1, int u2, int u3, long mask, long match, float angle);
#endif
