extern void SetLayoutObjAccessSwitchThisObjOnly(void *obj, int on);

static void func_000348C0(char *o)
{
    int kind;

    *(int *)(o + 0x98) = 0;
    SetLayoutObjAccessSwitchThisObjOnly(*(void **)(o + 0x94), 0);
    switch (*(int *)(o + 0x4C)) {
    case 0:
    case 2:
        *(short *)(o + 0xA0) = 1;
        break;
    case 1:
        kind = *(int *)(o + 0x48);
        if (kind == 4 || kind == 6) {
            *(short *)(o + 0xA0) = 2;
        } else if (kind == 7) {
            *(short *)(o + 0xA0) = 4;
        } else if (kind == 5) {
            *(short *)(o + 0xA0) = kind;
        }
        break;
    }
}
