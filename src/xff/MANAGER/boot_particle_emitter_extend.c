typedef unsigned int s128 __attribute__((mode(TI)));

extern void GetGeometryPointerPosition(void *, void *);
extern void **isysGroupForFirst(void *, int);
extern void **isysGroupForNext(void **, int);
extern void isysGroupForExit(void *, int);
extern void isysAddGroupWithLinkParam(void *, void *, int, int);
extern int *get_top_emitter_list_from_particle_geodisp(void *);
extern void *create_and_boot_particle_geodisp(void *, int, int, int, int);
extern int func_000C5718(int *, s128 *, void *, int, int, int, int);
extern char B_001499C0[];

static void *func_000C54B0(int);
static int func_000C54B8(void *, int, int, int, int);

int boot_particle_emitter_extend(int on, int a, int b, int c, int d)
{
    int r;
    if (on != 0) {
        r = func_000C54B8(func_000C54B0(on), a, b, c, d);
        if (r == 0)
            r = -1;
        return r;
    }
    return 0;
}

static void *func_000C54B0(int on)
{
    return (void *)on;
}

static int func_000C54B8(void *def, int a, int b, int c, int d)
{
    s128 pos;
    void **it;
    void *geo;
    int r;
    void *g;

    r = 0;
    if (*(int *)((char *)def + 0x2C) != 0) {
        geo = 0;
        GetGeometryPointerPosition(&pos, (void *)a);
        for (it = isysGroupForFirst(B_001499C0, 0); it != 0; it = isysGroupForNext(it, 0)) {
            geo = *it;
            r = func_000C5718(get_top_emitter_list_from_particle_geodisp(geo), &pos, def, a, b, c, d);
            if (r != 0) {
                break;
            }
        }
        if (geo != 0) {
            isysGroupForExit(geo, 0);
        }
    }
    if (r == 0) {
        g = create_and_boot_particle_geodisp(def, a, b, c, d);
        if (g != 0) {
            isysAddGroupWithLinkParam(g, B_001499C0, 0, 0);
            r = *get_top_emitter_list_from_particle_geodisp(g);
        }
    }
    return r;
}
