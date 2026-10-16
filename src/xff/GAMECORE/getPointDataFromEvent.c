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

char *getPointDataFromEvent(char *w, int id, int *idx)
{
    PathSet *s = getPathInfo(w);
    int i;
    unsigned int j;

    if (idx != 0)
        *idx = -1;
    for (i = 0; i < s->n; i++) {
        int *arr = s->e[i].point;

        if (arr == 0)
            continue;
        for (j = 0; j < *arr; j++) {
            char *p = getPointData(arr, j);

            if (p != 0 && id == *(short *)(p + 0x1C)) {
                if (idx != 0)
                    *idx = j;
                return p;
            }
        }
    }
    return 0;
}
