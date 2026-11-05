typedef int s128 __attribute__((mode(TI)));

typedef union {
    s128 q;
    float f[4];
} VecQ;

typedef struct {
    char pad[0x1C];
    int f1C;
    char pad20[0xC];
    int layout;
    char pad30[0x4];
} AnimalType;

typedef struct {
    char pad[0x10];
    AnimalType *types;
} AnimalTypeTable;

typedef struct {
    char pad[0x20];
    s128 pos;
    float f30;
    short type;
    char pad36[0xA];
    float f40;
    char pad44[0xC];
    short s50;
    short s52;
} SObjNode;

extern AnimalTypeTable SH_SmallAnimalTypeDEFAULT;
extern void *isysGetThisSubThread(void);
extern SObjNode *getSObjNode(void *);
extern char *GetLayoutClass(void *);
extern void AI_SetAnimalLayout(char *, VecQ *, float, float);
extern void Kite_SetAnimalLayout(void *, VecQ *, float, float, float);

typedef union { int i; short s; } IS;

static void func_000A9FA8(char *o)
{
    VecQ p;
    VecQ p2;
    float r;
    float h;
    AnimalType *ty;
    void *t = isysGetThisSubThread();
    SObjNode *n = getSObjNode(t);

    if (n != 0) {
        if (*(int *)o == 8) {
            h = n->f40;
            r = n->f30;
            p.q = n->pos;
            AI_SetAnimalLayout(o + 0x800, &p, r, h);
            h = h * 0.5f;
            p.f[1] += h * 0.5f;
        } else {
            r = n->f30;
            h = n->f40;
            p.q = n->pos;
        }
        Kite_SetAnimalLayout(o + 0x470, &p, r, h, *(float *)(*(char **)(o + 0x20) + 0x14));
        ((IS *)(o + 0x8))->i = n->s52;
        ((IS *)(o + 0x4))->i = n->s50;
        ty = SH_SmallAnimalTypeDEFAULT.types;
        if (ty != 0) {
            if (ty[n->type].f1C != 0) {
                ((IS *)(o + 0x288))->i = 0;
            }
            *(int *)(o + 0x7C4) = ty[n->type].layout;
        }
    } else {
        char *l = GetLayoutClass(t);

        if (*(int *)o != 8) {
            p2.q = **(s128 **)(l + 0x134);
            Kite_SetAnimalLayout(o + 0x470, &p2, 20.0f, 10.0f, *(float *)(*(char **)(o + 0x20) + 0x14));
        }
        *(int *)(o + 0x8) = 0;
        *(int *)(o + 0x4) = -1;
    }
}
