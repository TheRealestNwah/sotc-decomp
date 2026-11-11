typedef int s128 __attribute__((mode(TI)));

extern char gcGlobalVar[];

extern char *GetCharacterClass(void *);
extern int GetCharacterClassMotionInterpNodePosition(void *, void *, int);
extern int _SCRGetCollisionTwoBoneRay3D(void *, int, int, void *, void *, void *, void *);
extern int func_00090408(void *, void *, int);
extern int func_00091AB8();
extern void CharaCtrlSetScriptCtrlStatus(void *, int);
extern void CopyGeometryPointer(void *, void *);

#ifdef NONMATCHING /* 90 diffs: the original keeps the hit buffer pointer in $s5 (eight saved registers, frame 0xA0) and copies the flags argument twice ($s0, $s2); ours uses seven and a 0x90 frame */
static int func_00090560(int *cfg, void *geoA, void *geoB, int flags, void *obj)
{
    char pos[0x10] __attribute__((aligned(16)));
    char hit[0x40] __attribute__((aligned(16)));
    char *cc;
    int st;

    cc = GetCharacterClass(obj);
    if (GetCharacterClassMotionInterpNodePosition(pos, cc, cfg[1]) != 0 &&
        _SCRGetCollisionTwoBoneRay3D(hit, cfg[0], cfg[1], gcGlobalVar + 0x230, obj, func_00091AB8, 0) != 0) {
        st = func_00090408(hit, cc, cfg[4]);
        if (st & 4) {
            if (cfg[3] >= 0)
                CharaCtrlSetScriptCtrlStatus(obj, cfg[3]);
            if (geoA != 0) {
                if (cfg[5] != 0) {
                    CopyGeometryPointer(geoA, hit);
                    flags |= 1;
                }
            }
        }
        if (st & 2) {
            if (cfg[3] >= 0)
                CharaCtrlSetScriptCtrlStatus(obj, cfg[3]);
            if (geoB != 0) {
                if (cfg[5] != 0) {
                    CopyGeometryPointer(geoB, hit);
                    flags |= 2;
                }
            }
        }
        if (st & 1) {
            if (cfg[2] >= 0)
                CharaCtrlSetScriptCtrlStatus(obj, cfg[2]);
        }
    }
    return flags;
}
#endif
