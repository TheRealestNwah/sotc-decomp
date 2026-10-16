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
extern int getPointData(int, int);

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

int getPointDataByAreaIdx(char *w, int b, int area)
{
    PathE *e = getPathDataAddr(w, area);

    if (e != 0)
        return getPointData(*(int *)((char *)e + 0x4), b);
    return 0;
}
