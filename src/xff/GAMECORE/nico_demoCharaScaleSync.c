typedef int s128 __attribute__((mode(TI)));
extern void *isysGetThisSubThread(void);
extern char *GetCharacterClass(void *);
extern void func_000421F8(void *, s128 *);
extern void scrRun(void);

void nico_demoCharaScaleSync(void)
{
    char *c = GetCharacterClass(isysGetThisSubThread());
    s128 s = *(s128 *)(c + 0x90);
    for (;;) {
        func_000421F8(c, &s);
        scrRun();
    }
}
