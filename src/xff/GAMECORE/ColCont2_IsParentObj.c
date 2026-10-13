extern void *GetLayoutClass(int);

int ColCont2_IsParentObj(void *arg0, int arg1)
{
    int temp_v0;

    if ((*(int *)((char *)(arg0) + 0x20)) != 0) {
        temp_v0 = (*(int *)((char *)(arg0) + 0x10));
        if (temp_v0 != 0) {
            return arg1 == (*(int *)((char *)(GetLayoutClass(temp_v0)) + 0x1A4));
        }
    }
    return 0;
}
