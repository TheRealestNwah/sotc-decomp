/* Parked draft: projects a world-space offset into the compass/sprite plane and draws one
   128x128-colour sprite there (create, colour, scale, blend, position, rotation, draw, delete).
   The three-float vector goes through a 16-byte copy; constants: 600.0 divisor, -0.0672 pitch
   factor, 0.1, 0.857. Continues in func_000CE5E8 (spriteDeleteObject and epilogue). */
#ifdef NONMATCHING
typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;

extern char rootPtn[];
extern void *spriteCreateObject(char *);
extern void spriteSetColor(void *, int, int, int, int);
extern void spriteSetScale(void *, float, float);
extern void spriteSetBlendMode(void *, int, int, int);
extern void spriteSetPosition(void *, float, float);
extern void spriteSetRotation(void *, float);
extern void spriteDrawSprite(void *, int, int, int, float, float, float, float, float, float);
extern void spriteDeleteObject(void *, int);

static void func_000CE428(float *v, char *obj)
{
    Vec4 a __attribute__((aligned(16)));
    Vec4 b __attribute__((aligned(16)));
    float scale = *(float *)(obj + 0x18);
    float f0;
    float f1;
    float f2;
    float x;
    float z;
    int tex;
    void *sprite;
    int data;

    a.f[0] = -v[0];
    a.f[1] = v[1];
    a.f[2] = -v[2];
    a.f[3] = 1.0f;
    b = a;
    f0 = b.f[2] / 600.0f;
    f1 = b.f[0] / 600.0f;
    f2 = b.f[1] * -0.067f;
    b.f[1] = f2;
    tex = *(int *)(obj + 0x58) - 0x18;
    data = *(int *)(obj + 0x74);
    b.f[0] = ((f1 * *(float *)(obj + 0x40)) * 0.1f) * scale;
    b.f[2] = (-((f0 * *(float *)(obj + 0x40)) * 0.1f + f2) * scale) * 0.857142866f;
    x = b.f[0];
    z = b.f[2];
    if (data != 0) {
        sprite = spriteCreateObject(rootPtn);
        spriteSetColor(sprite, 0x80, 0x80, 0x80, 0x80);
        spriteSetScale(sprite, scale, scale);
        spriteSetBlendMode(sprite, 1, 0, 1);
        spriteSetPosition(sprite, x, z);
        spriteSetRotation(sprite, 0.0f);
        spriteDrawSprite(sprite, 0xFFFFFF, tex, -1,
                         *(float *)(obj + 0x48) + *(float *)(obj + 0x50),
                         *(float *)(obj + 0x4C) + *(float *)(obj + 0x54), 1.0f, 1.0f,
                         0.0f, *(float *)(obj + 0x14));
        spriteDeleteObject(sprite, -1);
    }
}
#endif
