typedef struct { int unk0; int a; int b; } ModPair;
typedef struct { char pad0[0x30]; ModPair pair; int x3C; int x40; char pad44[0x96C]; } Mod;
extern Mod B_000C5C18[];

int Sg2ModGetParam(int port, int type, int *a, int *b)
{
    switch (type) {
    case 1:
        *a = B_000C5C18[port].pair.a;
        *b = B_000C5C18[port].pair.b;
        break;
    case 4:
        *a = B_000C5C18[port].x3C;
        break;
    case 8:
        *a = B_000C5C18[port].x40;
        break;
    }
    return 0;
}
