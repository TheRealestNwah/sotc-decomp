typedef int s128 __attribute__((mode(TI)));
typedef unsigned int u128 __attribute__((mode(TI)));
typedef struct Link { struct Link *next; struct Link *prev; } Link;
extern int DeleteTwoWayLink(Link *);
extern void *GetLayoutClass(void *);
extern void SetGeometryPointerGlobalState(void *, void *, void *);
extern unsigned char IdentityQuaternion[];
extern unsigned char ZeroPoint[];

void ForceUnparentLayoutObj(void *actor)
{
    void *temp_v0;

    temp_v0 = GetLayoutClass(actor);
    if ((*(int *)((char *)(temp_v0) + 0x124)) != 0) {
        (*(s128 *)((char *)(temp_v0) + 0x60)) = (s128) *(*(s128 **)((char *)(temp_v0) + 0x13C));
        SetGeometryPointerGlobalState(temp_v0 + 0xC0, IdentityQuaternion, ZeroPoint);
        DeleteTwoWayLink((Link *)(temp_v0 + 0x100));
        (*(int *)((char *)(temp_v0) + 0x124)) = 0;
    }
}
