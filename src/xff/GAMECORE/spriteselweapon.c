typedef struct { int a; int *run; int mode; int c; } SpriteParam;
typedef struct { float a; float b; float c; int state; } DispSw;

extern void *isysGetThisSubThread(void);
extern char *GetSpriteClass(void *);
extern void ScrSpriteParamSetup(SpriteParam *, void *);
extern void func_000BFAE0(char *);
extern float getDemoBarFade(void);
extern float getFadeValue(void);
extern int getDrawScreenHeight(void);
extern void scrRun(void);
extern DispSw B_0019CCD0[];
extern int D_0017AFEC;
extern int D_0017AFE8;

void spriteselweapon(void *arg)
{
    SpriteParam p;
    void *t = isysGetThisSubThread();
    char *spr = GetSpriteClass(t);

    ScrSpriteParamSetup(&p, arg);
    while (*p.run != 0) {
        func_000BFAE0(spr);
        *(float *)(spr + 0x30) = B_0019CCD0[2].b;
        if (((getDemoBarFade() == 1.0f && getFadeValue() == 0.0f) || D_0017AFEC != 0) && D_0017AFE8 != 0) {
            *(float *)(spr + 0x18) = -((0x1C0 - getDrawScreenHeight()) >> 1);
            (*(void (**)(void *))(spr + 0x54))(t);
        }
        scrRun();
    }
}
