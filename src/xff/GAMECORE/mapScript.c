typedef struct { int a, b, mode, c; } SpriteParam;
extern void *isysGetThisSubThread(void);
extern void ScrSpriteParamSetup(SpriteParam *, void *);
extern void PauseSeamlessStageManager(int);
extern void func_000CFA70(void *);
extern void func_000D0CC0(void *, SpriteParam *);
extern void ScrSpriteParamEnd(SpriteParam *, int);

void mapScript(void *a)
{
    SpriteParam p;
    void *t = isysGetThisSubThread();
    ScrSpriteParamSetup(&p, a);
    if (p.mode == 0) {
        PauseSeamlessStageManager(1);
        func_000CFA70(t);
        PauseSeamlessStageManager(0);
    } else {
        func_000D0CC0(t, &p);
    }
    ScrSpriteParamEnd(&p, 1);
}
