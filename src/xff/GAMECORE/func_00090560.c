typedef int s128 __attribute__((mode(TI)));

extern char gcGlobalVar[];

extern char *GetCharacterClass(void *);
extern int GetCharacterClassMotionInterpNodePosition(void *, void *, int);
extern int _SCRGetCollisionTwoBoneRay3D(void *, int, int, void *, void *, void *, void *);
extern int func_00090408(void *, void *, int);
extern int func_00091AB8();
extern void CharaCtrlSetScriptCtrlStatus(void *, int);
extern void CopyGeometryPointer(void *, void *);

#ifdef NONMATCHING /* 17 diffs: cfg, h and ret are pinned to $s1, $s5 and $s2 like the original. Remaining: register allocation in the prologue. The original keeps flags in $s0, copies it to $s2 for the result, puts the character class in $s4 and computes hit into $s5 after the first call; ours puts flags straight into $s2, the class in $s0, and computes hit into $s4 up front before copying it to $s5. Pinning the class to $s4 or flags to $s0 costs more diffs. */
static int func_00090560(int *cfg0, void *geoA, void *geoB, int flags, void *obj)
{
    register int *cfg __asm__("$17") = cfg0;
    char pos[0x10] __attribute__((aligned(16)));
    char hit[0x40] __attribute__((aligned(16)));
    char *cc;
    register char *h __asm__("$21");
    int fl = flags;
    register int ret __asm__("$18") = fl;

    h = hit;

    cc = GetCharacterClass(obj);
    if (GetCharacterClassMotionInterpNodePosition(pos, cc, cfg[1]) != 0 &&
        _SCRGetCollisionTwoBoneRay3D(h, cfg[0], cfg[1], gcGlobalVar + 0x230, obj, func_00091AB8, 0) != 0) {
        fl = func_00090408(h, cc, cfg[4]);
        if (fl & 4) {
            if (cfg[3] >= 0)
                CharaCtrlSetScriptCtrlStatus(obj, cfg[3]);
            if (geoA != 0) {
                if (cfg[5] != 0) {
                    CopyGeometryPointer(geoA, h);
                    ret |= 1;
                }
            }
        }
        if (fl & 2) {
            if (cfg[3] >= 0)
                CharaCtrlSetScriptCtrlStatus(obj, cfg[3]);
            if (geoB != 0) {
                if (cfg[5] != 0) {
                    CopyGeometryPointer(geoB, h);
                    ret |= 2;
                }
            }
        }
        if (fl & 1) {
            if (cfg[2] >= 0)
                CharaCtrlSetScriptCtrlStatus(obj, cfg[2]);
        }
    }
    return ret;
}
#endif
