typedef struct {
    char *data;
    int *point;
    int *line;
    int *root;
    int f10;
    int f14;
    char pad[0xC];
} PathE;

typedef struct {
    PathE e[4];
    int n;
    int pad;
} PathSet;

extern PathSet *getPathInfo(char *);
typedef int s128 __attribute__((mode(TI)));

extern char *getPointData(int *, int);

static inline char *findPoint(char *w, int id)
{
    PathSet *s = getPathInfo(w);
    int i;
    unsigned int j;

    for (i = 0; i < s->n; i++) {
        int *arr = s->e[i].point;

        if (arr == 0)
            continue;
        for (j = 0; j < *arr; j++) {
            char *p = getPointData(arr, j);

            if (p != 0 && id == *(short *)(p + 0x1C))
                return p;
        }
    }
    return 0;
}

int getPointPosFromEvent(char *w, int id, s128 *out)
{
    char *p = findPoint(w, id);

    if (p != 0) {
        *out = *(s128 *)p;
        return 1;
    }
    return 0;
}
