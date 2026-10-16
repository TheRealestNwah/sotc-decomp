extern char rootPtn[];
extern int D_0017ABD0;
extern int D_0017ABD4;
extern int D_0017ABD8;
extern int D_0017ABDC;
extern void *gcCreateScriptObj(void *, int, void *, int, int, int, char *);
extern void scrRun(void);
extern void func_00064798(void);

void setNowLoadingEffectDisplayFlagHokoraBack(int flag, int arg, int wait)
{
    D_0017ABD8 = 1;
    if (D_0017ABD0 != flag) {
        D_0017ABD0 = flag;
        if (flag != 0) {
            D_0017ABD4 = 0;
            D_0017ABDC = 0;
            gcCreateScriptObj(func_00064798, arg, rootPtn, 0x1200, 0, 8, "st_drawNowLoadingEffect");
            if (wait != 0 && D_0017ABDC < 4) {
                do {
                    scrRun();
                } while (D_0017ABDC < 4);
            }
        }
    }
}
