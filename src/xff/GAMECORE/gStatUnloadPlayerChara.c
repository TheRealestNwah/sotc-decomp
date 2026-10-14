

#define NULL ((void *)0)
extern void stagemanager_unloadstagecore(int);
extern unsigned char D_0017A240[];
extern int D_0017A280;
extern int D_0017A284;
extern int D_0017A288;
extern void *D_0017A28C;
extern void *D_0017A290;

void gStatUnloadPlayerChara(void) {
    int temp_a0;
    int temp_a0_2;

    temp_a0 = (*(int *)((char *)(D_0017A28C) + 4));
    if (temp_a0 != 0) {
        stagemanager_unloadstagecore(temp_a0);
    }
    D_0017A28C = D_0017A240;
    temp_a0_2 = (*(int *)((char *)(D_0017A290) + 4));
    if (temp_a0_2 != 0) {
        stagemanager_unloadstagecore(temp_a0_2);
    }
    D_0017A290 = NULL;
    if (D_0017A284 != 0) {
        stagemanager_unloadstagecore(D_0017A284);
        D_0017A284 = 0;
    }
    if (D_0017A288 != 0) {
        stagemanager_unloadstagecore(D_0017A288);
        D_0017A288 = 0;
    }
    if (D_0017A280 != 0) {
        stagemanager_unloadstagecore(D_0017A280);
    }
    D_0017A280 = 0;
}
