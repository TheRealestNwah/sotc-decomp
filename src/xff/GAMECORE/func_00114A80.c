extern char *getSCRDataCtrlWork(void *actor);

static int func_00114A80(void *actor, char *s)
{
    char *w = getSCRDataCtrlWork(actor) + 0x4030;
    if (s == 0) {
        return 0;
    }
    switch (*(int *)(s + 0x18)) {
    case 0:
        return 1;
    case 1:
        return *(int *)(w + 0x2C);
    case 2:
        return *(int *)(w + 0x30) | *(int *)(w + 0x34);
    }
    return 0;
}
