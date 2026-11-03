typedef struct AdpcmUser {
    char pad0[0x38];
    unsigned long flags;
} AdpcmUser;

extern AdpcmUser *Sg2ExStAdpcmGetUserParam(int);
extern void func_000DB778(AdpcmUser *, int, int);

static int func_000DC8F8(int handle, int command, int arg, int value)
{
    AdpcmUser *user = Sg2ExStAdpcmGetUserParam(handle);
    int ret = 0;

    switch (command) {
    case 1:
        func_000DB778(user, value / 2048, arg);
        ret = 0;
        break;
    case 16:
        user->flags |= 1UL << 36;
        ret = 0;
        break;
    case 2: case 3: case 4: case 5: case 6: case 7:
        break;
    case 8:
        ret = (int)(user->flags >> 35) & 1 ? -1 : 0;
        break;
    case 9: case 10: case 11: case 12: case 13: case 14: case 15:
        break;
    }
    return ret;
}
