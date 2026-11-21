typedef struct { short x; short y; short w; short pad; } Span;
typedef struct { int kind; int pad4[4]; int n; Span *list; } Grp;
typedef struct { unsigned int lo : 4; unsigned int hi : 28; } ChipFlags;
typedef struct { int data[2]; ChipFlags flags[2]; Grp *grp; int f14; } ChipRow;
typedef struct { char pad0[8]; ChipRow *chips; char padC[0x3C]; int width; int height; } MapSize;
typedef struct SeamlessObj {
    int x;
    int y;
    int layer;
    int id;
    int arg;
    struct SeamlessObj *prev;
    struct SeamlessObj *next;
} SeamlessObj;

extern MapSize D_0017A340;
extern SeamlessObj *D_0017A3D4;
extern int D_0017A314;
extern int D_0017A318;
extern int func_0001EC38(void *);
extern void func_0001FA68(int, int, int);

static inline int get_chip_no(int x, int y)
{
    if (x < 0 || x >= D_0017A340.width || y < 0 || y >= D_0017A340.height)
        return -1;
    return y * D_0017A340.width + x;
}

static inline int get_chip_state(int layer, int group)
{
    if (group != -1)
        return D_0017A340.chips[group].flags[layer].lo;
    return 7;
}

static inline int get_kind(int c)
{
    return D_0017A340.chips[c].grp != 0 ? D_0017A340.chips[c].grp->kind : 0;
}

static inline int unload_ready(SeamlessObj *o)
{
    if (get_chip_state(o->layer, get_chip_no(o->x, o->y)) == 6) {
        func_0001EC38(o);
        func_0001FA68(o->layer, o->x, o->y);
        return 1;
    }
    return 0;
}

#define ABS(x) ((x) < zero ? -(x) : (x))
#define FAR(d) (ABS((float)(d) + half) > (float)(D_0017A314 + D_0017A318))

static void func_00021020(int px, int pz, int x, int z)
{
    Grp *g = D_0017A340.chips[get_chip_no(x, z)].grp;
    int kind = get_kind(get_chip_no(x, z));
    SeamlessObj *o;
    float half, zero;

    switch (kind) {
    case 1:
    case 2:
    case 3:
        o = D_0017A3D4;
        if (o != 0) {
            half = 0.5f;
            zero = 0.0f;
            do {
                Grp *og = D_0017A340.chips[get_chip_no(o->x, o->y)].grp;
                if (!unload_ready(o)) {
                    if ((og != g && D_0017A340.chips[get_chip_no(x, z)].f14 == 0)
                        || FAR(o->x - px) || FAR(o->y - pz)) {
                        func_0001EC38(o);
                        func_0001FA68(o->layer, o->x, o->y);
                    }
                }
                o = o->next;
            } while (o != 0);
        }
        break;
    case 5:
        for (o = D_0017A3D4; o != 0; o = o->next) {
            int found = 0;
            int i;
            Span *e;
            if (unload_ready(o))
                continue;
            for (i = 0, e = g->list; i < g->n; i++, e++) {
                if (e->x <= o->x && o->x < e->x + e->w && e->y == o->y) {
                    found = 1;
                    break;
                }
            }
            if (!found) {
                func_0001EC38(o);
                func_0001FA68(o->layer, o->x, o->y);
            }
        }
        break;
    case 0:
    case 4:
        o = D_0017A3D4;
        if (o != 0) {
            half = 0.5f;
            zero = 0.0f;
            do {
                int c = get_chip_no(o->x, o->y);
                if (!unload_ready(o)) {
                    if ((get_kind(c) == 3 && D_0017A340.chips[c].f14 == 0)
                        || FAR(o->x - px) || FAR(o->y - pz)) {
                        func_0001EC38(o);
                        func_0001FA68(o->layer, o->x, o->y);
                    }
                }
                o = o->next;
            } while (o != 0);
        }
        break;
    }
}
