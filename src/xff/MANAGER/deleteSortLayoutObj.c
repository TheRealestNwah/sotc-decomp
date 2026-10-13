extern void DeleteSortList(int);
extern int D_00136BF8;
extern int D_00136BFC;

void deleteSortLayoutObj(void)
{
    if (D_00136BF8 != 0) {
        DeleteSortList(D_00136BF8);
    }
    if (D_00136BFC != 0) {
        DeleteSortList(D_00136BFC);
    }
}
