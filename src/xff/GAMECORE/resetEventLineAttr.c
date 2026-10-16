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
extern char *getLineData(int *, int);

void resetEventLineAttr(char *w, int id)
{
    PathSet *s = getPathInfo(w);
    int i;
    unsigned int j;

    for (i = 0; i < s->n; i++) {
        int *arr = s->e[i].line;

        if (arr == 0)
            continue;
        for (j = 0; j < *arr; j++) {
            char *l = getLineData(arr, j);

            if (id == *(short *)(l + 0x10) || id == *(short *)(l + 0x12))
                *(int *)(l + 8) = *(int *)(l + 4);
        }
    }
}
