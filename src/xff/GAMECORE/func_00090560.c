typedef int s128 __attribute__((mode(TI)));

extern char gcGlobalVar[];

extern char *GetCharacterClass(void *);
extern int GetCharacterClassMotionInterpNodePosition(void *, void *, int);
extern int _SCRGetCollisionTwoBoneRay3D(void *, int, int, void *, void *, void *, void *);
extern int func_00090408(void *, void *, int);
extern int func_00091AB8();
extern void CharaCtrlSetScriptCtrlStatus(void *, int);
extern void CopyGeometryPointer(void *, void *);

#ifdef NONMATCHING /* 88 diffs: the original copies flags twice ($s0, then $s2 for the result) and uses eight saved registers with a 0xA0 frame; ours folds the copy and uses seven with 0x90 */
static int func_00090560(int *cfg, void *geoA, void *geoB, int flags, void *obj)
{
    char pos[0x10] __attribute__((aligned(16)));
    char hit[0x40] __attribute__((aligned(16)));
    char *cc;
    char *h;
    int ret;

    h = hit;
    ret = flags;

    cc = GetCharacterClass(obj);
    if (GetCharacterClassMotionInterpNodePosition(pos, cc, cfg[1]) != 0 &&
        _SCRGetCollisionTwoBoneRay3D(h, cfg[0], cfg[1], gcGlobalVar + 0x230, obj, func_00091AB8, 0) != 0) {
        flags = func_00090408(h, cc, cfg[4]);
        if (flags & 4) {
            if (cfg[3] >= 0)
                CharaCtrlSetScriptCtrlStatus(obj, cfg[3]);
            if (geoA != 0) {
                if (cfg[5] != 0) {
                    CopyGeometryPointer(geoA, h);
                    ret |= 1;
                }
            }
        }
        if (flags & 2) {
            if (cfg[3] >= 0)
                CharaCtrlSetScriptCtrlStatus(obj, cfg[3]);
            if (geoB != 0) {
                if (cfg[5] != 0) {
                    CopyGeometryPointer(geoB, h);
                    ret |= 2;
                }
            }
        }
        if (flags & 1) {
            if (cfg[2] >= 0)
                CharaCtrlSetScriptCtrlStatus(obj, cfg[2]);
        }
    }
    return ret;
}
#endif
