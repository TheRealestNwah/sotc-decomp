/* Parked draft: collects every path point of the active area (B_001A57E8 table) within the
   squared radius at +0x3B8 of the given object, as 8-byte {index, area, squared distance}
   entries after the count in out[0], then selection-sorts them by distance (the swaps are
   unaligned 8-byte struct copies, ldl/ldr in the original). Written from the m2c draft; not yet
   compared closely. */
#ifdef NONMATCHING
typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;

typedef struct {
    unsigned short index;
    short area;
    float dist;
} __attribute__((packed)) PointEntry;

typedef struct {
    char *owner;
    int *list;
    char pad8[0x1C];
} AreaRecord;

typedef struct {
    AreaRecord rec[4];
    int count;
} AreaTable;

extern char B_001A57E8[];
extern Vec4 *getPointDataByAreaIdx(char *, unsigned int, int, char *);

static inline float distSq(Vec4 *a, Vec4 *b)
{
    float r;
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyzw vf7, vf5, vf6\n"
                         "sqc2 vf7, 0x0(%3)\n"
                         "lqc2 vf5, 0x0(%3)\n"
                         "lqc2 vf6, 0x0(%3)\n"
                         "vaddw.x vf7, vf0, vf0w\n"
                         "vmul.xyz vf6, vf5, vf6\n"
                         "vaddax.x ACC, vf0, vf6x\n"
                         "vmadday.x ACC, vf7, vf6y\n"
                         "vmaddz.x vf6, vf7, vf6z\n"
                         "qmfc2.ni $2, vf6\n"
                         "mtc1 $2, %0\n"
                         : "=f"(r) : "r"(a), "r"(b), "r"(&r) : "$2", "memory");
    return r;
}

void execPointListSort(char *obj, int *out, int unused)
{
    PointEntry *entries = (PointEntry *)(out + 1);
    AreaTable *table = (AreaTable *)(B_001A57E8 + *(int *)(obj + 0x3C50) * 0x98);
    float radius = *(float *)(obj + 0x3B8);
    float radiusSq = radius * radius;
    unsigned int n = 0;
    unsigned int i;
    int a;

    out[0] = 0;
    for (a = 0; a < table->count; a++) {
        int *list = table->rec[a].list;
        int area = *(int *)(table->rec[a].owner + 0x1C);

        if (list != 0 && *list != 0) {
            unsigned int k;

            for (k = 0; k < (unsigned int)*list; k++) {
                Vec4 *p = getPointDataByAreaIdx(obj, k, area, obj);
                float d = distSq((Vec4 *)obj, p);

                if (d <= radiusSq) {
                    entries[n].dist = d;
                    entries[n].index = k;
                    entries[n].area = area;
                    n++;
                }
            }
        }
    }
    for (i = 0; i < n; i++) {
        unsigned int best = i;
        unsigned int j;
        PointEntry tmp;

        for (j = i + 1; j < n; j++) {
            if (entries[j].dist < entries[best].dist)
                best = j;
        }
        tmp = entries[i];
        entries[i] = entries[best];
        entries[best] = tmp;
        out[0]++;
    }
}
#endif
