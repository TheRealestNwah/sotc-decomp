typedef struct Ptn Ptn;
extern Ptn rootPtn;
extern char RO_0017C6C0[], RO_0017C6D0[];
static void func_00005B68(void);
static void func_00008050(void);
extern void DebugGlobalMoveWith2ndController(void);
extern void *gcCreateScriptObj(void *, int, Ptn *, int, int, int, const char *);
extern void DEBUG_set_update_position_method_pointer(void *);

void createDebugSubThreads(void)
{
    gcCreateScriptObj(func_00005B68, 0, &rootPtn, 0x2000, 0, 8, RO_0017C6C0);
    gcCreateScriptObj(func_00008050, 0, &rootPtn, 0x1000, 0, 8, RO_0017C6D0);
    DEBUG_set_update_position_method_pointer(DebugGlobalMoveWith2ndController);
}
