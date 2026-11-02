typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;
typedef struct { int p0; int p4; } Entry;
typedef struct { int p0; int p4; int p8; Entry *entries; } Finder;
typedef struct { int p0; int p4; char p8[0x38]; s128 p40; } Result;
extern int ClipCollisionDB(Result *, s128 *, void *, Entry *);
extern void func_0009D8F8(s128 *, Entry *, Vec4 *, int);

int ClipCollisionFinderFarPlane4D(Result *r, s128 *plane, void *a2, Finder *f)
{
    int n = f->p4 < f->p0 ? f->p4 : f->p0;
    Entry *e;
    Entry *last;
    int hit;
    int i;
    Vec4 tmp;
    s128 local;

    hit = 0;
    e = f->entries;
    if (n != 0) {
    tmp.q = *plane;
    last = 0;
    for (i = 0; i < n; i++, e++) {
        if (e->p0 != 0) {
            func_0009D8F8(&local, e, &tmp, 1);
            if (ClipCollisionDB(r, &local, a2, e)) {
                hit++;
                last = e;
                tmp.q = r->p40;
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
