typedef int s128 __attribute__((mode(TI)));

typedef struct {
    char pad[0x2C];
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
extern char *GetLayoutClass(void *);
extern SObjNode *getSObjNode(void *);
extern void AI_InitAnimalOptimize(void *);
extern void AI_InitSurpriseArrow(void *);
extern void AI_InitGexCommonWork(void *);
extern void AI_SetAnimalWorkParam(void *, void *);
extern void func_000B1FE0(char *);

#define F(o) (*(float *)(a + (o)))
#define I(o) (*(int *)(a + (o)))
#define Q(o) (*(s128 *)(a + (o)))

static void func_000B2890(char *a)
{
    char *lay = GetLayoutClass(isysGetThisSubThread());
    void *th;
    SObjNode *n;

    AI_InitAnimalOptimize(a + 0x14);
    I(0x4C) = 0;
    I(0x198) = 5;
    I(0x19C) = 5;
    I(0x190) = 0;
    I(0x194) = 1;
    I(0x130) = 0;
    I(0x13C) = 0;
    F(0x1A4) = 1.0f;
    I(0x124) = 0;
    I(0x128) = 0;
    I(0x134) = 0;
    I(0x138) = 0;
    I(0x120) = 1;
    I(0x1AC) = 0;
    AI_InitSurpriseArrow(a + 0x1B4);
    I(0x1BC) = 1;
    I(0x1D4) = 0;
    I(0x1D8) = 0;
    F(0x1DC) = 3.40282347e+38f;
    __asm__ __volatile__("sqc2 vf0, 0x0(%0)" : : "r"(a + 0x1E0) : "memory");
    __asm__ __volatile__("sqc2 vf0, 0x0(%0)" : : "r"(a + 0x1F0) : "memory");
    Q(0x110) = **(s128 **)(lay + 0x134);
    Q(0x150) = **(s128 **)(GetLayoutClass(*(void **)(a + 0x44)) + 0x134);
    F(0x200) = 1.0f;
    I(0x140) = 0;
    I(0x148) = 0;
    I(0x204) = 0;
    I(0x208) = 0;
    I(0x20C) = 0;
    AI_InitGexCommonWork(a + 0x1C0);
    AI_SetAnimalWorkParam(a, a + 0x1C0);
    func_000B1FE0(a);
    th = isysGetThisSubThread();
    n = getSObjNode(th);
    if (n != 0) {
        if (SH_SmallAnimalTypeDEFAULT.types != 0)
            I(0x1BC) = SH_SmallAnimalTypeDEFAULT.types[n->type].layout;
        F(0x34) = n->f40;
        F(0x30) = n->f30;
        Q(0x20) = n->pos;
        I(0x8) = n->s52;
        I(0x4) = n->s50;
    } else {
        F(0x34) = 100.0f;
        F(0x30) = 15.0f;
        Q(0x20) = **(s128 **)(GetLayoutClass(th) + 0x134);
    }
}
