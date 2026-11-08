typedef struct { int unk0; int a; int b; } ModPair;
typedef struct { char pad0[0x30]; ModPair pair; int x3C; int x40; char pad44[0x96C]; } Mod;
extern Mod B_000C5C18[];

#ifdef NONMATCHING
/* Parked: 46 words differ (port kept in t0, port*5 in a0; register allocation and branch offsets) */
int Sg2ModGetParam(int port, int type, int *a, int *b)
{
    switch (type) {
    case 1: {
        ModPair *p = &B_000C5C18[port].pair;
        *a = p->a;
        *b = p->b;
        break;
    }
    case 4:
        *a = B_000C5C18[port].x3C;
        break;
    case 8:
        *a = B_000C5C18[port].x40;
        break;
    }
    return 0;
}
#endif
