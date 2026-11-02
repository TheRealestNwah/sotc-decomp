extern void *isysGetThisSubThread(void);
extern void CharaCtrlResetAllScriptCtrlStatus(void *);
extern int *GetDamageClass(void *);
extern void addPlayerHp(float);
extern float getPlayerHp(void);
extern void setPlayerHp(float);
extern void updateArrowThrustWork(void *, void *);
extern void scrRunM(int);

static void func_0004B8E0(char *arg)
{
    void *th = isysGetThisSubThread();

    for (;;) {
        CharaCtrlResetAllScriptCtrlStatus(th);
        if (*GetDamageClass(th) == 3) {
            addPlayerHp(-1.0f);
            if (getPlayerHp() < 0.0f)
                setPlayerHp(1.0f);
        }
        updateArrowThrustWork(th, arg + 0x10);
        scrRunM(1);
    }
}
