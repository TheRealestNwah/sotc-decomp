extern void *memset(void *, int, unsigned int);
extern void doit_double_spring_interp_cntrl3D(void *, void *, int, float);

static void func_000E2118(void *self, float t, int u1, int u2, int p)
{
    char tmp[0x10];

    memset(tmp, 0, 0x10);
    doit_double_spring_interp_cntrl3D(self, tmp, p, t);
}
