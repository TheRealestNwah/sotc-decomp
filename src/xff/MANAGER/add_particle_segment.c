extern int DldSysUndefSymbol;
extern void iosPushVu0RegistersToWork(char *);
extern void iosPopVu0RegistersFromWork(char *);
static int *func_000C53A0(void);
static int create_particle_texture_and_get_id(void *);
static int func_000C5328(void *, int, int *, char *);

static inline void *dldElem(unsigned int *h)
{
    unsigned int v = *h;
    unsigned int off = v & 0x3FFFF;
    int *t = off != 0 ? *(int **)((char *)h - off) : 0;
    if (t != 0 && t != (int *)DldSysUndefSymbol)
        return (void *)(t[4] + ((v >> 18) & 0xFFF) * ((int *)t[2])[3]);
    return 0;
}

void add_particle_segment(int *s)
{
    char vu0Registers[0x400] __attribute__((aligned(16)));
    int *ps;
    int i;

    if (s == 0)
        return;
    iosPushVu0RegistersToWork(vu0Registers);
    ps = func_000C53A0();
    ps[0] = s[0];
    ps[1] = (int)s;
    ps[2] = s[3];
    ps[3] = s[4];
    for (i = 0; i < ps[2]; i++) {
        char *e = (char *)ps[3] + i * 0x54;
        int tex = create_particle_texture_and_get_id(dldElem((unsigned int *)(e + 0x20)));
        *(int *)(e + 0x48) = func_000C5328(e + 0xC, tex, s, e);
        *(int *)(e + 0x4C) = func_000C5328(e + 0x1C, -1, s, e);
    }
    iosPopVu0RegistersFromWork(vu0Registers);
}
