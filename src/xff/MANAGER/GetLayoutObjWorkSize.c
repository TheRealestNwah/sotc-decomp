#define NULL ((void *)0)
extern int GetClothWorkSize(int);
extern int func_00074270(void *);

int GetLayoutObjWorkSize(void *arg0) {
    int var_s1;
    void *temp_v0;

    temp_v0 = (*(void **)((char *)(arg0) + 0xC));
    var_s1 = 0;
    if (temp_v0 != NULL) {
        var_s1 = GetClothWorkSize((*(int *)((char *)((*(void **)((char *)(temp_v0) + 8))) + 0x20)));
    }
    return var_s1 + func_00074270(arg0);
}
