typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;
typedef struct { int f0; int id; } FinderEntry;
typedef struct { Vec4 position; Vec4 auxiliary; FinderEntry geometry; } KeepResult;
typedef struct { Vec4 geometry[4]; Vec4 position; } CollisionPoint;

extern int func_000A2B30(void *, void *, void *, void *, void *, float, void *);
extern int func_000A0DE8(void *, void *, void *, void *, void *, float);
extern int func_000A1580(void *, void *, void *, void *, void *, float);

/* Wrapping the first finder call in an inline keeps gcc from caching the
 * &aux / &pt.position stack addresses across both calls. */
static inline int clip_finder_entry(void *aux, void *e, void *start, void *pos, void *entry, float slope)
{
    return func_000A0DE8(aux, e, start, pos, entry, slope);
}

static inline void copy_finder_header(FinderEntry *destination, FinderEntry *source)
{
    destination->f0 = source->f0;
    destination->id = source->id;
}

int ClipCollisionFinderWithKeepSlopeLimit(KeepResult *out, Vec4 *start, Vec4 *end, int *finder, int *keep, float f12)
{
    Vec4 e;
    Vec4 aux;
    CollisionPoint pt;
    int ret = 0;
    FinderEntry *cur;
    int n;
    FinderEntry *cur2;
    int n2;
    int r;
    int r2;
    int ok;

    out->position.q = end->q;
    if (keep != 0) {
        n = keep[0x20 / 4];
        if (n != 0) {
            e.q = start->q;
            n--;
            cur = (FinderEntry *)keep[0x24 / 4];
            while (n != -1) {
                r = func_000A2B30(&pt, &aux, &e, out, cur, f12, keep);
                if (r != 0) {
                    if (r - 5 < 2U)
                        e.q = pt.position.q;
                    ret = r;
                    out->position.q = pt.position.q;
                    out->auxiliary.q = aux.q;
                    copy_finder_header(&out->geometry, cur);
                }
                n--;
                cur = (FinderEntry *)((char *)cur + 0x14);
            }
        }
    }
    n2 = finder[0];
    if (finder[1] < n2)
        n2 = finder[1];
    if (n2 != 0) {
        n2--;
        cur2 = (FinderEntry *)finder[3];
        while (n2 != -1) {
            if (cur2->f0 != 0) {
                pt.position.q = out->position.q;
                r2 = clip_finder_entry(&aux, &e, start, &pt.position, cur2, f12);
                ok = 0;
                if (r2 == 1) {
                    ok = 1;
                    pt.position.q = pt.geometry[3].q;
                }
                if (r2 == 0) {
                    if (func_000A1580(&aux, &e, start, &pt.position, cur2, f12) != 0)
                        ok = 1;
                }
                if (ok != 0) {
                    ret = ok;
                    out->position.q = pt.geometry[3].q;
                    out->auxiliary.q = e.q;
                    copy_finder_header(&out->geometry, cur2);
                }
            }
            n2--;
            cur2++;
        }
    }
    return ret;
}
