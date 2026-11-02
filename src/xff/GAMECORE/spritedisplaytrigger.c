typedef struct {
    char pad0[0x168];
    float time;
} GlobalVar;

typedef struct {
    char pad0[0x30];
    float alpha;
    float start;
    char pad38[4];
    float fadeIn;
    float hold;
    float fadeOut;
    char pad48[0xC];
    void (*draw)(int);
} SpriteClass;

typedef struct {
    int *done;
    int pad4;
    float *delay;
} SpriteTrigger;

extern GlobalVar gcGlobalVar;
extern int isysGetThisSubThread(void);
extern SpriteClass *GetSpriteClass(int);
extern void scrRun(void);
extern void iosFree(void *);

void spritedisplaytrigger(SpriteTrigger *arg)
{
    int th = isysGetThisSubThread();
    SpriteClass *sp = GetSpriteClass(th);
    float t0 = gcGlobalVar.time;
    float t;

    do {
        scrRun();
    } while (!(gcGlobalVar.time - t0 >= *arg->delay));
    sp->start = gcGlobalVar.time;
    while (1) {
        t = gcGlobalVar.time - sp->start;
        if (t <= sp->fadeIn)
            sp->alpha = 1.0f - (sp->fadeIn - t) / sp->fadeIn;
        else if (t <= sp->hold)
            sp->alpha = 1.0f;
        else if (t <= sp->fadeOut)
            sp->alpha = (sp->fadeOut - t) / (sp->fadeOut - sp->hold);
        else
            break;
        sp->draw(th);
        scrRun();
    }
    if (arg->done != 0)
        *arg->done = 1;
    iosFree(arg);
}
