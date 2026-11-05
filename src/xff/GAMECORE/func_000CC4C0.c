typedef struct {
    int a;
    float b;
    float cur;
    int d;
    void *tex;
    int f;
} TexAnim;

extern char *GetSCRCharaAIWorkPtr(void *);
extern float getBossPartsLifeRatio(void *, int);
extern void bootTexAlphaAnim(void *, void *, float, float);
extern TexAnim D_0017B288;
extern TexAnim D_0017B2A0;
extern TexAnim D_0017B2B8;
extern TexAnim D_0017B2D0;
extern TexAnim D_0017B2E8;
extern TexAnim D_0017B300;

#define FADE -0.05f

static void func_000CC4C0(void *chr)
{
    char *w = GetSCRCharaAIWorkPtr(chr);
    float r;

    if (*(int *)(w + 0x5A98) == 0) {
        r = getBossPartsLifeRatio(chr, 0x10);
        if (r == 0.0f) {
            *(int *)(w + 0x5A98) = 1;
        } else {
            r = r * 0.5f + 0.5f;
        }
        if (D_0017B288.cur != r) bootTexAlphaAnim(chr, &D_0017B288, r, FADE);
        if (D_0017B2A0.cur != r) bootTexAlphaAnim(chr, &D_0017B2A0, r, FADE);
    }
    if (*(int *)(w + 0x5A9C) == 0) {
        r = getBossPartsLifeRatio(chr, 0x30);
        if (r == 0.0f) {
            *(int *)(w + 0x5A9C) = 1;
        } else {
            r = r * 0.5f + 0.5f;
        }
        if (D_0017B2B8.cur != r) bootTexAlphaAnim(chr, &D_0017B2B8, r, FADE);
        if (D_0017B2D0.cur != r) bootTexAlphaAnim(chr, &D_0017B2D0, r, FADE);
    }
    if (*(int *)(w + 0x5AA0) == 0) {
        r = getBossPartsLifeRatio(chr, 0x40);
        if (r == 0.0f) {
            *(int *)(w + 0x5AA0) = 1;
        } else {
            r = r * 0.5f + 0.5f;
        }
        if (D_0017B2E8.cur != r) bootTexAlphaAnim(chr, &D_0017B2E8, r, FADE);
        if (D_0017B300.cur != r) bootTexAlphaAnim(chr, &D_0017B300, r, FADE);
    }
}
