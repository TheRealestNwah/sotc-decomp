extern char gcGlobalVar[];
extern int SCRGetFirstObj(void *);
extern int nico_playerGetSightOn(int);
extern int nico_playerIsActingSightOn(int);
extern char *GetLayoutClass(int);
extern void get_snipe_position_nico_sight_on(void *, int);
extern void get_radiate_direction_nico_sight_on(void *, int);
extern int get_predict_hit_position_nico_sight_on(void *, int);

#ifdef NONMATCHING /* 45 diffs (pinned $f0/$f1 for the two dot results fixes the float numbering; remaining: v40 goes through an a2 temp instead of straight into s1, and the early-exit shape). Earlier note (50 diffs): VU blocks, call order and pinned pointer registers match; early-exit shape (original returns 0 from branch delay slots) and the float register numbering ($f0/$f1 vs ours $f3) differ */
int AI_CheckSightOn(int obj, float rad)
{
    char sp[0x60] __attribute__((aligned(16)));
    int o = SCRGetFirstObj(gcGlobalVar + 0x2B0);
    int sight = nico_playerGetSightOn(o);
    char *lc;
    register char *dir __asm__("$18");
    register char *v40 __asm__("$17");
    register char *p0 __asm__("$4");
    register char *p10 __asm__("$5");
    register char *p50 __asm__("$3");
    float dd;
    float a;
    float b;
    float c;
    float len;
    register float dot __asm__("$f0");
    register float dot2 __asm__("$f1");

    if (o == 0)
        return 0;
    if (nico_playerIsActingSightOn(o) == 0)
        return 0;
    lc = GetLayoutClass(obj);
    get_snipe_position_nico_sight_on(sp, sight);
    dir = sp + 0x20;
    get_radiate_direction_nico_sight_on(dir, sight);
    p10 = sp + 0x10;
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vadd.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(p10), "r"(sp), "r"(dir) : "memory");
    p0 = sp;
    v40 = p0 + 0x40;
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(v40), "r"(*(char **)(lc + 0x134)), "r"(p0) : "memory");
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(p50), "r"(p10), "r"(p0) : "memory");
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vaddw.x vf7, vf0, vf0w\n"
                         "vmul.xyz vf6, vf5, vf6\n"
                         "vaddax.x ACC, vf0, vf6x\n"
                         "vmadday.x ACC, vf7, vf6y\n"
                         "vmaddz.x vf6, vf7, vf6z\n"
                         "qmfc2.ni $2, vf6\n"
                         "mtc1 $2, %0\n"
                         : "=f"(dot) : "r"(v40), "r"(p50) : "$2");
    __asm__ __volatile__("lqc2 vf7, 0x0(%1)\n"
                         "vmul.xyz vf7, vf7, vf7\n"
                         "vaddy.x vf7, vf7, vf7y\n"
                         "vaddz.x vf7, vf7, vf7z\n"
                         "qmfc2.ni $2, vf7\n"
                         "mtc1 $2, %0\n"
                         : "=f"(a) : "r"(v40) : "$2");
    __asm__ __volatile__("lqc2 vf7, 0x0(%1)\n"
                         "vmul.xyz vf7, vf7, vf7\n"
                         "vaddy.x vf7, vf7, vf7y\n"
                         "vaddz.x vf7, vf7, vf7z\n"
                         "qmfc2.ni $2, vf7\n"
                         "mtc1 $2, %0\n"
                         : "=f"(b) : "r"(p50) : "$2");
    dd = a - dot * dot / b;
    __asm__ __volatile__("lqc2 vf5, 0x0(%2)\n"
                         "lqc2 vf6, 0x0(%3)\n"
                         "vsub.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf7, 0x0(%1)\n"
                         "vmul.xyz vf7, vf7, vf7\n"
                         "vmulax.w ACC, vf0, vf7x\n"
                         "vmadday.w ACC, vf0, vf7y\n"
                         "vmaddz.w vf7, vf0, vf7z\n"
                         ".word 0x4BA703BD\n"
                         "vwaitq\n"
                         "cfc2.ni $2, $vi22\n"
                         "mtc1 $2, %0\n"
                         "lqc2 vf5, 0x0(%1)\n"
                         "vmul.xyz vf7, vf5, vf5\n"
                         "vmulax.w ACC, vf0, vf7x\n"
                         "vmadday.w ACC, vf0, vf7y\n"
                         "vmaddz.w vf7, vf0, vf7z\n"
                         "vrsqrt Q, vf0w, vf7w\n"
                         "vwaitq\n"
                         "vmulq.xyz vf5, vf5, Q\n"
                         "sqc2 vf5, 0x0(%1)\n"
                         : "=f"(len) : "r"(sp + 0x30), "r"(*(char **)(lc + 0x134)), "r"(sp) : "$2", "memory");
    if (!(dd <= rad * rad))
        return 0;
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vaddw.x vf7, vf0, vf0w\n"
                         "vmul.xyz vf6, vf5, vf6\n"
                         "vaddax.x ACC, vf0, vf6x\n"
                         "vmadday.x ACC, vf7, vf6y\n"
                         "vmaddz.x vf6, vf7, vf6z\n"
                         "qmfc2.ni $2, vf6\n"
                         "mtc1 $2, %0\n"
                         : "=f"(dot2) : "r"(dir), "r"(sp + 0x30) : "$2");
    if (!(0.0f < dot2))
        return 0;
    if (get_predict_hit_position_nico_sight_on(v40, sight) == 0)
        return 1;
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyzw vf7, vf5, vf6\n"
                         "vmul.xyz vf7, vf7, vf7\n"
                         "vmulax.w ACC, vf0, vf7x\n"
                         "vmadday.w ACC, vf0, vf7y\n"
                         "vmaddz.w vf7, vf0, vf7z\n"
                         ".word 0x4BA703BD\n"
                         "vwaitq\n"
                         "cfc2.ni $2, $vi22\n"
                         "mtc1 $2, %0\n"
                         : "=f"(c) : "r"(v40), "r"(sp) : "$2");
    if (c - len < -rad)
        return 0;
    return 1;
}
#endif
