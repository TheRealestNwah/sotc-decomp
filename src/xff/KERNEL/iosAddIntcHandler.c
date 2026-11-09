/* Matches only with -fno-strict-aliasing (config/ee_cflags.json). */
typedef struct {
    int id;
    int intc;
    int (*handler)(int);
} IntcEntry;

extern IntcEntry D_000405A0[];
extern char RO_00041ED8[];
extern char RO_00041F20[];
extern void iosJumpRecoverPoint(const char *, ...);
extern int AddIntcHandler(int, int (*)(int), int);
extern void LoaderSysEntryExternalIntcHandlerList(int, int);
extern int EnableIntc(int);

void iosAddIntcHandler(int id, int (*handler)(int))
{
    unsigned int i;

    for (i = 0; i < 11; i++) {
        if (D_000405A0[i].id == id)
            goto found;
    }
    iosJumpRecoverPoint(RO_00041ED8);
    return;
found:
    if (D_000405A0[i].handler) {
        iosJumpRecoverPoint(RO_00041F20);
        return;
    }
    D_000405A0[i].handler = handler;
    LoaderSysEntryExternalIntcHandlerList(AddIntcHandler(D_000405A0[i].intc, handler, 0), D_000405A0[i].intc);
    EnableIntc(D_000405A0[i].intc);
}
