typedef int s128 __attribute__((mode(TI)));

extern void *GetCharacterClass(void *);
extern char *GetLayoutClass(void *);
extern void CharaCtrlResetScriptCtrlStatus(void *, int);
extern void CharaCtrlSetScriptCtrlStatus(void *, int);
extern int func_0007E608(int, void *, int, int);
extern void player_HellDangerDetect(void *, int);
extern void *ScriptCtrlDef_SCRPlayerFallDanger;

static inline float distanceSquare(float *a, float *b)
{
    float d;

    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyzw vf7, vf5, vf6\n"
                         "vmul.xyz vf7, vf7, vf7\n"
                         "vaddy.x vf7, vf7, vf7y\n"
                         "vaddz.x vf7, vf7, vf7z\n"
                         "qmfc2.ni $2, vf7\n"
                         "mtc1 $2, %0\n"
                         : "=f"(d) : "r"(a), "r"(b) : "$2");
    return d;
}

void player_AvoidDangerCliff(void *chara, int work)
{
    char *cls;
    s128 *pos;
    s128 *last;

    player_HellDangerDetect(chara, work);
    cls = GetCharacterClass(chara);
    CharaCtrlResetScriptCtrlStatus(chara, *(int *)((char *)ScriptCtrlDef_SCRPlayerFallDanger + 4));
    if (func_0007E608(work + 0x10, cls + 0xE20, *(int *)(cls + 0x138), *(int *)(cls + 0x134)) != 0) {
        CharaCtrlSetScriptCtrlStatus(chara, *(int *)((char *)ScriptCtrlDef_SCRPlayerFallDanger + 4));
    }
    pos = *(s128 **)(GetLayoutClass(chara) + 0x134);
    last = (s128 *)(work + 0x50);
    if (0.009999997913837433f < distanceSquare((float *)last, (float *)pos)) {
        *last = *pos;
    }
}
