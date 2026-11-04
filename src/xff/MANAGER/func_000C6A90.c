typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; int i[4]; } Vec4;
typedef struct { float u, v; int a, b; } __attribute__((aligned(8))) UV;
typedef struct {
    Vec4 pos;
    Vec4 color;
    char pad20[0x10];
    Vec4 dir;
    float w;
    char pad44[0xC];
} Sprite;
extern float UnitMatrix[];
extern void glLoadMatrixf(float *);
extern void func_000C6DF0(char *, char *, char *);
extern float func_000C6DA0(char *);
extern void func_000C6EB8(void);
extern void func_000C70C0(Sprite *, UV *, char *);

static inline void clampColor(Vec4 *v)
{
    __asm__ __volatile__("lqc2 vf7, 0x0(%0)\n"
                         "vminiw.xyzw vf7, vf7, vf0w\n"
                         "vmaxx.xyzw vf7, vf7, vf0x\n"
                         "sqc2 vf7, 0x0(%0)\n"
                         : : "r"(v) : "memory");
}

static void func_000C6A90(char *e, char *b, char *c, char *d)
{
    UV uv;
    char *n;
    int i;

    uv = (UV){ *(float *)(c + 0x58), *(float *)(c + 0x5C), 0, 0 };
    n = *(char **)(e + 0x128);
    func_000C6DF0(e, b, c);
    glLoadMatrixf(UnitMatrix);
    for (i = 0; i < *(int *)(e + 0x124); i++) {
        if (*(float *)(n + 0x40) != 0.0f) {
            Sprite s;

            s.pos.q = ((Vec4 *)n)->q;
            s.pos.f[3] = *(float *)(e + 0x144) * *(float *)(n + 0x4C);
            s.color.f[0] = *(float *)(e + 0x70) * *(float *)(n + 0x68);
            s.color.f[1] = *(float *)(e + 0x74) * *(float *)(n + 0x70);
            s.color.f[2] = *(float *)(e + 0x78) * *(float *)(n + 0x78);
            s.color.f[3] = *(float *)(e + 0x140) * *(float *)(n + 0x54) * func_000C6DA0(n);
            clampColor(&s.color);
            s.dir.q = ((Vec4 *)(n + 0x30))->q;
            s.w = *(float *)(n + 0x98);
            func_000C70C0(&s, &uv, d);
        }
        n = *(char **)(n + 0xA8);
    }
    func_000C6EB8();
}
