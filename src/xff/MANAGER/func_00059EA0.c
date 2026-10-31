typedef float sceVu0FVECTOR[4] __attribute__((aligned(16)));

typedef struct {
    int id;
    int pad;
} Surface;

typedef struct {
    int id;
    int index;
} SurfaceKey;

typedef struct {
    int count;
    int limit;
    int pad;
    Surface *surfaces;
} SurfaceList;

extern void GetCollisionDBSurfBoundary(sceVu0FVECTOR boundary, void *surface);

#define NEAR(x) ((x) < 0.0f ? -0.1f < (x) : (x) < 0.1f)

static Surface *func_00059EA0(SurfaceKey *key, SurfaceList *list)
{
    sceVu0FVECTOR base;
    sceVu0FVECTOR boundary;
    sceVu0FVECTOR diff;
    Surface *s;
    int id;
    int i;

    if (key->index < 0) {
        i = list->count;
        if (list->limit < i)
            i = list->limit;
        s = list->surfaces;
        id = key->id;
        GetCollisionDBSurfBoundary(base, key);
        for (i--; i != -1; i--, s++) {
            if (s->id == 0)
                continue;
            if (s->id == id)
                continue;
            GetCollisionDBSurfBoundary(boundary, s);
            if (!NEAR(boundary[3] - base[3]))
                continue;
            __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                                 "lqc2 vf6, 0x0(%2)\n"
                                 "vsub.xyzw vf7, vf5, vf6\n"
                                 "sqc2 vf7, 0x0(%0)\n"
                                 : : "r"(diff), "r"(boundary), "r"(base) : "memory");
            if (NEAR(diff[0]) && NEAR(diff[1]) && NEAR(diff[2]))
                return s;
        }
    }
    return 0;
}
