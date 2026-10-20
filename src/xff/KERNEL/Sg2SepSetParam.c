typedef struct { int status, previous, unk8, vab, mod; char pad14[60]; } Sep;
extern Sep B_000DD700[];
extern int Sg2ModSetParam(int, int, int, int);
int Sg2SepSetParam(unsigned int id, int selector, int value, int extra)
{
    if (id < 32) {
        switch (selector) {
        case 2:
            Sg2ModSetParam(B_000DD700[id].mod, 1, value, extra);
            break;
        case 0x400:
            Sg2ModSetParam(B_000DD700[id].mod, 0x10000, value, extra);
            break;
        case 4:
            Sg2ModSetParam(B_000DD700[id].mod, 4, value, extra);
            break;
        case 8:
            Sg2ModSetParam(B_000DD700[id].mod, 0x10, 1, 0);
            break;
        case 0x10:
            Sg2ModSetParam(B_000DD700[id].mod, 0x10, 0, 0);
            break;
        case 0x20:
            Sg2ModSetParam(B_000DD700[id].mod, 0x100, value, extra);
            break;
        case 0x40:
            Sg2ModSetParam(B_000DD700[id].mod, 0x200, value, 0);
            break;
        case 0x80:
            Sg2ModSetParam(B_000DD700[id].mod, 0x400, value, extra);
            break;
        case 0x100:
            Sg2ModSetParam(B_000DD700[id].mod, 0x800, value, extra);
            break;
        case 0x200:
            Sg2ModSetParam(B_000DD700[id].mod, 0x1000, value, extra);
            break;
        }
    }
    return 0;
}
