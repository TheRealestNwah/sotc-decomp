/* Parked draft: boss-status map markers. For every boss whose game flag is clear it projects the
   boss position to the compass/map plane (/ 600, * zoom * 0.1, y * -0.067, * 0.857) and draws one
   sprite with a texture-coordinate cell picked from the boss number (4 x 4 atlas, cell size 0.25 + 0.01
   inset). Sibling of func_000CEAE0 / func_000CE620. Written from the m2c draft; not yet compared
   closely. */
#ifdef NONMATCHING
extern int DldSysUndefSymbol;
extern int SH_BossStatusDEFAULT[];
extern char rootPtn[];
extern int _gameFlagChk(int);
extern void *memset(void *, int, unsigned int);
extern void *spriteCreateObject(char *, int, int);
extern void spriteDeleteObject(void *);
extern void spriteDrawSprite(void *, int, int, int, float, float, float, float, float, float);
extern void spriteSetBlendMode(void *, int, int, int);
extern void spriteSetColor(void *, int, int, int);
extern void spriteSetPosition(void *, float, float);
extern void spriteSetRotation(void *, float);
extern void spriteSetScale(void *, float, float);
extern void spriteSetTextureCoordinateST(void *, float, float, float, float);

static void func_000CED18(char *map)
{
    int *sh = DldSysUndefSymbol != (int)SH_BossStatusDEFAULT ? SH_BossStatusDEFAULT : 0;
    int count = sh[3];
    char *b;
    int i;

    if (count > 0) {
        b = (char *)sh[4];
        for (i = 0; i < count; i++, b += 0xEC) {
            if (_gameFlagChk(*(int *)(b + 0x18)) == 0) {
                float v[4] __attribute__((aligned(16)));
                float zoom;
                int tex;
                int image;
                int cell;
                float col;
                float row;
                float x;
                float z;

                memset(v, 0, 0x10);
                v[0] = *(float *)(b + 0x44);
                v[1] = *(float *)(b + 0x48);
                v[2] = *(float *)(b + 0x4C);
                zoom = *(float *)(map + 0x18);
                tex = *(int *)(map + 0x58) - 0x18;
                image = *(int *)(map + 0x70);
                cell = *(int *)(b + 0x14) - 1;
                row = (float)((cell < 0 ? cell + 3 : cell) >> 2);
                col = (float)(cell - (((cell < 0 ? cell + 3 : cell) >> 2) * 4));
                v[1] = v[1] * -0.067f;
                x = (v[0] / 600.0f) * *(float *)(map + 0x40) * 0.1f * zoom;
                z = -(((v[2] / 600.0f) * *(float *)(map + 0x40) * 0.1f) + v[1]) * zoom * 0.857142f;
                if (image != 0) {
                    void *s = spriteCreateObject(rootPtn, image, image);
                    float half = zoom * 0.25f;

                    spriteSetColor(s, 0x80, 0x80, 0x80);
                    spriteSetScale(s, half, half);
                    spriteSetBlendMode(s, 1, 0, 1);
                    spriteSetTextureCoordinateST(s, col * 0.25f + 0.01f, row * 0.25f + 0.01f, 0.23f, 0.23f);
                    spriteSetPosition(s, x, z);
                    spriteSetRotation(s, 0.0f);
                    spriteDrawSprite(s, 0xFFFFFF, tex, -1,
                                     *(float *)(map + 0x48) + *(float *)(map + 0x50),
                                     *(float *)(map + 0x4C) + *(float *)(map + 0x54),
                                     1.0f, 1.0f, 0.0f, *(float *)(map + 0x14));
                    spriteDeleteObject(s);
                }
            }
        }
    }
}
#endif
