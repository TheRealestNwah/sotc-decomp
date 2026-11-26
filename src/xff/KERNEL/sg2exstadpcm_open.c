extern void *memset(void *, int, unsigned int);

void Sg2ExStAdpcmWorkClear(int *p, int a)
{
    memset(p, 0, 0x2E0);
    p[0] = 0;
    p[2] = a;
    p[3] = a;
}

extern int B_000C5B40[];
extern int Sg2StAdpcmOpen(char *);
extern void Sg2SlotSetReverbOnBit(int, int);
extern void Sg2SlotSetReverbOffBit(int, int);

typedef struct {
    int magic;
    int info;
    char pad8[0x50];
    int rev[1];
} ExStRevHdr;

static int func_000200F0(char *st)
{
    ExStRevHdr *hdr = (ExStRevHdr *)(st + 0x28);
    unsigned long on[2];
    unsigned long off[2];
    unsigned long *p;
    unsigned long slot;
    int chunk;
    int n;
    int i;
    int j;
    int end;
    int start;
    int a3;

    n = ((short *)hdr)[3];
    chunk = 0x800 / n;
    on[1] = 0;
    on[0] = 0;
    off[1] = 0;
    off[0] = 0;
    for (i = 0; i < n; i++) {
        a3 = *(int *)(st + 0x23C);
        *(int *)(st + 0x18) = *(int *)(st + 0x230) + i * chunk;
        *(int *)(st + 0x1C) = *(int *)(st + 0x234);
        *(int *)(st + 0x20) = *(int *)(st + 0x238) + a3 * i;
        *(int *)(st + 0x24) = a3;
        if (*(int *)(st + 8) & 0x40) {
            start = 0x18;
            end = 0x30;
        } else {
            start = 0;
            end = 0x18;
        }
        for (j = start; j < end; j++) {
            if (B_000C5B40[j] == 1) {
                slot = j;
                B_000C5B40[j] = 2;
                break;
            }
        }
        if (j == end)
            return -1;
        *(int *)(st + 0x10) = slot;
        *(int *)(st + 0x14) = hdr->info;
        if (hdr->rev[i] != 0)
            on[slot / 24] |= 1 << (slot % 24);
        else
            off[slot / 24] |= 1 << (slot % 24);
        Sg2StAdpcmOpen(st + 0x10);
        *(unsigned long *)(st + 0xA0) |= (unsigned long)1 << (int)slot;
    }
    for (i = 0; i < 2; i++) {
        if (on[i] != 0)
            Sg2SlotSetReverbOnBit(i, on[i]);
        if (off[i] != 0)
            Sg2SlotSetReverbOffBit(i, off[i]);
    }
    *(int *)st = 1;
    return 0;
}


int Sg2ExStAdpcmOpenFake(char *st)
{
    int *magic = (int *)(st + 0x28);
    if (*(int *)st != 0)
        return -3;
    if (*magic != 0x54535845)
        return -1;
    *(int *)(st + 0x2D4) = 0;
    *(int *)(st + 0x248) = 0;
    *(long *)(st + 0xA0) = 0;
    *(int *)(st + 0x228) = 0;
    *(int *)(st + 0x22C) = 0;
    memset(st + 0xA8, 0, 0x180);
    *(int *)(st + 8) = *(int *)(st + 0xC);
    if (func_000200F0(st))
        return -2;
    return 0;
}

typedef struct {
    int w[0x1E];
} ExStHdr;

typedef struct {
    int a;
    int b;
} ExStVol;

typedef struct {
    char pad0[0x28];
    ExStHdr hdr;
    char padA0[0x230 - 0xA0];
    int unk230;
    int unk234;
    int unk238;
    int unk23C;
    int unk240;
    int unk244;
    char pad248[4];
    ExStVol vol[8];
    char pad28C[0x2CC - 0x28C];
    int unk2CC;
    char pad2D0[8];
    int unk2D8;
    int unk2DC;
} ExSt;


int Sg2ExStAdpcmOpen(ExSt *st, ExStHdr *hdr, int a2, int a3, int a4, int a5)
{
    int i;
    int *v;

    st->hdr = *hdr;
    st->unk230 = a2;
    st->unk234 = a3;
    st->unk238 = a4;
    st->unk23C = a5;
    st++;
    st--;
    st->unk2D8 = 0;
    st->unk2DC = 0;
    st->unk240 = hdr->w[4] << 11;
    st->unk244 = hdr->w[5] << 11;
    v = &st->vol[0].b;
    for (i = 0; i < 8; i++) {
        v[-1] = 100;
        v[0] = 100;
        v += 2;
    }
    st->unk2CC = 100;
    return Sg2ExStAdpcmOpenFake((char *)st);
}
