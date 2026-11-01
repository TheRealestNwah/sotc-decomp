typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;

extern int D_00179AC8;
extern float D_00179ACC;
extern char *GetCharacterClass(void *);
extern char *GetLayoutClass(void *);
extern long iosGetTCountExtension(void);
extern float iosGetSecondFromTCount(unsigned long);
extern void func_000064B0(Vec4 *, Vec4 *, void *, int, int);

void DebugGetCameraWithPursue2(Vec4 *pos, Vec4 *tgt, void *obj, int a3, int t0)
{
    if (GetCharacterClass(obj) != 0) {
        long t = iosGetTCountExtension();

        func_000064B0(pos, tgt, obj, a3, t0);
        if (D_00179AC8++ > 10) {
            D_00179AC8 = 0;
            D_00179ACC = 0.0f;
        }
        D_00179ACC += iosGetSecondFromTCount(iosGetTCountExtension() - t) * 60.0f * 100.0f;
    } else {
        s128 v = **(s128 **)(GetLayoutClass(obj) + 0x134);

        tgt->q = v;
        pos->q = v;
        pos->f[2] += 5.0f;
    }
}
