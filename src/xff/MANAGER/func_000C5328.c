extern void *create_and_init_particle_effect_lod(void *, int, int, int, int);
extern void iosFree(void *);

static void *func_000C5328(void **pp, int a, int b, int c)
{
    void *r = 0;

    if (*pp != 0) {
        r = create_and_init_particle_effect_lod(*pp, 0, a, b, c);
        if (r == 0)
            __asm__ __volatile__("break 0");
        iosFree(*pp);
        *pp = 0;
    }
    return r;
}
