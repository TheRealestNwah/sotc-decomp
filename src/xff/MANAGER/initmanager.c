typedef struct Ptn Ptn;
extern Ptn rootPtn;
extern void *D_00130340;
extern void dsysInit(void);
extern void InitBinarySize(void);
extern void sheetMgrInit(void);
extern void initSoundManager(void);
extern void adpcmMgrInit(void);
extern void *iosCreatePartition(Ptn *, int);
extern void init_camera_context_manager(void);
extern void init_wind_manager(void);
extern void init_particle_manager(void);
extern void InitDamageLetter(void);

void initmanager(void)
{
    dsysInit();
    InitBinarySize();
    sheetMgrInit();
    initSoundManager();
    adpcmMgrInit();
    D_00130340 = iosCreatePartition(&rootPtn, 0x19999);
    init_camera_context_manager();
    init_wind_manager();
    init_particle_manager();
    InitDamageLetter();
}
