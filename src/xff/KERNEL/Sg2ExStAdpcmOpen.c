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

extern int Sg2ExStAdpcmOpenFake(ExSt *);

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
    return Sg2ExStAdpcmOpenFake(st);
}
