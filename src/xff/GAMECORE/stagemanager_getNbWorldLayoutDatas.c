#define NULL ((void *)0)
extern void *D_0017A868;
extern int D_0017A86C;

int stagemanager_getNbWorldLayoutDatas(void) {
    if ((D_0017A868 != NULL) && (D_0017A86C != 0)) {
        return (*(int *)((char *)(D_0017A868) + 0x34)) * (*(int *)((char *)(D_0017A868) + 0x38));
    }
    return 0;
}
