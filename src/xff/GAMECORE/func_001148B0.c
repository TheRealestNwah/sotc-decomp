extern char *getSCRDataCtrlWork(void *actor);

static void func_001148B0(void *actor, void *a1, void *a2, char *src)
{
    char *work = getSCRDataCtrlWork(actor) + 0x40C0;
    *(int *)(work + 0x10) = 0;
    *(int *)(work + 0x8) += 1;
    if (src != 0) {
        *(float *)(work + 0x14) = *(float *)(src + 0x4C);
    }
}
