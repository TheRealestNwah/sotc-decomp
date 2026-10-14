typedef int s128 __attribute__((mode(TI)));
typedef unsigned int u128 __attribute__((mode(TI)));
extern void GetGeometryPointerPosition(void *, int);
extern int GetLayoutClass(int);
extern unsigned char B_0018A4E0[1];
extern s128 B_0018A4F0;
extern s128 ZeroPoint;

void nico_IK_getParentPoint(int *arg0)
{
    GetGeometryPointerPosition(&B_0018A4E0, GetLayoutClass(*arg0) + 0xC0);
    B_0018A4F0 = ZeroPoint;
}
