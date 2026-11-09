#ifdef NONMATCHING
/* ~60 words off: original keeps source order for the quad copies and copies the by-value struct through a second stack slot. */
typedef int s128 __attribute__((mode(TI)));
typedef struct V16 {
    float x, y, z;
    int w;
} V16 __attribute__((aligned(8)));

typedef struct Cam {
    char pad0[0x3C];
    int f3C;
    char pad40[0xC];
    int f4C;
    char pad50[0x6C];
    float bc, c0, c4;
} Cam;

typedef struct Src {
    Cam *cam;
    char pad4[0x40];
    int *p44;
} Src;

typedef struct Out {
    int f0, f4, f8;
    char padC[4];
    s128 v10;
    s128 v20;
    s128 v30;
    s128 v40;
    int f50, f54;
    char pad58[8];
    s128 v60;
    s128 v70;
    int f80, f84, f88;
    float f8C;
} Out;

extern s128 ZeroPoint;
extern s128 ZeroVector;
extern void func_000E74B8(Out *, Src *);
extern void func_000E75F8(Out *, Src *, int);
extern void func_000E7688(void *, void *, Cam *, int, int, V16);

int get_camera_lws_animation_data(Out *o, Src *s, int a2, int a3, int a4, int a5, int a6)
{
    Cam *c;
    V16 v;

    o->f0 = -1;
    o->f4 = 0;
    o->f8 = -1;
    o->v10 = ZeroVector;
    o->v20 = ZeroVector;
    o->v30 = ZeroPoint;
    o->f54 = -1;
    o->v40 = ZeroPoint;
    o->f50 = 0;
    o->v60 = ZeroPoint;
    o->f8C = 1.0f;
    o->v70 = ZeroPoint;
    o->f80 = 0;
    o->f84 = 0;
    o->f88 = 0;
    c = s->cam;
    if (c == 0)
        return 0;
    v.x = c->bc;
    v.y = c->c0;
    v.w = 0;
    v.z = c->c4;
    o->f4 = a4;
    o->f50 = a6;
    o->f0 = *(s->p44 + 5) != 1;
    func_000E74B8(o, s);
    if (o->f0 == 1)
        func_000E75F8(o, s, a5);
    o->v20 = o->v10;
    func_000E7688(&o->v40, &o->v30, c, o->f4, c->f3C, v);
    func_000E7688(&o->v70, &o->v60, c, o->f50, c->f4C, v);
    return 1;
}
#else
extern int get_camera_lws_animation_data(void *, void *, int, int, int, int, int);
#endif
