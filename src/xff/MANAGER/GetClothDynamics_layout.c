/*
 * GetClothDynamics: steps every cloth of a layout object (or hands off to
 * the resource's override callback). The file name differs from the
 * function's because getClothDynamics.c already exists and Windows file
 * names are case-insensitive.
 *
 * Parked: 14 diffs (ee-gcc 2.96 -O2 -G0).
 * Remaining: the 0x180 test loads into $v1 instead of $v0, and the four
 * vertex copy loops fill their entry beq delay slots the other way round
 * (the mode == 2 loops take mov.s $f12 where the original takes the -1
 * constant, the other loops the reverse).
 */
#ifdef NONMATCHING
typedef struct { int a; int b; char pad8[8]; int c; int d; } ClothVert;
typedef struct { int pad0; int count; } ClothHeader;
typedef struct { ClothHeader *header; char pad4[8]; ClothVert *verts; char pad10[0x70]; unsigned char flip; char pad81[0xF]; } Cloth;
typedef struct ClothRes {
    Cloth *cloths;
    short count;
    char pad6[0xA];
    int (*check)(Cloth *, void *);
    int (*override)(void *, float, float, int, void *);
} ClothRes;
extern char *GetLayoutClass(void *);
extern void func_000BBE58(Cloth *, char *, int, float, float);
extern void func_000BC5C8(Cloth *, char *, int);
extern void func_000BC3B0(Cloth *, char *, float, float);

static inline void step(Cloth *cloth, char *lc, int f, float t0, float t1)
{
    ClothVert *v = cloth->verts;
    int n = cloth->header->count;
    if ((cloth->flip = (cloth->flip + 1) & 1) != 0) {
        while (n-- != 0) {
            v->c = v->b;
            v->d = v->a;
            v++;
        }
    } else {
        while (n-- != 0) {
            v->c = v->a;
            v->d = v->b;
            v++;
        }
    }
    func_000BBE58(cloth, lc, f, t0, t1);
    func_000BC5C8(cloth, lc, 0);
    func_000BC3B0(cloth, lc, t0, t1);
}

int GetClothDynamics(void *obj, float t0, float t1, int mode, void *arg)
{
    char *lc = GetLayoutClass(obj);
    ClothRes *r;
    Cloth *c;
    int n;

    if (*(int *)(lc + 0x180) == 0)
        return 0;
    r = *(ClothRes **)(lc + 0x178);
    if (r->override != 0) {
        r->override(obj, t0, t1, mode, arg);
        return 1;
    }
    n = r->count;
    c = r->cloths;
    if (mode == 2) {
        while (n-- != 0) {
            int f = r->check(c, arg) != 0;
            if (t0 != 0.0f)
                step(c, lc, f, t0, t1);
            c++;
        }
    } else {
        while (n-- != 0) {
            if (t0 != 0.0f)
                step(c, lc, mode, t0, t1);
            c++;
        }
    }
    return 1;
}
#endif
