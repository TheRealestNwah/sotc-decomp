#ifdef NONMATCHING
/* 66 diffs, 3 words short (93 vs 96). Draft from the asm: samples two node positions of a character (nodeA into p20, nodeB into p10), then either probes with ClipCollisionDirectCallBack (cb given) or with ClipCollisionFinderCallBack / ClipCollisionFinder, and copies the hit geometry into *out. The Original reuses the nodeB register ($s5) as the hit flag (zeroed after the second node call) and returns it with one shared sltu; ours does not reach the same register assignment or branch shape. Not yet permuted. */
typedef int s128 __attribute__((mode(TI)));

extern char *GetCharacterClass(void *);
extern int GetCharacterClassMotionInterpNodePosition(void *, void *, int);
extern int ClipCollisionDirectCallBack(void *, void *, void *, void *, int, int, int, void *, void *);
extern void *ClipCollisionFinderCallBack(void *, void *, void *, void *, void *, void *);
extern int ClipCollisionFinder(void *, void *, void *);
extern void CopyGeometryPointer(void *, void *);

int _SCRGetCollisionTwoBoneRay3D(void *out, int hit, int nodeA, void *cb, void *chr, void *f1, void *f2)
{
    struct {
        s128 p10;
        s128 p20;
        s128 p30;
        s128 p40;
        char p50[0x50];
    } L;
    char *cc = GetCharacterClass(chr);
    int r;

    if (!GetCharacterClassMotionInterpNodePosition(&L.p20, cc, nodeA))
        return 0;
    GetCharacterClassMotionInterpNodePosition(&L.p10, cc, hit);
    hit = 0;
    if (cb) {
        L.p30 = L.p10;
        L.p40 = L.p20;
        ((float *)&L.p30)[3] = 1.0f;
        ((float *)&L.p40)[3] = 1.0f;
        r = ClipCollisionDirectCallBack(L.p50, &L.p30, &L.p40, cb, 0, 0, 0, f1, f2);
        if (r) {
            if (out)
                CopyGeometryPointer(out, L.p50);
            if (r)
                hit = 1;
        }
    } else {
        if (f1) {
            if (ClipCollisionFinderCallBack(&L.p30, &L.p10, &L.p20, cc + 0xE20, f1, f2))
                hit = 1;
        } else {
            hit = ClipCollisionFinder(&L.p30, &L.p10, &L.p20) != 0;
        }
        if (hit)
            CopyGeometryPointer(out, &L.p30);
    }
    return hit != 0;
}
#endif
