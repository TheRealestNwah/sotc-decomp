extern int LoaderSysCheckCDBootMode(void);
extern int iosCreateSema(int, int, int);
extern void Sg2ExStAdpcmInit(void);
extern void Sg2ExStAdpcmSlotReserv(int, int);
extern void Sg2ExStAdpcmSetSignal(void *);
extern void func_000DC448(void);
extern void T_000DBFC0(void);
extern void func_000DBC88(void);
extern int func_000DC8F8(void);
extern void *schedAdpcmFunc;
extern void *schedAdpcmTickProc;
extern int D_00139BE0;
extern int D_00139BE4;
extern int B_0014E890;
extern int B_0014F8B8;

void adpcmMgrInit(void)
{
    int *p;
    int mode = LoaderSysCheckCDBootMode();

    p = &B_0014E890;

    if (mode == 1) {
        D_00139BE0 = mode;
        D_00139BE4 = 0x20000;
    }
    *p = LoaderSysCheckCDBootMode() == 1 ? 0xB4 : 0x168;
    B_0014F8B8 = iosCreateSema(1, 1, 0);
    Sg2ExStAdpcmInit();
    Sg2ExStAdpcmSlotReserv(0, 6);
    func_000DC448();
    schedAdpcmFunc = T_000DBFC0;
    schedAdpcmTickProc = func_000DBC88;
    Sg2ExStAdpcmSetSignal(func_000DC8F8);
}
