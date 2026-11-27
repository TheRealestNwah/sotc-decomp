/* Parked: 28 words off. Collects every path point of the active area (B_001A57E8 table) within
   the squared radius at +0x3B8 of the given object, as 8-byte {index, area, squared distance}
   entries after the count in out[0], then selection-sorts them by distance. The VU distance
   temp and the swap temp share sp+0 in the original (a union here), and the point loop and the
   sort share one counter. Remaining: the out[0] = 0 store is scheduled before the radius load,
   $a0/$v1 swapped in the sort's address math, and out[0]++ is loaded before the swap. */
#ifdef NONMATCHING
#include "vu0.h"
typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;

typedef struct {
    unsigned short index;
    short area;
    float dist;
} PointEntry;

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
extern Vec4 *getPointDataByAreaIdx(char *, int, int);

void execPointListSort(char *obj, int *out, Vec4 *pos)
{
    PointEntry *entries = (PointEntry *)(out + 1);
    AreaTable *table;
    float radius;
    float radiusSq;
    unsigned int n = 0;
    unsigned int i;
    int a;
    union { Vec4 v; PointEntry e; } u __attribute__((aligned(16)));

    table = (AreaTable *)(B_001A57E8 + *(int *)(obj + 0x3C50) * 0x98);
    radius = *(float *)(obj + 0x3B8);
    out[0] = 0;
    radiusSq = radius * radius;
    for (a = 0; a < table->count; a++) {
        int *list = table->rec[a].list;
        int area = *(int *)(table->rec[a].owner + 0x1C);

        if (list != 0) {
            for (i = 0; i < (unsigned int)*list; i++) {
                Vec4 *p = getPointDataByAreaIdx(obj, i, area);
                float d;

                vu0_sub4(&u.v, pos, p);
                d = vu0_dot3(&u.v, &u.v);
                if (d <= radiusSq) {
                    entries[n].dist = d;
                    entries[n].index = i;
                    entries[n].area = area;
                    n++;
                }
            }
        }
    }
    for (i = 0; i < n; i++) {
        unsigned int best = i;
        unsigned int j;

        for (j = i + 1; j < n; j++) {
            if (entries[j].dist < entries[best].dist)
                best = j;
        }
        u.e = entries[i];
        entries[i] = entries[best];
        entries[best] = u.e;
        out[0]++;
    }
}
#endif
