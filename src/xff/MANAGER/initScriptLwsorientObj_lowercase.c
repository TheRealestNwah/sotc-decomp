/* initScriptLwsorientObj: the file name avoids colliding with InitScriptLwsOrientObj.c on case-insensitive file systems. */
#ifdef NONMATCHING
/* 8 diffs (518 words, same size). Builds a 0x158-byte creation record from the Lws orient element (dld of src+4), the info block and the arguments, copies it to the outgoing by-value slot at sp+0 (arg declared before c) and calls CreateScriptLwsOri(heap, 0, rec). Stores go through an int/float union so loads from the element are not hoisted past them, as in the Original. Remaining: storing t0 (field 0x140) before t2 (field 0x134) is what gives the Original's s3 = t0, s4 = t2, but then the 0x134 store is scheduled after 0x29C instead of between 0x290 and 0x298 (6 diffs), and the field 0xE0 float copy uses $f1 instead of $f0 (2 diffs). */
extern int DldSysUndefSymbol;
extern char *D_00136C10;

typedef struct { char pad[0xC]; int size; } DldType;
typedef struct { char pad[8]; DldType *type; char pad2[4]; char *data; } DldTable;

typedef struct {
    int w[0x56];
} Def;

extern void *CreateScriptLwsOri(void *, int, Def);

static inline void *dldElement(int *h)
{
    int off = *h & 0x3FFFF;
    DldTable *t = off != 0 ? *(DldTable **)((char *)h - off) : 0;
    return (t != 0 && t != (DldTable *)DldSysUndefSymbol) ? t->data + (((unsigned int)*h >> 18) & 0xFFF) * t->type->size : 0;
}

#define W(o) (*(int *)((char *)e + (o)))
#define FL(o) (*(float *)((char *)e + (o)))
typedef union { int i; float f; } U;
#define CW(o) (((U *)((char *)&c + (o)))->i)
#define CF(o) (((U *)((char *)&c + (o)))->f)

void *initScriptLwsorientObj(int a0, void *heap, char *src, int *info, int t0, int t1, int t2, int t3, int t4)
{
    Def arg;
    Def c;
    char *e;
    char *p14, *p18, *p20;
    int v14, v18, v20;

    e = dldElement((int *)(src + 4));
    p14 = dldElement((int *)(e + 0x14));
    v14 = p14 != 0 ? *(int *)(p14 + 8) : 0;
    p18 = dldElement((int *)(e + 0x18));
    v18 = p18 != 0 ? *(int *)(p18 + 8) : 0;
    p20 = dldElement((int *)(e + 0x20));
    v20 = p20 != 0 ? *(int *)(p20 + 8) : 0;
    if (v14 == 0 && dldElement((int *)(e + 0x14)) != 0)
        return 0;
    if (v20 == 0 && dldElement((int *)(e + 0x20)) != 0)
        return 0;
    if (v18 == 0 && dldElement((int *)(e + 0x18)) != 0)
        return 0;

    CW(0x00) = W(0);
    CW(0x04) = 1;
    CW(0x08) = 0;
    CW(0x0C) = 0;
    CW(0x10) = 0;
    CW(0x14) = 0;
    CW(0x18) = 0;
    CW(0x1C) = 0;
    CW(0x20) = (int)dldElement((int *)(e + 0x128));
    CW(0x24) = info[8];
    CW(0x28) = info[0];
    CW(0x2C) = info[1];
    CW(0x30) = info[2];
    CW(0x34) = info[3];
    CW(0x38) = info[0xB];
    CW(0x3C) = info[0xD] | 7;
    CW(0x40) = info[4];
    CW(0x44) = 0;
    CW(0x48) = 0;
    CW(0x4C) = info[5];
    CF(0x50) = *(float *)&info[6];
    CW(0x54) = info[9];
    CW(0x58) = 0;
    CW(0x5C) = 0;
    CW(0x60) = 0;
    CW(0x64) = 0;
    CW(0x68) = 0;
    CW(0x6C) = 0;
    CW(0x70) = 0;
    CW(0x74) = info[0xA];
    CW(0x78) = 0;
    CW(0x7C) = (int)dldElement((int *)(e + 0xDC));
    CW(0x80) = *(short *)(e + 8);
    CW(0x84) = 0;
    CW(0x88) = (int)dldElement((int *)(e + 0xE4));
    CW(0x8C) = W(0xD4);
    CW(0x90) = (int)(D_00136C10 + 0x60);
    CW(0x94) = W(0x4C);
    CW(0x98) = W(0x48);
    CF(0x9C) = FL(0x44);
    CF(0xA0) = FL(0x74);
    CF(0xA4) = FL(0x88);
    CF(0xA8) = FL(0x98);
    CF(0xAC) = FL(0x94);
    CF(0xB0) = FL(0x8C);
    CF(0xB4) = FL(0x90);
    CF(0xB8) = FL(0x5C);
    CF(0xBC) = FL(0xAC);
    CF(0xC0) = FL(0xB4);
    CF(0xC4) = FL(0xB8);
    CF(0xC8) = FL(0xBC);
    CF(0xCC) = FL(0x54);
    CF(0xD0) = FL(0x60);
    CW(0xD4) = W(0x40);
    CW(0xD8) = (int)(e + 0xD0);
    CF(0xDC) = FL(0xC0);
    CF(0xE0) = FL(0xCC);
    CW(0xE4) = (int)(e + 0x104);
    CW(0xE8) = W(0x58);
    CW(0xEC) = info[0xC];
    CW(0xF0) = 0;
    CW(0xF4) = (int)(e + 0xF0);
    CW(0xF8) = (int)(e + 0xF4);
    CW(0xFC) = (int)(e + 0xF8);
    CW(0x100) = (int)(e + 0xDC);
    CW(0x104) = (int)(e + 0xD8);
    CW(0x108) = (int)(D_00136C10 + 0x18);
    CW(0x10C) = 0;
    CW(0x110) = (int)(dldElement((int *)(e + 0xE8)) != 0 ? dldElement((int *)(e + 0xE8)) : dldElement((int *)(e + 0xDC)));
    CW(0x114) = (int)(e + 0xB0);
    CW(0x118) = (int)e;
    CW(0x11C) = (int)src;
    CW(0x120) = a0;
    CW(0x124) = t1;
    CW(0x128) = 0;
    CF(0x12C) = *(float *)(src + 0xC) * 0.5f;
    CW(0x130) = 0;
    CW(0x138) = 0;
    CW(0x13C) = W(0x100);
    CW(0x140) = t0;
    CW(0x134) = t2;
    CW(0x144) = t3;
    CW(0x148) = t4;
    CW(0x14C) = 0;
    CW(0x150) = 0;
    CW(0x154) = (int)(e + 0x150);
    arg = c;
    return CreateScriptLwsOri(heap, 0, arg);
}
#endif
