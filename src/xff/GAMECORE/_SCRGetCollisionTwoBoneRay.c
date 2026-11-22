#ifdef NONMATCHING
/* Parked: 3 diffs, same size. Probes four rays between the current and last positions of two nodes (lastB-curB, lastA-curA, lastB-curA, lastA-curB) with ClipCollisionDirectCallBack, ClipCollisionFinderCallBack or ClipCollisionFinder, and copies the hit geometry into *out. The dead chr parameter doubles as the hit flag, which keeps the final sltu. Remaining: in the fourth ray the Original stores the end w (0x1BC) before the call and the start w (0x1AC) in its delay slot; ours swaps the two swc1 around the sw of f2. A 30-minute permuter run found nothing better. */
typedef int s128 __attribute__((mode(TI)));

extern char *GetCharacterClass(void *);
extern int GetCharacterClassMotionInterpNodePosition(void *, void *, int);
extern int GetCharacterClassMotionInterpNodeLastPosition(void *, void *, int);
extern int ClipCollisionDirectCallBack(void *, void *, void *, void *, int, int, int, void *, void *);
extern int ClipCollisionFinderCallBack(void *, void *, void *, void *, void *, void *);
extern int ClipCollisionFinder(void *, void *, void *, void *);
extern void CopyGeometryPointer(void *, void *);

typedef struct { s128 s; s128 e; char g[0x50]; } Ray;

static inline int ray(void *out, Ray *R, s128 *a, s128 *b, void *cb, void *f1, void *f2)
{
    int r;
    R->s = *a;
    R->e = *b;
    ((float *)&R->e)[3] = 1.0f;
    ((float *)&R->s)[3] = 1.0f;
    r = ClipCollisionDirectCallBack(R->g, &R->s, &R->e, cb, 0, 0, 0, f1, f2);
    if (r) {
        if (out)
            CopyGeometryPointer(out, R->g);
    }
    return r;
}

int _SCRGetCollisionTwoBoneRay(void *out, int nodeB, int nodeA, void *cb, int chr, void *f1, void *f2)
{
    struct {
        s128 curB, curA, lastB, lastA;
        union {
            Ray R[4];
            char res[0x50];
            } u;
    } L;
    char *cc = GetCharacterClass((void *)chr);

    if (!GetCharacterClassMotionInterpNodePosition(&L.curA, cc, nodeA))
        return 0;
    chr = 0;
    GetCharacterClassMotionInterpNodePosition(&L.curB, cc, nodeB);
    GetCharacterClassMotionInterpNodeLastPosition(&L.lastB, cc, nodeB);
    GetCharacterClassMotionInterpNodeLastPosition(&L.lastA, cc, nodeA);
    if (cb) {
        if (ray(out, &L.u.R[0], &L.lastB, &L.curB, cb, f1, f2)
            || ray(out, &L.u.R[1], &L.lastA, &L.curA, cb, f1, f2)
            || ray(out, &L.u.R[2], &L.lastB, &L.curA, cb, f1, f2)
            || ray(out, &L.u.R[3], &L.lastA, &L.curB, cb, f1, f2))
            chr = 1;
    } else {
        cc += 0xE20;
        if (f1) {
            if (ClipCollisionFinderCallBack(L.u.res, &L.lastB, &L.curB, cc, f1, f2)
                || ClipCollisionFinderCallBack(L.u.res, &L.lastA, &L.curA, cc, f1, f2)
                || ClipCollisionFinderCallBack(L.u.res, &L.lastB, &L.curA, cc, f1, f2)
                || ClipCollisionFinderCallBack(L.u.res, &L.lastA, &L.curB, cc, f1, f2))
                chr = 1;
        } else {
            if (ClipCollisionFinder(L.u.res, &L.lastB, &L.curB, cc)
                || ClipCollisionFinder(L.u.res, &L.lastA, &L.curA, cc)
                || ClipCollisionFinder(L.u.res, &L.lastB, &L.curA, cc)
                || ClipCollisionFinder(L.u.res, &L.lastA, &L.curB, cc))
                chr = 1;
        }
        if (chr)
            CopyGeometryPointer(out, L.u.res);
    }
    return chr != 0;
}
#endif
