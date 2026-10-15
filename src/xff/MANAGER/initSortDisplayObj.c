extern void *D_00136BF8, *D_00136BFC;
extern void *CreateSortList(int, int, float);

void initSortDisplayObj(void)
{
    if (D_00136BF8 == 0)
        D_00136BF8 = CreateSortList(10, 1, 200.0f);
    if (D_00136BFC == 0)
        D_00136BFC = CreateSortList(10, 1, 200.0f);
}
