/* 2 diffs: the Original copies the start vector with lq/sq through $v1 (lq $v1, 0($s4); sq $v1, 0x70($sp)) where ours uses $v0; everything else matches. The permuter found nothing better in ~2700 iterations. */
typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;
typedef struct { int f0; int id; } FinderEntry;
typedef struct { Vec4 position; Vec4 auxiliary; FinderEntry geometry; } KeepResult;
typedef struct { Vec4 geometry[4]; Vec4 position; } CollisionPoint;

extern void func_0009D8F8(void *, void *, void *, int);
extern int func_000A2B30(void *, void *, void *, void *, void *, float, void *);
extern int func_000A0DE8(void *, void *, void *, void *, void *, float);
extern int func_000A1580(void *, void *, void *, void *, void *, float);

#ifdef NONMATCHING
static inline int clip_finder_entry(void *aux, void *e, void *start, void *pos, void *entry, float slope)
{
    return func_000A0DE8(aux, e, start, pos, entry, slope);
}

static inline int clip_keep_entry(void *pt, void *aux, void *e, void *out, void *entry, float slope, void *keep)
{
    return func_000A2B30(pt, aux, e, out, entry, slope, keep);
}

static inline void to_local(void *d, void *e, void *s)
{
    func_0009D8F8(d, e, s, 1);
}

static inline void copy_finder_header(FinderEntry *destination, FinderEntry *source)
{
    destination->f0 = source->f0;
    destination->id = source->id;
}

int ClipCollisionFinderWithKeep4DSlopeLimitCB(KeepResult *out, Vec4 *start, Vec4 *end, int *finder, int *keep,
                                              int (*filter)(void *, void *), void (*callback)(void *, int, void *),
                                              void *user, float f12)
{
    Vec4 e;
    Vec4 aux;
    CollisionPoint pt;
    Vec4 tmp;
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
                if (filter(cur, user) != 0) {
                to_local(&tmp, cur, &e);
                r = clip_keep_entry(&pt, &aux, &tmp, out, cur, f12, keep);
                if (r != 0) {
                    if (r - 5 < 2U)
                        e.q = pt.position.q;
                    ret = r;
                    out->position.q = pt.position.q;
                    out->auxiliary.q = aux.q;
                    copy_finder_header(&out->geometry, cur);
                    if (callback != 0)
                        callback(cur, ret, user);
                }
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
            if (cur2->f0 != 0 && filter(cur2, user) != 0) {
                to_local(&pt.position, cur2, start);
                tmp.q = out->position.q;
                r2 = clip_finder_entry(&aux, &e, &pt.position, &tmp, cur2, f12);
                ok = 0;
                if (r2 == 1) {
                    ok = 1;
                    tmp.q = pt.geometry[3].q;
                }
                if (r2 == 0) {
                    if (func_000A1580(&aux, &e, &pt.position, &tmp, cur2, f12) != 0)
                        ok = 1;
                }
                if (ok != 0) {
                    ret = ok;
                    out->position.q = pt.geometry[3].q;
                    out->auxiliary.q = e.q;
                    copy_finder_header(&out->geometry, cur2);
                    if (callback != 0)
                        callback(cur2, ret, user);
                }
            }
            n2--;
            cur2++;
        }
    }
    return ret;
}
#endif
