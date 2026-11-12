/* Parked draft: boss-status map markers. For every boss whose game flag is clear it projects the
   boss position to the compass/map plane (/ 600, * zoom * 0.1, y * -0.067, * 0.857) and draws one
   sprite with a texture-coordinate cell picked from the boss number (4 x 4 atlas, cell size 0.25 + 0.01
   inset). Sibling of func_000CEAE0 / func_000CE620. ~176 diffs (was ~185): restructured with the
   CE620 tricks (V4h ld/sd temp, in-loop float locals, do-while). Remaining: the V4h temp gets its own
   stack slot (0x20) instead of sharing vv's 0x10, an extra callee-saved float, and the cell/4 divide
   and tex/image loads are scheduled differently. A union-shared temp scored 177. */
#ifdef NONMATCHING
extern int *DldSysUndefSymbol;
extern int SH_BossStatusDEFAULT[];
extern char rootPtn[];
extern int _gameFlagChk(int);
extern void *memset(void *, int, unsigned int);
extern void *spriteCreateObject(char *, int, int);
extern void spriteDeleteObject(void *);
extern void spriteDrawSprite(void *, int, int, int, float, float, float, float, float, float);
extern void spriteSetBlendMode(void *, int, int, int);
extern void spriteSetColor(void *, int, int, int, int);
extern void spriteSetPosition(void *, float, float);
extern void spriteSetRotation(void *, float);
extern void spriteSetScale(void *, float, float);
extern void spriteSetTextureCoordinateST(void *, float, float, float, float);

typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;
typedef struct { float x, y, z, w; } V4h __attribute__((aligned(8)));

static void func_000CED18(char *map)
{
    int *sh = DldSysUndefSymbol != SH_BossStatusDEFAULT ? SH_BossStatusDEFAULT : 0;
    int count = sh[3];
    char *b;
    int i;

    if (count > 0) {
        b = (char *)sh[4];
        i = count;
        do {
            if (_gameFlagChk(*(int *)(b + 0x18)) == 0) {
                Vec4 tmp;
                Vec4 vv;
                float zoom;
                int tex;
                int image;
                int cell;
                int q;
                float col;
                float row;
                float x;
                float z;
                float zero = 0.0f;
                float one = 1.0f;
                float quarter = 0.25f;
                float inner = 0.23f;

                {
                    V4h t;
                    memset(&t, 0, 0x10);
                    t.x = *(float *)(b + 0x44);
                    t.y = *(float *)(b + 0x48);
                    t.z = *(float *)(b + 0x4C);
                    *(V4h *)&tmp = t;
                }
                vv.q = tmp.q;
                zoom = *(float *)(map + 0x18);
                tex = *(int *)(map + 0x58) - 0x18;
                image = *(int *)(map + 0x70);
                cell = *(int *)(b + 0x14) - 1;
                q = cell / 4;
                row = (float)q;
                col = (float)(cell - q * 4);
                vv.f[1] = vv.f[1] * -0.067f;
                x = (vv.f[0] / 600.0f) * *(float *)(map + 0x40) * 0.1f * zoom;
                z = -(((vv.f[2] / 600.0f) * *(float *)(map + 0x40) * 0.1f) + vv.f[1]) * zoom * 0.857142866f;
                if (image != 0) {
                    void *s = spriteCreateObject(rootPtn, image, image);
                    float half = zoom * quarter;

                    spriteSetColor(s, 0x80, 0x80, 0x80, 0x80);
                    spriteSetScale(s, half, half);
                    spriteSetBlendMode(s, 1, 0, 1);
                    spriteSetTextureCoordinateST(s, col * quarter + 0.01f, row * quarter + 0.01f, inner, inner);
                    spriteSetPosition(s, x, z);
                    spriteSetRotation(s, zero);
                    spriteDrawSprite(s, 0xFFFFFF, tex, -1,
                                     *(float *)(map + 0x48) + *(float *)(map + 0x50),
                                     *(float *)(map + 0x4C) + *(float *)(map + 0x54),
                                     one, one, zero, *(float *)(map + 0x14));
                    spriteDeleteObject(s);
                }
            }
            b += 0xEC;
        } while (--i);
    }
}
#endif
