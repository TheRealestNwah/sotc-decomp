typedef struct {
    int a;
    int b;
    int started;
    int valid;
    int pad[3];
} AdpcmEntry;

extern int D_0017A004;
extern int D_0017A008;
extern int D_0017A010;
extern AdpcmEntry B_00183E10[];
extern char rootPtn[];
extern const char RO_0017CAB0[];
extern void func_00013B20(void);
extern void gcCreateScriptObj(void *, void *, void *, int, int, int, const char *);
extern int bgmStandby(int, int, int, int);
extern void scrRun(void);

void endingflowEndAdpcmSeq(int flag)
{
    AdpcmEntry *e;
    int i;

    D_0017A010 = 0;
    D_0017A008 = 0;
    if (flag != 0) {
        e = B_00183E10;
        for (i = 0; i < 3; i++, e++) {
            if (e->valid != 0 && e->started == 0) {
                e->started = 1;
                gcCreateScriptObj(func_00013B20, e, rootPtn, 0x1000, 0, 4, RO_0017CAB0);
            }
        }
        if (D_0017A004 != 0) {
            while ((D_0017A008 = bgmStandby(D_0017A004, 0, 0, 0)) == 0)
                scrRun();
        }
    }
    D_0017A004 = 0;
}
