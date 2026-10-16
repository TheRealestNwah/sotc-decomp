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
    float ratio;
    float inv;
    char table[1];
} AnimClass;

extern float GetMotionStretchRatio(void *);
extern void ResetAnimeFrameTableInfo(void *, int, int);

static inline float stretchRatio(char *mot)
{
    if (mot != 0)
        return GetMotionStretchRatio(mot + 0x50);
    return 1.0f;
}

void InitAnimationClass(AnimClass *a, char *mot)
{
    float ratio;

    a->mot = mot;
    a->a = 0;
    *(int *)&a->b = 0;
    *(int *)&a->c = 0;
    a->d = 0;
    a->e = 1.0f;
    a->f = 0;
    a->g = 0;
    ratio = stretchRatio(mot);
    a->ratio = ratio;
    a->inv = 1.0f / ratio;
    ResetAnimeFrameTableInfo(a->table, 0, 0);
}
