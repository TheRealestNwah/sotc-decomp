typedef struct { char c[16]; } SpriteParam;

extern void *isysGetThisSubThread(void);
extern char *GetSpriteMenuClass(unsigned char *);
extern void ScrSpriteParamSetup(SpriteParam *, SpriteParam *);
extern void SpriteMenuSetDispFlagAll(unsigned char *, int);
extern int sheetFsLanguageCode;
extern int D_0017A99C;

void chooseLangScript(SpriteParam *parameters)
{
    SpriteParam local;
    int language;
    void *thread;

    thread = isysGetThisSubThread();
    GetSpriteMenuClass(thread);
    language = 1;
    ScrSpriteParamSetup(&local, parameters);
    SpriteMenuSetDispFlagAll(thread, 0);
    sheetFsLanguageCode = language;
    D_0017A99C = language;
}
