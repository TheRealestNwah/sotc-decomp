extern char rootPtn[];
extern char gcGlobalVar[];
extern int D_0017A280;
extern int D_0017A284;
extern int D_0017A288;
extern int *D_0017A28C;
extern int *D_0017A290;
extern void stagemanager_restartstagecore(void *, int, int, int);
extern void *SCRGetFirstObj(void *);
extern int _omakeSelectFlagChk(int);
extern void nico_hydePlayerByMagireManteau(void *, int);

void gStatRestartPlayerChara(void)
{
    void *p;

    if (D_0017A280 != 0)
        stagemanager_restartstagecore(rootPtn, D_0017A280, -1, 0);
    if (D_0017A284 != 0)
        stagemanager_restartstagecore(rootPtn, D_0017A284, -1, 0);
    if (D_0017A288 != 0)
        stagemanager_restartstagecore(rootPtn, D_0017A288, -1, 0);
    if (D_0017A28C[1] != 0)
        stagemanager_restartstagecore(rootPtn, D_0017A28C[1], -1, 0);
    if (D_0017A290[1] != 0)
        stagemanager_restartstagecore(rootPtn, D_0017A290[1], -1, 0);
    if (D_0017A280 != 0) {
        p = SCRGetFirstObj(gcGlobalVar + 0x2B0);
        nico_hydePlayerByMagireManteau(p, _omakeSelectFlagChk(7) != 0);
    }
}
