typedef struct {
    unsigned int n;
} PList;

typedef struct {
    char *data;
    char pad4[8];
    PList *list;
    char pad10[0x14];
} PathE;

typedef struct {
    PathE e[4];
    int n;
    int pad;
} PathSet;

extern PathSet B_001A57E8[];
extern char *getRootPointData(PList *, int);
extern PathE *getPathDataAddr(char *, int);

int getRootPointIdxForGroupID(char *w, int id, int path, int *out)
{
    PathSet *s = &B_001A57E8[*(int *)(w + 0x3C50)];
    PathE *e;
    unsigned int i;
    int k;

    if (path < 0) {
        for (k = 0; k < s->n; k++) {
            PathE *p = &s->e[k];

            if (p->list != 0) {
                for (i = 0; i < p->list->n; i++) {
                    if (id == *(int *)(getRootPointData(p->list, i) + 0x10)) {
                        *out = *(int *)(p->data + 0x1C);
                        return i;
                    }
                }
            }
        }
    } else {
        e = getPathDataAddr(w, path);
        if (e != 0 && e->list != 0) {
            for (i = 0; i < e->list->n; i++) {
                if (id == *(int *)(getRootPointData(e->list, i) + 0x10)) {
                    *out = *(int *)(e->data + 0x1C);
                    return i;
                }
            }
        }
    }
    *out = -1;
    return -1;
}
