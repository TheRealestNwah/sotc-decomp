typedef int s128 __attribute__((mode(TI)));

extern char gcGlobalVar[];
extern int isysGetThisSubThread(void);
extern char *GetLayoutClass(int);
extern char *GetScriptAnimationClass(int);
extern char *GetDamageClass(int);
extern void SCRExecBossPreProcess(int);
extern void SCRExecBossPostProcess(int);
extern void CharaCtrlResetAllScriptCtrlStatus(int);
extern void updateScriptDataSystem(int);
extern int GetWaterSurfacePositionY(float *, float *, void *, float, float);
extern void setDischargeParam(int, void *, float, float);
extern int nico_GetCharacterAttackedGPAttr(int, int);
extern void func_000CC4C0(int);
extern void scrRunM(int);

#ifdef NONMATCHING /* 29 diffs: stack slots of thr/base/b ($sp+0x34/0x38/0x30 in the original), a[1] load order, sqrt operand register */
void func_000CB658(char *o)
{
    float pos[4] __attribute__((aligned(16)));
    float c[4] __attribute__((aligned(16)));
    float a[4] __attribute__((aligned(16)));
    float b;
    int thr;
    char *volatile base;
    int s6, s0, i, n, found, type, entry;
    char *s5, *anim, *tbl;
    float ratio, d;

    thr = isysGetThisSubThread();
    base = o + 4;
    for (;;) {
        s6 = 0;
        s0 = isysGetThisSubThread();
        s5 = (char *)base + 0x5AA0;
        SCRExecBossPreProcess(*(int *)o);
        CharaCtrlResetAllScriptCtrlStatus(s0);
        updateScriptDataSystem(s0);
        do {
            if (s6 == 0)
                s0 = *(int *)(o + 0x5A80);
            else if (s6 == 1)
                s0 = *(int *)(o + 0x5A84);
            else
                s0 = *(int *)(o + 0x5A88);
            if (*(signed char *)(GetScriptAnimationClass(s0) + 0x364) != 1) {
                anim = GetScriptAnimationClass(s0);
                tbl = *(char **)(anim + 0x328);
                n = *(int *)tbl;
                found = 0;
                for (i = 0; i < n; i++) {
                    entry = *(int *)(*(char **)(anim + 0x338) + i * 8);
                    if (entry == 0)
                        continue;
                    type = *(int *)(*(char **)(tbl + 0x18) + i * 12);
                    switch (type) {
                    case 3:
                    case 10:
                    case 13:
                    case 0x2B:
                        *(s128 *)pos = **(s128 **)(GetLayoutClass(entry) + 0x134);
                        found = 1;
                        break;
                    }
                    if (found)
                        break;
                }
                *(s128 *)a = *(s128 *)pos;
                *(s128 *)c = *(s128 *)pos;
                if (GetWaterSurfacePositionY(&b, a, gcGlobalVar + 0x230, a[1] + 6.0f, a[1] - 6.0f)) {
                    c[1] = b;
                    d = __builtin_fabsf(b - a[1]);
                    if (6.0f < d)
                        ratio = 0.0f;
                    else
                        ratio = (6.0f - d) / 6.0f;
                } else {
                    ratio = 0.0f;
                }
                __asm__("sqrt.s %0, %1" : "=f"(ratio) : "f"(ratio));
                setDischargeParam(*(int *)s5, c, 6.0f, ratio);
            } else {
                setDischargeParam(*(int *)s5, pos, 0.0f, 0.0f);
            }
            s6++;
            s5 += 4;
        } while (s6 < 3);
        if (GetDamageClass(thr)) {
            int g = nico_GetCharacterAttackedGPAttr(thr, 0x3F0);
            if (g == 0x10 || g == 0x30 || g == 0x40)
                func_000CC4C0(thr);
        }
        isysGetThisSubThread();
        SCRExecBossPostProcess(*(int *)o);
        scrRunM(1);
    }
}
#endif
