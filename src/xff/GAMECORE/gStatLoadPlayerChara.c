typedef struct Ptn Ptn;
extern Ptn rootPtn;
extern int D_0017A280;
extern void stagemanager_unloadstagecore(int);
extern void stagemanager_loadstagecore(Ptn *, int, int, int);
extern void gStatLoadPlayerAccessories(void);

void gStatLoadPlayerChara(int a)
{
    int id = 0xB6;
    int c = D_0017A280;
    if (c != 0) {
        if (c == id)
            goto done;
        if (c != 0)
            stagemanager_unloadstagecore(c);
    }
    stagemanager_loadstagecore(&rootPtn, 0xB6, a, 0);
done:
    D_0017A280 = 0xB6;
    gStatLoadPlayerAccessories();
}
