extern char gcGlobalVar[];
extern char SH_SmallAnimalTypeDEFAULT[];
extern int *isysGroupForFirst(void *, int);
extern int *isysGroupForNext(int *, int);
extern void isysGroupForExit(void *, int);
extern char *getLayoutPointData(unsigned int *, int);
extern int gexsFlagChk(int, int);

void getSmallAnimalSaveTypePos(void (*func)(char *, void *), void *arg)
{
    char *types = *(char **)(SH_SmallAnimalTypeDEFAULT + 0x10);
    char *o = 0;
    int *g;

    for (g = isysGroupForFirst(gcGlobalVar + 0x2F4, 0); g != 0; g = isysGroupForNext(g, 0)) {
        unsigned int i;
        unsigned int **points;

        o = (char *)*g;
        points = (unsigned int **)(o + 0x58);
        if (*points == 0)
            continue;
        for (i = 0; i < **(unsigned int **)(o + 0x58); i++) {
            char *pd = getLayoutPointData(*(unsigned int **)(o + 0x58), i);
            int j;

            if (*(int *)(types + *(short *)(pd + 0x14) * 52 + 0xC) == 0)
                continue;
            for (j = 0; j < *(short *)(pd + 0x18); j++) {
                int k = *(short *)(pd + 0x1A) + j;

                if (k < 0x40 && gexsFlagChk(*(int *)(*(char **)(o + 0x38) + 0x1C), k) == 0) {
                    func(pd, arg);
                    break;
                }
            }
        }
    }
    if (o != 0)
        isysGroupForExit(o, 0);
}
