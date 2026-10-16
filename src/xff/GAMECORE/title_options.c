extern int *GetSpriteMenuClass(void *);
extern void PauseGame(int);
extern void ReleaseGame(int);
extern void OptionMenuStart(int *, int *);
extern int SpriteMenuGetSelectLayer(void *);
extern void func_000C95C0(float);
extern void scrRun(void);

void title_options(void *m)
{
    int *s = GetSpriteMenuClass(m);
    int done;
    int r;

    PauseGame(1);
    done = 0;
    r = 0;
    OptionMenuStart(&done, &r);
    while (done == 0) {
        func_000C95C0(*(float *)((char *)s[1] + SpriteMenuGetSelectLayer(m) * 0x44 + 0xC));
        ((void (*)(void *))s[11])(m);
        scrRun();
    }
    ReleaseGame(1);
}
