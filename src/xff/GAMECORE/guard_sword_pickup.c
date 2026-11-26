extern void RequestCharacterMotionShiftFunc(void *character, void (*func)(void *character));
typedef union {
    struct {
        float x;
        float y;
        float z;
        float w;
    } f;
    int i[4];
} __attribute__((aligned(8))) Vec4;
extern void SetGeometryPointerNodePosState(void *, void *, int, void *, void *);
extern void ParentLayoutObj(int, void *);
extern Vec4 IdentityQuaternion;
extern char *SkelFocusDef_Guard_A_LeftHand;
extern char *GameObject_END_SWORD;
extern int D_0017ABBC;
extern int D_0017ABC0;

static void func_00055AE0(void *character);
static void func_00055B48(void);

void SCRGuardSwordPickup(void *character)
{
    RequestCharacterMotionShiftFunc(character, &func_00055AE0);
}

void SCRGuardSwordPickupEnd(void *character)
{
    RequestCharacterMotionShiftFunc(character, &func_00055B48);
}

static void func_00055AE0(void *character)
{
    char gp[0x40];
    Vec4 pos = {{0.01f, 0.0f, -0.05f, 1.0f}};

    SetGeometryPointerNodePosState(gp, character, *(int *)(SkelFocusDef_Guard_A_LeftHand + 8),
                                   &IdentityQuaternion, &pos);
    ParentLayoutObj(*(int *)(GameObject_END_SWORD + 8), gp);
}

static void func_00055B48(void)
{
    D_0017ABBC = 1;
    D_0017ABC0 = 0;
}
