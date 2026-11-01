typedef struct {
    char pad0[8];
    unsigned int flags;
    char padC[4];
    short a;
    short b;
} LineData;

typedef struct {
    unsigned int count;
} LineGroup;

typedef struct {
    LineGroup *group;
    char pad4[0x20];
} PathEntry;

typedef struct {
    char pad0[8];
    PathEntry e[3];
    char pad74[0x90 - 0x74];
    int count;
} PathInfo;

extern PathInfo *getPathInfo(void *);
extern LineData *getLineData(LineGroup *, unsigned int);

void setEventLineDir(void *obj, int id, unsigned int mode)
{
    PathInfo *info = getPathInfo(obj);
    int i;

    for (i = 0; i < info->count; i++) {
        LineGroup *g = info->e[i].group;
        unsigned int j;
        if (!g)
            continue;
        for (j = 0; j < g->count; j++) {
            LineData *l = getLineData(g, j);
            if (id == l->a || id == l->b) {
                l->flags &= ~0x70;
                switch (mode) {
                case 0:
                    l->flags |= 0x10;
                    break;
                case 1:
                    l->flags |= 0x20;
                    break;
                case 2:
                    l->flags |= 0x40;
                    break;
                }
            }
        }
    }
}
