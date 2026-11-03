#ifdef NONMATCHING /* 18 diffs: target schedules the two 1.0f stores after the struct-copy loads */
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
