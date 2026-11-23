/* Draws the two direction-arrow sprites (ptn at +0x6C and +0x68) rotated to
 * the player's facing. 3.14159251f spells 0x40490FDA under gcc 2.96. */

typedef struct { float x, y, z, w; } Vec4;

extern void *getSeamlessStageEnv(void);
extern char *GetCharacterClass(int);
extern void GetCharacterClassControlFrontDirection(Vec4 *, void *);
extern float iosGetATan2fExact(float, float);
extern char rootPtn[];
extern void *spriteCreateObject(char *, int);
extern void spriteSetColor(void *, int, int, int, int);
extern void spriteSetScale(void *, float, float);
extern void spriteSetBlendMode(void *, int, int, int);
extern void spriteSetPosition(void *, float, float);
extern void spriteSetRotation(void *, float);
extern void spriteDrawSprite(void *, int, float, float, float, float, float, float, int, int);
extern void spriteDeleteObject(void *);

#define W(type, o) (*(type *)(menu + (o)))

static inline void draw(char *menu, int ptn, int pri, float x, float y, float ang)
{
    void *spr = spriteCreateObject(rootPtn, ptn);
    spriteSetColor(spr, 0x80, 0x80, 0x80, 0x80);
    spriteSetScale(spr, 1.0f, 1.0f);
    spriteSetBlendMode(spr, 1, 0, 1);
    spriteSetPosition(spr, x, y);
    spriteSetRotation(spr, ang);
    spriteDrawSprite(spr, 0xFFFFFF, W(float, 0x48) + W(float, 0x50), W(float, 0x4C) + W(float, 0x54), 1.0f, 1.0f, 0.0f, W(float, 0x14), pri, -1);
    spriteDeleteObject(spr);
}

static void func_000CE878(char *menu)
{
    char *env;
    char *cls;
    Vec4 dir;
    float ang, x, y;
    int pri;
    int k;

    env = getSeamlessStageEnv();
    if (env == 0)
        return;
    if (W(int, 0x58) == -1)
        return;
    if (*(int *)(env + 0x24) == 0)
        return;
    cls = GetCharacterClass(*(int *)(env + 0x24));
    if (cls == 0)
        return;
    GetCharacterClassControlFrontDirection(&dir, cls);
    ang = iosGetATan2fExact(-dir.x, dir.z) + 3.14159251f;
    x = W(float, 0x34) * W(float, 0x18);
    y = (W(float, 0x3C) + W(float, 0x38) * -0.067f) * W(float, 0x18);
    pri = W(int, 0x58) - 0x18;
    if (W(int, 0x6C) != 0)
        draw(menu, W(int, 0x6C), pri, x, y, ang);
    pri = (k = W(int, 0x58) - 0x18);
    if (W(int, 0x68) != 0)
        draw(menu, W(int, 0x68), pri, x, y, ang);
}
