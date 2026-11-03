typedef struct { char pad[8]; int count; char pad2[0xC8]; char *effects; } Particle;
extern void *memcpy(void *, const void *, unsigned int);
extern void constructor_particle_effect_lod_except_npe(Particle *);
extern int recreate_particle_effects(Particle *, int);

static int func_000C9C00(Particle *p, char *src, unsigned int size, unsigned int esize, int flag)
{
    int i;
    int count;
    unsigned int len;

    memcpy(p, src, size > 0x140 ? 0x140 : size);
    src += size;
    constructor_particle_effect_lod_except_npe(p);
    if (flag != 0)
        count = 3;
    else
        count = p->count + 1;
    if (!recreate_particle_effects(p, count))
        return 0;
    len = esize > 0x1BC ? 0x1BC : esize;
    for (i = 0; i < count; i++) {
        memcpy(p->effects + i * 0x1BC, src, len);
        src += esize;
    }
    return 1;
}
