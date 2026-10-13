extern void AddTwoWayLinkNext(int, void *);
extern void GetGeometryPointerWithCollisionDBDataGlobalPoint(void *, int *, int);
extern int GetLayoutClass(int);

void LinkSecureParentInfoByDBPos(void *arg0, int *arg1, int arg2)
{
    int temp_s3;

    temp_s3 = GetLayoutClass(*arg1);
    GetGeometryPointerWithCollisionDBDataGlobalPoint(arg0, arg1, arg2);
    (*(int *)((char *)(arg0) + 0x4C)) = 1;
    AddTwoWayLinkNext(temp_s3 + 0x118, arg0 + 0x40);
}
