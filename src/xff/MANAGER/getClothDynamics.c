#ifdef NONMATCHING /* 61 diffs: the copy loops use beql instead of beq, and the vertex/count registers swap */
typedef struct { int a; int b; char pad8[8]; int c; int d; } ClothVert;
typedef struct { int pad0; int count; } ClothHeader;
typedef struct { ClothHeader *header; char pad4[8]; ClothVert *verts; char pad10[0x70]; unsigned char flip; } Cloth;
typedef void (*ClothCallback)(Cloth *, void *, void *);
extern void func_000BBE58(Cloth *, void *, float, float);
extern void func_000BC5C8(Cloth *, void *, int);
extern void func_000BC3B0(Cloth *, void *, float, float);

int getClothDynamics(Cloth *cloth, void *work, int unused, ClothCallback callback, void *arg, float t0, float t1)
{
    if (t0 != 0.0f) {
        ClothVert *v;
        int n;
        ClothHeader *h = cloth->header;
        v = cloth->verts;
        cloth->flip = (cloth->flip + 1) & 1;
        n = h->count;
        if (cloth->flip) {
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
        func_000BBE58(cloth, work, t0, t1);
        if (callback) {
            callback(cloth, work, arg);
        } else {
            func_000BC5C8(cloth, work, 0);
        }
        func_000BC3B0(cloth, work, t0, t1);
    }
    return 1;
}
#endif
