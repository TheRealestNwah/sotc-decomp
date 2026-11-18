typedef struct {
    char pad[0x68];
    unsigned int pad0 : 5;
    unsigned int b5 : 1;
    unsigned int b6 : 1;
    unsigned int b7 : 1;
    unsigned int b8 : 1;
    unsigned int b9 : 1;
    unsigned int b10 : 1;
    unsigned int pad11 : 1;
    unsigned int b12 : 1;
    unsigned int pad13 : 1;
    unsigned int b14 : 1;
    unsigned int pad15 : 1;
    unsigned int b16 : 1;
} CollAttr;

typedef struct {
    int f0;
    int f4;
    int f8;
    int fC;
    int f10;
    int f14;
    int f18;
    int f1C;
    int f20;
    float f24;
    float f28;
    int pad2C;
    float v30[4];
} CollFilter;

static int func_00058F50();
extern unsigned long *GetCollisionDBAttributeAdr(void *);
extern float *GetCollisionDBPlane(void *);
extern int GetCollisionDBCallBack(void *, void *, void *, void *, void *, int, int, int (*)(), CollFilter *);

int charrootdyn_getCollisionDBwithFunc(void *a0, void *a1, void *a2, void *a3, CollAttr *attr, void *arg, CollFilter *f)
{
    int all;

    if (attr != 0) {
        f->fC = attr->b10;
        f->f18 = attr->b12;
        f->f1C = attr->b14;
        f->f20 = attr->b16;
        f->f0 = attr->b5;
        f->f4 = attr->b6;
        f->f8 = attr->b7;
        f->f10 = attr->b8;
        f->f14 = attr->b9;
    } else {
        f->f1C = 0;
        f->f20 = 1;
        f->f18 = 0;
        f->f14 = 0;
        f->f10 = 0;
        f->fC = 0;
        f->f8 = 0;
        f->f4 = 0;
        f->f0 = 0;
    }
    all = f->f0 && f->f4 && f->f8 && f->fC && f->f10 && f->f14 && f->f18 && f->f1C;
    return GetCollisionDBCallBack(a0, a1, a2, a3, arg, 0, 0, all ? 0 : func_00058F50, f);
}

static inline float dot3(float *a, float *b)
{
    float r;
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vaddw.x vf7, vf0, vf0w\n"
                         "vmul.xyz vf6, vf5, vf6\n"
                         "vaddax.x ACC, vf0, vf6x\n"
                         "vmadday.x ACC, vf7, vf6y\n"
                         "vmaddz.x vf6, vf7, vf6z\n"
                         "qmfc2.ni $2, vf6\n"
                         "mtc1 $2, %0\n"
                         : "=f"(r) : "r"(a), "r"(b) : "$2");
    return r;
}

#define KIND(n) ((unsigned long)(n) << 31)
#define SUB(n) ((n) << 26)

static int func_00058F50(void *col, CollFilter *f)
{
    unsigned long attr = *GetCollisionDBAttributeAdr(col);
    unsigned long t = attr & KIND(0x1F);
    unsigned long k;

    if (t == KIND(6) || t == KIND(10) || t == KIND(5)) {
        return 0;
    }
    k = attr & SUB(0x1F);
    if (!f->f0 && k == SUB(12)) {
        return 0;
    }
    if (!f->f4 && k == SUB(13)) {
        return 0;
    }
    if (k == SUB(27)) {
        return 0;
    }
    if (!f->f8 && k == SUB(9)) {
        return 0;
    }
    if (!f->fC && (t == KIND(4) || t == KIND(23))) {
        return 0;
    }
    if (!f->f18 && k == SUB(1)) {
        return 0;
    }
    if (!f->f1C && k == SUB(18)) {
        return 0;
    }
    if (k == SUB(25)) {
        if (!f->f10 || f->f24 < GetCollisionDBPlane(col)[1]) {
            return 0;
        }
    }
    if (k == SUB(26)) {
        if (!f->f14 || f->f28 < -dot3(GetCollisionDBPlane(col), f->v30)) {
            return 0;
        }
    }
    if (k == SUB(15) && !f->f20) {
        return 0;
    }
    return (attr & ((unsigned long)0xF << 42)) != ((unsigned long)2 << 42);
}
