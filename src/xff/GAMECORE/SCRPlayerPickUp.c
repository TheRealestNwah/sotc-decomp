extern char *GetSCRCharaAIWorkPtr(void *);
extern void _omakeGetFlagSet(int);
extern void _omakeSelectFlagSet(int);
extern void SCRPlayerGetWeapon(int);
extern void SetLayoutObjAccessSwitch(void *, int);
extern void isysRequestDeleteObj(void *);

void SCRPlayerPickUp(void *a)
{
    char *w = GetSCRCharaAIWorkPtr(a);
    if (*(void **)(w + 0xD90) == 0)
        return;
    _omakeGetFlagSet(0x10);
    _omakeSelectFlagSet(0x10);
    SCRPlayerGetWeapon(9);
    SetLayoutObjAccessSwitch(*(void **)(w + 0xD90), 0);
    *(void **)(w + 0xD90) = 0;
    if (*(void **)(w + 0x150) != 0) {
        isysRequestDeleteObj(*(void **)(w + 0x150));
        *(void **)(w + 0x150) = 0;
    }
}
