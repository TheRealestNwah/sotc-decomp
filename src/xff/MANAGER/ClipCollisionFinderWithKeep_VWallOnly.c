typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;
typedef struct { int f0; int id; } FinderEntry;
typedef struct { Vec4 position; Vec4 auxiliary; FinderEntry geometry; } KeepResult;
typedef struct { Vec4 geometry[4]; Vec4 position; } CollisionPoint;
typedef struct { FinderEntry geometry; char unknown8[12]; } WallEntry;
typedef struct { char unknown0[0x20]; int count; WallEntry *entries; } WallFinderView;
extern int func_000A2B30(CollisionPoint *, Vec4 *, Vec4 *, Vec4 *, WallEntry *, float, WallFinderView *);
static inline void copy_finder_header(FinderEntry *destination, FinderEntry *source)
{
    destination->f0 = source->f0;
    destination->id = source->id;
}

int ClipCollisionFinderWithKeep_VWallOnly(KeepResult *out, Vec4 *start, Vec4 *finish, WallFinderView *finder, float keep)
{
    int status = 0;
    int count;
    out->position.q = finish->q;
    count = finder->count;
    if (count != 0) {
        Vec4 begin;
        Vec4 auxiliary;
        CollisionPoint point;
        WallEntry *entry = finder->entries;
        begin.q = start->q;
        while (--count != -1) {
            int result = func_000A2B30(&point, &auxiliary, &begin, &out->position, entry, keep, finder);
            if (result != 0) {
                if (result == 5 || result == 6)
                    begin.q = point.position.q;
                status = result;
                out->position.q = point.position.q;
                out->auxiliary.q = auxiliary.q;
                copy_finder_header(&out->geometry, &entry->geometry);
            }
            entry++;
        }
    }
    return status;
}
