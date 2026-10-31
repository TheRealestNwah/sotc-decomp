typedef int qword __attribute__((mode(TI)));

typedef union {
    qword q;
    float v[4];
} Vec;

extern int ClipCollisionDirectCallBack(void *, float *, float *, int, int, int, int, int, int);
extern void CopyGeometryPointer(void *, void *);

static inline int getCollision(void *out, qword *a, qword *b, int d, int e, int f)
{
    Vec va;
    Vec vb;
    char buf[0x50] __attribute__((aligned(16)));
    int r;

    va.q = *a;
    va.v[3] = 1.0f;
    vb.q = *b;
    vb.v[3] = 1.0f;
    r = ClipCollisionDirectCallBack(buf, va.v, vb.v, d, 0, 0, 0, e, f);
    if (r != 0 && out != 0)
        CopyGeometryPointer(out, buf);
    return r;
}

int SCRGetCollision(void *out, qword *a, qword *b, int d)
{
    return getCollision(out, a, b, d, 0, 0);
}
