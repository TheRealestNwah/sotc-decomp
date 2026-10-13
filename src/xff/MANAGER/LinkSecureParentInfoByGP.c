extern void AddTwoWayLinkNext(int, void *);
extern void CopyGeometryPointer(void *, int);
extern int GetGeometryPointerObject(int);
extern int GetLayoutClass(int);

void LinkSecureParentInfoByGP(void *arg0, int arg1)
{
    int temp_s2;

    temp_s2 = GetLayoutClass(GetGeometryPointerObject(arg1));
    CopyGeometryPointer(arg0, arg1);
    (*(int *)((char *)(arg0) + 0x4C)) = 1;
    AddTwoWayLinkNext(temp_s2 + 0x118, arg0 + 0x40);
}
