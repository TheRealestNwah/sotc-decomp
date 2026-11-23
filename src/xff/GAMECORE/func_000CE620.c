/* Save-point map icons. For every save point whose flag is set it
   converts the point's world position (plus the seamless-area centre) to the map plane with
   getPosOnMap and draws one icon sprite there, scaled by the map zoom.
   The list pointer is loaded before the count; the SH ternary keeps the Undef test as written. */
typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;

extern int *DldSysUndefSymbol;
extern int SH_SavePointDEFAULT[];
extern char rootPtn[];
extern void YattsukeGetSeamlessAreaCenter(Vec4 *, int);
extern int _gameFlagChk(int);
extern void getPosOnMap(Vec4 *, float *, float *);
extern void *spriteCreateObject(char *, int);
extern void spriteDeleteObject(void *);
extern void spriteDrawSprite(void *, int, float, float, float, float, float, float, int, int);
extern void spriteSetBlendMode(void *, int, int, int);
extern void spriteSetColor(void *, int, int, int, int);
extern void spriteSetPosition(void *, float, float);
extern void spriteSetRotation(void *, float);
extern void spriteSetScale(void *, float, float);

static inline void addXYZ(Vec4 *out, Vec4 *a, Vec4 *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vadd.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}

typedef struct { float x, y, z, w; } V4h __attribute__((aligned(8)));

static void func_000CE620(char *map)
{
    int *sh = DldSysUndefSymbol != SH_SavePointDEFAULT ? SH_SavePointDEFAULT : 0;
    char *list = (char *)sh[4];
    int count = sh[3];
    char *p;
    int i;

    if (count > 0) {
        p = list;
        i = count;
        do {
            if (p[3] != 0 && _gameFlagChk(*(int *)(p + 4)) != 0) {
                Vec4 area __attribute__((aligned(16)));
                Vec4 pos __attribute__((aligned(16)));
                float mx;
                float my;
                float scale;
                float x;
                float y;
                int tex;
                int image;
                float zero = 0.0f;

                {
                    V4h t;
                    t.x = -*(float *)(p + 8);
                    t.y = *(float *)(p + 0xC);
                    t.z = -*(float *)(p + 0x10);
                    t.w = 1.0f;
                    *(V4h *)&pos = t;
                }
                YattsukeGetSeamlessAreaCenter(&area, p[0]);
                addXYZ(&pos, &pos, &area);
                getPosOnMap(&pos, &mx, &my);
                scale = *(float *)(map + 0x18);
                tex = *(int *)(map + 0x58) - 0x18;
                image = *(int *)(map + 0x64);
                x = mx * *(float *)(map + 0x40) * 0.1f * scale;
                y = ((-my * *(float *)(map + 0x44) * 0.1f) + (pos.f[1] * -0.067f)) * scale;
                if (image != 0) {
                    void *s = spriteCreateObject(rootPtn, image);
                    spriteSetColor(s, 0x80, 0x80, 0x80, 0x80);
                    spriteSetScale(s, scale, scale);
                    spriteSetBlendMode(s, 1, 0, 1);
                    spriteSetPosition(s, x, y);
                    spriteSetRotation(s, zero);
                    spriteDrawSprite(s, 0xFFFFFF, *(float *)(map + 0x48) + *(float *)(map + 0x50), *(float *)(map + 0x4C) + *(float *)(map + 0x54), 1.0f, 1.0f, 0.0f, *(float *)(map + 0x14), tex, -1);
                    spriteDeleteObject(s);
                }
            }
            p += 0x44;
        } while (--i);
    }
}

