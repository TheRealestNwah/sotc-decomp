typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;
typedef struct { int f0; int id; } FinderEntry;
typedef struct { Vec4 position; Vec4 auxiliary; FinderEntry geometry; } KeepResult;
typedef struct { Vec4 geometry[4]; Vec4 position; } CollisionPoint;
extern int func_000AE618(CollisionPoint *, Vec4 *, float *, Vec4 *, FinderEntry *, float);

static inline void copy_finder_header(FinderEntry *destination, FinderEntry *source)
{
    destination->f0 = source->f0;
    destination->id = source->id;
}

int ClipCollisionFinderWithKeep4D(KeepResult *out, float *start, Vec4 *finish, int *finder, float keep)
{
    int count = finder[0];
    if (finder[1] < count)
        count = finder[1];
    if (count != 0) {
        Vec4 auxiliary;
        CollisionPoint point;
        FinderEntry *entry = (FinderEntry *)finder[3];
        int found = 0;
        out->position.q = finish->q;
        while (--count != -1) {
            if (entry->f0 != 0 && func_000AE618(&point, &auxiliary, start, &out->position, entry, keep)) {
                found = 1;
                out->position.q = point.position.q;
                out->auxiliary.q = auxiliary.q;
                copy_finder_header(&out->geometry, entry);
            }
            entry++;
        }
        if (found != 0)
            return 1;
    }
    return 0;
}
