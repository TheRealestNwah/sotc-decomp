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

static void func_00055AE0(void *character)
{
    char gp[0x40];
    Vec4 pos = {{0.01f, 0.0f, -0.05f, 1.0f}};

    SetGeometryPointerNodePosState(gp, character, *(int *)(SkelFocusDef_Guard_A_LeftHand + 8),
                                   &IdentityQuaternion, &pos);
    ParentLayoutObj(*(int *)(GameObject_END_SWORD + 8), gp);
}
