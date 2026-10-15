typedef struct { int used; } MotMan;
extern MotMan B_001498C0;
extern char *sheetFileGetDataAdrs(void *);
extern int sheetFileGetSize(void *);
extern void isysRequestDeleteObj(void *);

void unloadCdMotionFile(void *f, int b, void *o)
{
    char *d = sheetFileGetDataAdrs(f);
    if (*(int *)(d + 0xC) == 0)
        return;
    *(int *)(d + 0xC) = 0;
    B_001498C0.used -= sheetFileGetSize(f);
    isysRequestDeleteObj(o);
}
