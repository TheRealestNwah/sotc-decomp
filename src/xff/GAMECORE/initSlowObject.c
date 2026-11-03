typedef struct { void *name; int a; void *b; char pad[0x30]; int c; char pad2[0x20]; void *disp; int pad3; void *clip; void *light; char pad4[0xC]; } Desc;
extern void *memset(void *, int, unsigned int);
extern int DldSysUndefSymbol;
extern char rootPtn[];
extern unsigned char RO_0017CCE0[];
extern char B_00188610[];
extern void DispLayoutObjModel(void *, void *);
extern int ClipLayoutObjModel();
extern int CalcLightLayoutObj();
extern void *CreateLayoutObjVU0Secure(void *, int, Desc *);
extern void isysAddGroupWithLinkParam(void *, void *, int, int);

static inline char *resolve(unsigned int *h)
{
    unsigned int v = *h;
    int off = v & 0x3FFFF;
    char *t = off != 0 ? *(char **)((char *)h - off) : 0;
    return (t != 0 && t != (char *)DldSysUndefSymbol) ? *(char **)(t + 0x10) + ((v >> 18) & 0xFFF) * *(int *)(*(char **)(t + 8) + 0xC) : 0;
}

void initSlowObject(char *list)
{
    int n = *(int *)(list + 0xC);
    char *e = *(char **)(list + 0x10);
    int i;

    for (i = 0; i < n; i++, e += 0xC) {
        char *p = resolve((unsigned int *)(e + 4));
        void *model;
        p = resolve((unsigned int *)(p + 4));
        model = *(void **)(p + 8);
        if (model != 0) {
            Desc d;
            void *obj;
            memset(&d, 0, 0x7C);
            d.name = RO_0017CCE0;
            d.a = 1;
            d.c = 6;
            d.b = model;
            d.disp = DispLayoutObjModel;
            d.clip = ClipLayoutObjModel;
            d.light = CalcLightLayoutObj;
            obj = CreateLayoutObjVU0Secure(rootPtn, 0, &d);
            if (obj != 0)
                isysAddGroupWithLinkParam(obj, B_00188610, 0, 0);
        }
    }
}
