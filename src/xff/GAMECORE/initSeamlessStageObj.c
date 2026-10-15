typedef struct { void *name; int a; void *b; char pad[0x30]; int c; char pad2[0x20]; void *disp; int pad3; void *clip; void *light; char pad4[0xC]; } Desc;
extern void *memset(void *, int, unsigned int);
extern unsigned char RO_0017CCD0[];
extern int DispLayoutObjModel();
extern int ClipLayoutObjModel();
extern int CalcLightLayoutObj();
extern void *CreateLayoutObj(void *, int, Desc *);

void *initSeamlessStageObj(void *a, void *b)
{
    Desc d;
    unsigned char *name = RO_0017CCD0;
    memset(&d, 0, 0x7C);
    d.name = name;
    d.b = b;
    d.a = 1;
    d.c = 6;
    d.disp = DispLayoutObjModel;
    d.clip = ClipLayoutObjModel;
    d.light = CalcLightLayoutObj;
    return CreateLayoutObj(a, 0, &d);
}
