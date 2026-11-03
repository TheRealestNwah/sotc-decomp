struct ExcReg {
    unsigned int lo;
    unsigned int hi;
};

struct ExcState {
    struct ExcReg gpr[32];
    struct ExcReg cop0[32];
};

extern void *SetDebugHandler(int cause, void (*handler)());
extern void func_001021E0();
extern void func_00102360();
extern void func_00103B40(void);
extern struct ExcReg D_00131D00[];
extern struct ExcState D_00131D80;

register char *sp asm("$29");

void InitException(void) {
    int i;

    for (i = 0; (unsigned int)i < 14; i++) {
        switch (i) {
        case 0:
        case 8:
            break;
        case 9:
            SetDebugHandler(D_00131D00[9].lo, func_00102360);
            break;
        default:
            SetDebugHandler(D_00131D00[i].lo, func_001021E0);
            break;
        }
    }
    for (i = 63; i >= 0; i--) {
        ((volatile struct ExcState *)&D_00131D80)->gpr[i].lo = 0;
    }
    D_00131D80.gpr[29].lo = (unsigned int)sp;
    D_00131D80.gpr[31].lo = (unsigned int)func_00103B40;
    D_00131D80.cop0[14].lo = (unsigned int)func_00103B40;
}
