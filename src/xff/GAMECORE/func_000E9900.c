extern void *get_camera_lws_animation_param(int);
extern int get_boot_obj_camera_lws_animation(int);
extern int CAM_get_parent_obj_by_base_space(int, void *, int, void *);
extern int *DldSysUndefSymbol;

typedef struct {
    char pad0[0x10];
    unsigned int f0 : 6;
    unsigned int b6 : 1;
    unsigned int b7 : 1;
    unsigned int b8 : 1;
    unsigned int b9 : 1;
    unsigned int b10 : 1;
    unsigned int rest : 21;
    char pad14[0xC];
    float f20, f24, f28, f2C, f30, f34, f38;
    char pad3C[0x10];
    int f4C;
    char f50[0x34];
    int f84;
    float f88;
    char pad8C[8];
    int f94;
    int f98;
    float f9C, fA0, fA4, fA8, fAC, fB0;
    unsigned int fB4;
    int fB8;
} LwsParam;

static inline char *dldResolve(unsigned int *h) { unsigned int v = *h; int off = v & 0x3FFFF;
    int *t = off != 0 ? *(int **)((char *)h - off) : 0;
    return (t != 0 && t != DldSysUndefSymbol) ? (char *)t[4] + ((v >> 18) & 0xFFF) * ((int *)t[2])[3] : 0; }

typedef union { int i; float f; char *p; } W;
typedef struct { char pad0[0x9C]; W w[0x19]; } CamWork;

#define I(o) (*(int *)(a + (o)))
#define F(o) (*(float *)(a + (o)))

static void func_000E9900(CamWork *a, int id, void *c)
{
    LwsParam *p = get_camera_lws_animation_param(id);

    a->w[0].i = p->b6;
    a->w[1].i = p->b7;
    a->w[2].f = p->f20;
    a->w[3].f = p->f24;
    a->w[4].f = p->f28;
    a->w[5].f = p->f2C;
    a->w[6].f = p->f30;
    a->w[7].i = p->b8;
    a->w[8].f = p->f34;
    a->w[9].f = p->f38;
    a->w[10].i = p->b9;
    a->w[11].i = p->b10;
    a->w[12].i = CAM_get_parent_obj_by_base_space(p->f4C, p->f50, get_boot_obj_camera_lws_animation(id), c);
    a->w[13].i = p->f84;
    a->w[14].f = p->f88;
    a->w[15].i = p->f94;
    a->w[16].i = p->f98;
    a->w[17].f = p->f9C;
    a->w[18].f = p->fA0;
    a->w[19].f = p->fA4;
    a->w[20].f = p->fA8;
    a->w[21].f = p->fAC;
    a->w[22].f = p->fB0;
    a->w[23].p = dldResolve(&p->fB4);
    a->w[24].i = p->fB8;
}
