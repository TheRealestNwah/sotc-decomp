typedef struct {
    char *mot;
    int a;
    float b;
    float c;
    int pad10;
    int pad14;
    int d;
    float e;
    int f;
    int g;
    union { float f; int i; } ratio;
    union { float f; int i; } inv;
} AnimClass;

typedef struct {
    float f0;
    float f4;
    float f8;
    float fC;
    float f10;
    float f14;
    float f18;
} MotShift;

extern void *DldSysUndefSymbol;
extern int GetMotionResourceFrames(void *);
extern float GetMotionStretchRatio(void *);

static inline void *dldEntry(unsigned int *ref)
{
    unsigned int enc = *ref;
    unsigned int off = enc & 0x3FFFF;
    char *mod;

    if (off != 0)
        mod = *(char **)((char *)ref - off);
    else
        mod = 0;
    if (mod != 0 && mod != DldSysUndefSymbol)
        return *(char **)(mod + 0x10) + ((enc >> 18) & 0xFFF) * *(int *)(*(char **)(mod + 8) + 0xC);
    return 0;
}

static inline MotShift *getShift(char *mot)
{
    if (mot != 0)
        return (MotShift *)dldEntry((unsigned int *)(mot + 0x60));
    return 0;
}

void *ForceAcceptMotion(char *chara, char *mot, float frame)
{
    AnimClass *anim = (AnimClass *)(chara + 0x1C0);
    char *res;
    MotShift *sh;

    anim->mot = mot;
    if (mot != 0) {
        int frames;
        float ratio;
        float f;

        res = mot + 0x50;
        frames = GetMotionResourceFrames(res);
        ratio = GetMotionStretchRatio(res);
        f = frame * ratio;
        anim->ratio.f = ratio;
        anim->inv.f = 1.0f / ratio;
        if ((float)frames <= f)
            *(float *)(chara + 0x720) = (float)frames;
        else
            *(float *)(chara + 0x720) = f;
        if (*(float *)(*(char **)(chara + 0x1140) + 0x138) == 0.0f)
            *(float *)(chara + 0x740) = f;
    } else {
        *(float *)(chara + 0x720) = 0.0f;
        anim->ratio.f = 1.0f;
        anim->inv.f = 1.0f;
        if (*(float *)(*(char **)(chara + 0x1140) + 0x138) == 0.0f)
            *(float *)(chara + 0x740) = 0.0f;
        res = mot + 0x50;
    }
    *(int *)(chara + 0x73C) = 0;
    sh = getShift(mot);
    if (sh != 0) {
        *(char *)(chara + 0x5E2) = 1;
        *(float *)(chara + 0x5C4) = sh->fC;
        *(float *)(chara + 0x5C8) = sh->f0;
        *(float *)(chara + 0x5CC) = sh->f10;
        *(float *)(chara + 0x5D0) = sh->f14;
        *(float *)(chara + 0x5D4) = sh->f18;
        *(float *)(chara + 0x5C0) = anim->e;
        *(float *)(chara + 0x5D8) = sh->f8;
        *(float *)(chara + 0x5DC) = sh->f4;
        *(char *)(chara + 0x5E0) = 0;
        *(char *)(chara + 0x5E1) = 0;
    } else {
        *(char *)(chara + 0x5E2) = 0;
    }
    anim->e = 1.0f;
    return res;
}
