#ifdef NONMATCHING
/* Parked: 3 diffs. Was 4; the slot address is now int arithmetic for the addu operand order. Remaining: in the inlined findSlot loop the Original copies n to a1 and keeps e in a3; ours copies e. Register pins inside the inline and swapped parameter order make it worse. Permuter tried earlier. */
extern int DldSysUndefSymbol;
typedef struct { char pad0[0xC]; int size; } DldType;
typedef struct { char pad0[8]; DldType *type; char padC[4]; char *data; } DldTable;
typedef struct { char pad0[0x28]; int handle; } Geometry;
static inline void *dldElement(int *h)
{
    int off = *h & 0x3FFFF;
    DldTable *t = off != 0 ? *(DldTable **)((char *)h - off) : 0;
    return (t != 0 && t != (DldTable *)DldSysUndefSymbol) ? t->data + (((unsigned int)*h >> 18) & 0xFFF) * t->type->size : 0;
}
typedef struct {
    char pad0[4];
    void *elem;
    char pad8[4];
    float len;
    char pad10[0x1C];
    float scale;
    char pad30[0x14];
    int state;
    char pad48[8];
    float a;
    float b;
    char pad58[0x28];
} Slot;
extern void func_00051A60(void *, void *, int, void *);
static inline int findSlot(Slot *p, int n, void *e)
{
    int i;
    for (i = 0; i < n; i++, p++) {
        if (p->state != -2 && p->elem == e)
            return i;
    }
    return -1;
}
static inline int findFree(Slot *p, int n)
{
    int i;
    for (i = 0; i < n; i++, p++) {
        if (p->state == -2)
            return i;
    }
    return -1;
}
static void func_00052EA8(void *w, unsigned char *o, unsigned char *m)
{
    void *e;
    Slot *s;
    Slot *r;
    int n;
    int i;
    int ok;
    float t;
    void **new_var;
    float a;
    float b;
    float len;

    e = dldElement((int *)(m + 8));
    s = *(Slot **)(o + 0x30C);
    n = *(int *)(o + 0x3FC);
    i = findSlot(s, n, e);
    a = 0.0f;
    b = 1.0f;
    ok = 0;
    if (i < 0) {
        i = findFree(s, n);
        if (i >= 0)
            ok = 1;
    } else {
        char *q = (char *)(i * 128 + (int)s) + 4;
        t = *(float *)(m + 0xC);
        len = *(float *)(q + 8);
        if (!(t < 0.0f))
            t *= *(float *)(q + 0x28);
        if (t >= 0.0f && t < len) {
            a = *(float *)(m + 0x10);
            ok = 1;
            b = 0.0f;
        }
    }
    new_var = &e;
    if (ok) {
        r = &s[i];
        func_00051A60(w, o, i, *new_var);
        r->a = a;
        r->b = b;
    }
}
#endif
