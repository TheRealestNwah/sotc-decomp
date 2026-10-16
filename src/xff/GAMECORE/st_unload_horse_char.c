extern void *isysGetThisSubThread(void);
extern void gStatUnloadHorseChara(void);
extern void isysRequestDeleteObj(void *);

void st_unload_horse_char(void)
{
    void *t = isysGetThisSubThread();

    gStatUnloadHorseChara();
    isysRequestDeleteObj(t);
}
