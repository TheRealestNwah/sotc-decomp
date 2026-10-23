typedef union {
    struct {
        int f0;
        int f4;
        float f8;
        float fC;
        char pad10[8];
        int f18;
        float f1C;
        int f20;
        int f24;
        float f28;
        float f2C;
        char table[1];
    } s;
    char alias;
} AnimationClass;

typedef struct {
    int pad;
    short frames;
} AnimResource;

extern void ResetAnimeFrameTableInfo(void *, int, int);

int SetAnimationClassLastInfoDirectResource(AnimationClass *anim, AnimResource *res)
{
    float last = res->frames - 1;

    anim->s.f0 = 0;
    anim->s.f4 = 0;
    anim->s.f8 = last;
    anim->s.fC = last;
    anim->s.f18 = 0;
    anim->s.f1C = 1.0f;
    anim->s.f20 = 0;
    anim->s.f24 = 0;
    anim->s.f28 = 1.0f;
    anim->s.f2C = 1.0f;
    ResetAnimeFrameTableInfo(anim->s.table, 0, 0);
    return 1;
}
