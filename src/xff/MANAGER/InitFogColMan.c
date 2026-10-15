typedef struct { int p; } Group;
typedef struct { char pad[0x98]; Group g[3]; int a[128]; char pad2[0xC]; } FogColMan;
extern FogColMan B_00148A40;
extern void *memset(void *, int, unsigned int);
extern void isysInitGroup(Group *);

void InitFogColMan(void)
{
    FogColMan *m = &B_00148A40;
    int i;
    memset(m, 0, 0x2B0);
    for (i = 127; i >= 0; i--)
        m->a[i] = 0;
    isysInitGroup(&m->g[0]);
    isysInitGroup(&m->g[1]);
    isysInitGroup(&m->g[2]);
}
