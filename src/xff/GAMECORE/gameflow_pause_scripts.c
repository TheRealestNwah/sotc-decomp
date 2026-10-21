extern int isysGetThisSubThread(void);
extern void scrInit(int);
extern int PauseGame(int);
extern void ReleaseGame(int);

static void func_000186A8(void)
{
    scrInit(isysGetThisSubThread());
    PauseGame(1);
}
static void T_000186D0(void)
{
    scrInit(isysGetThisSubThread());
    ReleaseGame(1);
}
static void T_000186F8(void)
{
    scrInit(isysGetThisSubThread());
    PauseGame(1);
}
static void T_00018720(void)
{
    scrInit(isysGetThisSubThread());
    ReleaseGame(1);
}