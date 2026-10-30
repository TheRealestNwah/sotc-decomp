extern char *getSCRDataCtrlWork(void *actor);

static void func_00114A48(void *actor, void *a1, void *a2, char *src)
{
    char *work = getSCRDataCtrlWork(actor) + 0x40C0;
    if (src != 0) {
        *(float *)(work + 0x14) = *(float *)(src + 0x4C);
    }
}
