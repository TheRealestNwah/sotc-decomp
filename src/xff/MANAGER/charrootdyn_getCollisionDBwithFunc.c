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
} CollFilter;

static int func_00058F50();
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
