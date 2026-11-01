extern int D_0017ABC4;
extern int opflowAdvertiseDemoStat;
extern int isysGetThisSubThread(void);
extern void func_00056C60(char *);
extern void scrRunM(int);
extern void scrRun(void);
extern char *GetCharacterClass(int);
extern char *GetLayoutClass(int);
extern int StageManagerCheckAreaExist(int);

static void func_0005BFF0(char *w)
{
    int th = isysGetThisSubThread();
    for (;;) {
        func_00056C60(w);
        isysGetThisSubThread();
        scrRunM(1);
        if (*(int *)(w + 0x4204) != 0 || opflowAdvertiseDemoStat == 2) {
            while (*(int *)(GetCharacterClass(th) + 0x1170) != 0
                   && StageManagerCheckAreaExist(*(int *)(GetLayoutClass(th) + 0x134)) == 0) {
                scrRun();
            }
        }
        while (D_0017ABC4 != 0) {
            scrRun();
        }
    }
}
