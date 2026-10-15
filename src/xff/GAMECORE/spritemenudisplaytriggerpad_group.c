extern void *isysGetThisSubThread(void);
extern void GetSpriteMenuClass(void *);
extern volatile int D_0017AFDC;
extern void scrRun(void);

void spritemenudisplaytriggerpad_group(void)
{
    GetSpriteMenuClass(isysGetThisSubThread());
    D_0017AFDC++;
    for (;;)
        scrRun();
}
