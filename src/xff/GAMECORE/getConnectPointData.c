typedef struct {
    char *data;
    char pad[0x20];
} PathE;

typedef struct {
    PathE e[4];
    int n;
    int pad;
} PathSet;

extern PathSet B_001A57E8[];
extern char *getPointData(unsigned int *, unsigned int);

static inline PathE *getPathDataAddr(char *w, int id)
{
    PathSet *s = &B_001A57E8[*(int *)(w + 0x3C50)];
    int i;

    for (i = 0; i < s->n; i++) {
        if (id == *(int *)(s->e[i].data + 0x1C))
            return &s->e[i];
    }
    return 0;
}


char *getConnectPointData(char *w, int area, int id, unsigned int *out)
{
    PathE *e;
    unsigned int i;
    char *p;

    if (area != -1 && id != -1) {
        e = getPathDataAddr(w, area);
        if (e != 0 && *(unsigned int **)((char *)e + 0x4) != 0) {
            for (i = 0; i < **(unsigned int **)((char *)e + 0x4); i++) {
                p = getPointData(*(unsigned int **)((char *)e + 0x4), i);
                if (*(short *)(p + 0x22) == id) {
                    if (out != 0)
                        *out = i;
                    return p;
                }
            }
        }
    }
    return 0;
}
