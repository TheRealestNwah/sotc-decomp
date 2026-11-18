/* 1 diff: at 0x118 the Original has bnel v1,zero (delay slot v0 = k, annulled) where gcc 2.96 emits bnez. Same unsolved beql/beqz reorg puzzle as the track samplers (func_00033DE0 and siblings). Everything else matches; the keep path must be an inline helper or gcc hoists the stack addresses into saved registers. */
typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;
typedef struct { int f0; int id; } FinderEntry;
typedef struct { Vec4 position; Vec4 auxiliary; FinderEntry geometry; } KeepResult;
typedef struct { Vec4 geometry[4]; Vec4 position; } CollisionPoint;
extern int func_000A0DE8(CollisionPoint *, Vec4 *, float *, Vec4 *, float, FinderEntry *);
extern int func_000A1580(CollisionPoint *, Vec4 *, float *, Vec4 *, float, FinderEntry *);
extern int func_000A3F00(CollisionPoint *, Vec4 *, float *, Vec4 *, FinderEntry *);

static inline void copy_finder_header(FinderEntry *destination, FinderEntry *source)
{
    destination->f0 = source->f0;
    destination->id = source->id;
}

static inline int keep_hit(CollisionPoint *point, Vec4 *auxiliary, float *start, Vec4 *cur, float keep, FinderEntry *entry)
{
    Vec4 pos;
    int r;
    int k = 0;
    pos.q = cur->q;
    r = func_000A0DE8(point, auxiliary, start, &pos, keep, entry);
    if (r == 1) {
        k = 1;
        pos.q = point->position.q;
    }
    if (r == 0) {
        if (func_000A1580(point, auxiliary, start, &pos, keep, entry))
            k = 1;
    }
    return k;
}

#ifdef NONMATCHING
int ClipCollisionFinderWithVariableKeepCB(KeepResult *out, float *start, Vec4 *finish, int *finder,
                                          float (*getKeep)(int, void *), int (*filter)(FinderEntry *, void *),
                                          void (*onHit)(FinderEntry *, int, void *), void *user)
{
    int result = 0;
    int count;
    out->position.q = finish->q;
    count = finder[0];
    if (finder[1] < count)
        count = finder[1];
    if (count != 0) {
        Vec4 auxiliary;
        CollisionPoint point;
        FinderEntry *entry = (FinderEntry *)finder[3];
        int last = 0;
        float keep = 0.0f;
        while (--count != -1) {
            int id = entry->f0;
            if (id != 0 && (filter == 0 || filter(entry, user))) {
                int r;
                if (last != id) {
                    keep = getKeep(id, user);
                    last = id;
                }
                if (0.0f < keep)
                    r = keep_hit(&point, &auxiliary, start, &out->position, keep, entry);
                else
                    r = func_000A3F00(&point, &auxiliary, start, &out->position, entry);
                if (r != 0) {
                    result = r;
                    out->position.q = point.position.q;
                    out->auxiliary.q = auxiliary.q;
                    copy_finder_header(&out->geometry, entry);
                    if (onHit != 0)
                        onHit(entry, result, user);
                }
            }
            entry++;
        }
    }
    return result;
}
#endif
