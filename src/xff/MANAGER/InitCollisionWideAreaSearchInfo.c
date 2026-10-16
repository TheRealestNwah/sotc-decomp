typedef struct {
    long a[30];
} WideAreaSearch;

extern WideAreaSearch D_00136F90;

void InitCollisionWideAreaSearchInfo(WideAreaSearch *p)
{
    *p = D_00136F90;
}
