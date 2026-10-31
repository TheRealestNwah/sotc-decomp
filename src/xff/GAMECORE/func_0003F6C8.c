typedef struct { char pad0[0x134]; void *target; } AimInfo;
typedef struct { char pad0[0x407C]; AimInfo *aim; } SCRWork;

extern void *isysGetThisSubThread(void);
extern void SCRExecBossPreProcess(void *);
extern void SCRExecBossPostProcess(void *);
extern void CharaCtrlResetAllScriptCtrlStatus(void *);
extern void updateScriptDataSystem(void *);
extern SCRWork *getSCRDataCtrlWork(void *);
extern void updateAimIKWork(void *, void *);
extern void scrRunM(int);

static void func_0003F6C8(void **boss)
{
    void *self = isysGetThisSubThread();

    for (;;) {
        void *th = isysGetThisSubThread();

        SCRExecBossPreProcess(*boss);
        CharaCtrlResetAllScriptCtrlStatus(th);
        updateScriptDataSystem(th);
        updateAimIKWork(self, getSCRDataCtrlWork(self)->aim->target);
        isysGetThisSubThread();
        SCRExecBossPostProcess(*boss);
        scrRunM(1);
    }
}
