#ifdef NONMATCHING /* 18 diffs: target schedules the two 1.0f stores after the struct-copy loads (the target reads 0x8/0x10 before the 0xC/0x14 float stores, so p gets zeros there: a type-based alias reordering). Tried: long-only struct with float* stores and a long-typed copy (16, stores deleted as dead), stores after the copy (16), one store each side of the copy or int-bit stores (14). Permuter (20 min) found nothing valid. */
extern void *memset(void *, int, unsigned int);
typedef struct { int a; int b; int c; float d; int e; float f; long g[3]; } ColDyn;
void ConstructorCollisionDynamics(ColDyn *p)
{
    ColDyn t;
    memset(&t, 0, sizeof(t));
    t.f = 1.0f;
    t.d = 1.0f;
    *p = t;
}
#endif
