extern int *B_00149AB0[];
extern void func_000CBAD0(int *, float);
extern void func_000CBAE8(int *, float);
extern void func_000CBB00(int *, float);
extern void func_000CB9E0(int *);
extern void func_000CBA30(int *);
extern void func_000CBA80(int *);
extern void iosFree(void *);

static inline void doit_emitter(int *e, float f)
{
    if (e[0] == 0)
        func_000CBAD0(e, f);
    else if (e[0] == 1)
        func_000CBAE8(e, f);
    else
        func_000CBB00(e, f);
}

static inline void destroy_emitter(int **p)
{
    int *e = *p;
    if (e == 0)
        return;
    if (e[0] == 0)
        func_000CB9E0(e);
    else if (e[0] == 1)
        func_000CBA30(e);
    else
        func_000CBA80(e);
    iosFree(*p);
    *p = 0;
}

void doit_wind_manager(float f)
{
    int i;

    for (i = 0; i < 80; i++) {
        if (B_00149AB0[i] == 0)
            continue;
        doit_emitter(B_00149AB0[i], f);
        if (B_00149AB0[i][0x28] == 0)
            destroy_emitter(&B_00149AB0[i]);
    }
}
