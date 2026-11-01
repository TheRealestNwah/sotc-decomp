typedef int s128 __attribute__((mode(TI)));
typedef struct { int p0; int p4; } Entry;
typedef struct { int p0; int p4; int p8; Entry *entries; } Finder;
typedef struct { int p0; int p4; char p8[0x38]; s128 p40; } Result;
extern int ClipCollisionDB(Result *, s128 *, void *, Entry *);

int ClipCollisionFinderFarPlane(Result *r, s128 *plane, void *a2, Finder *f)
{
    int n = f->p4 < f->p0 ? f->p4 : f->p0;
    Entry *e;
    Entry *last;
    int hit;
    int i;
    s128 tmp;

    hit = 0;
    e = f->entries;
    if (n != 0) {
    tmp = *plane;
    last = 0;
    for (i = 0; i < n; i++, e++) {
        if (e->p0 != 0) {
            if (ClipCollisionDB(r, &tmp, a2, e)) {
                hit++;
                last = e;
                tmp = r->p40;
            }
        }
    }
    if (last != 0) {
        r->p0 = last->p0;
        r->p4 = last->p4;
    }
    return hit != 0;
    }
    return 0;
}
