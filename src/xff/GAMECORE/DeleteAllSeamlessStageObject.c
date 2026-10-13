#define NULL ((void *)0)
extern int func_0001EC38(void *);
extern void func_0001FA68(int, int, int);
extern int D_0017A348;
extern void *D_0017A3D4;

void DeleteAllSeamlessStageObject(void)
{
    void *temp_s0;

    if (D_0017A348 != 0) {
        temp_s0 = D_0017A3D4;
        if (temp_s0 != NULL) {
            do {
                if (func_0001EC38(temp_s0) != 0) {
                    func_0001FA68((*(int *)((char *)(temp_s0) + 8)), (*(int *)((char *)(temp_s0) + 0)), (*(int *)((char *)(temp_s0) + 4)));
                }
            } while (temp_s0 != NULL);
        }
    }
}
