typedef struct Ptn Ptn;
extern Ptn rootPtn;
extern void func_000420B8();
extern unsigned char RO_0017D138[];
extern void *_gcCreateChildScriptObj(void *, void *, Ptn *, int, int, int, void *, void *);

void bootTexAlphaAnim(void *parent, int *st, float a, float b)
{
    *(float *)&st[3] = b;
    *(float *)&st[2] = a;
    if (st[0] == 0) {
        st[0] = 1;
        _gcCreateChildScriptObj(func_000420B8, st, &rootPtn, 0x4000, 0, 4, RO_0017D138, parent);
        st = 0;
    }
}
