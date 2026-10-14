typedef int s128 __attribute__((mode(TI)));
typedef unsigned int u128 __attribute__((mode(TI)));
extern void DeleteTwoWayLink(void *);
extern void *GetLayoutClass();
extern void SetGeometryPointerGlobalState(void *, void *, void *);
extern unsigned char IdentityQuaternion[1];
extern unsigned char ZeroPoint[1];

void ForceUnparentLayoutObj(void)
{
    void *temp_v0;

    temp_v0 = GetLayoutClass();
    if ((*(int *)((char *)(temp_v0) + 0x124)) != 0) {
        (*(s128 *)((char *)(temp_v0) + 0x60)) = (s128) *(*(s128 **)((char *)(temp_v0) + 0x13C));
        SetGeometryPointerGlobalState(temp_v0 + 0xC0, &IdentityQuaternion, &ZeroPoint);
        DeleteTwoWayLink(temp_v0 + 0x100);
        (*(int *)((char *)(temp_v0) + 0x124)) = 0;
    }
}
