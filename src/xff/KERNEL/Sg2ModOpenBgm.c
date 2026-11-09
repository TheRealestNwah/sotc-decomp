typedef struct {
    int vab;
    int cls;
    char info8[4];
    char infoC[0xC];
    int unk18;
    char pad1C[0x30];
    int unk4C;
    int unk50;
    int unk54;
    void *unk58;
    void *unk5C;
    char pad60[0x9B0 - 0x60];
} SqPlayer;

extern SqPlayer B_000C5C18[];
extern int B_000D9218;
extern char D_000410F8[];
extern int vab_check_alive(void);
extern int DIntr(void);
extern int EIntr(void);
extern int Sg2SlotGetSlotClassIdx(int);
extern void func_00021488(int);
extern void vab_get_info(int, void *, void *);
extern void *vab_get_lfotbl_param(int, int *, void **);
extern int vab_get_veltbl(int, int *);

int Sg2ModOpenBgm(int vab, int arg)
{
    int i, n, intr;
    int idx;

    if (vab_check_alive() == 0) {
        return -1;
    }
    intr = DIntr();
    idx = -1;
    for (i = 0; i < 32; i++) {
        n = (B_000D9218 + i) % 32;
        if (B_000C5C18[n].vab == -1) {
            idx = n;
            B_000D9218++;
            B_000C5C18[n].cls = Sg2SlotGetSlotClassIdx(n);
            break;
        }
    }
    if (intr) {
        EIntr();
    }
    if (idx != -1) {
        func_00021488(idx);
        B_000C5C18[idx].unk18 = arg;
        vab_get_info(vab, B_000C5C18[idx].infoC, B_000C5C18[idx].info8);
        B_000C5C18[idx].vab = vab;
        B_000C5C18[idx].unk5C = vab_get_lfotbl_param(vab, &B_000C5C18[idx].unk54, &B_000C5C18[idx].unk58);
        if (B_000C5C18[idx].unk54 < 0) {
            B_000C5C18[idx].unk58 = D_000410F8;
        }
        B_000C5C18[idx].unk50 = vab_get_veltbl(vab, &B_000C5C18[idx].unk4C);
    }
    return idx;
}
