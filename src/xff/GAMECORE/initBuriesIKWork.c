typedef struct {
    char pad0[0x10];
    int a;
    int c;
    int b;
    char pad1C[4];
} BuriesIKNode;

typedef struct {
    int nodes;
    int n;
} BuriesIKWork;

extern int GetCharacterClassInitParamNbOptionNodes(void *);

void initBuriesIKWork(void *obj, void *param, BuriesIKWork *w)
{
    int i = 0;

    w->nodes = (int)(w + 2);
    w->n = GetCharacterClassInitParamNbOptionNodes(param);
    for (; i < w->n; i++) {
        ((BuriesIKNode *)w->nodes)[i].a = 0;
        ((BuriesIKNode *)w->nodes)[i].b = 0;
        ((BuriesIKNode *)w->nodes)[i].c = 0;
    }
}
