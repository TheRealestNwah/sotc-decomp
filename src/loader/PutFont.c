typedef int u_long128 __attribute__((mode(TI)));

struct Vif1Packet {
    u_long128 *pCurrent;
    u_long128 *pBase;
    char unk8[0x18];
};

extern void sceVif1PkInit(struct Vif1Packet *p, u_long128 *buf);
extern void sceVif1PkReset(struct Vif1Packet *p);
extern void sceVif1PkCnt(struct Vif1Packet *p, unsigned int opt);
extern void sceVif1PkOpenDirectCode(struct Vif1Packet *p, int i);
extern void sceVif1PkOpenGifTag(struct Vif1Packet *p, u_long128 gif);
extern void sceVif1PkAddGsData(struct Vif1Packet *p, unsigned long data);
extern void sceVif1PkCloseGifTag(struct Vif1Packet *p);
extern void sceVif1PkCloseDirectCode(struct Vif1Packet *p);
extern void sceVif1PkEnd(struct Vif1Packet *p, unsigned int opt);
extern void *sceVif1PkTerminate(struct Vif1Packet *p);
extern int sceGsSyncPath(int mode, unsigned short timeout);
extern int *sceDmaGetChan(int id);
extern void sceDmaSend(int *d, unsigned int addr);
extern int D_0013A144;
extern unsigned int D_0013A148;
extern u_long128 D_00137C40;
extern u_long128 D_00132240;
extern unsigned char D_00137440[];
extern int D_0013A150;
extern int D_0013A154;
extern int D_0013A158;

static inline void SetPrimColor(int prim, int r, int g, int b, int a) {
    struct Vif1Packet pkt;
    struct Vif1Packet *pk = &pkt;
    int *ch;

    sceVif1PkInit(pk, (u_long128 *)((D_0013A144 << 13) | 0x70000000));
    sceVif1PkReset(pk);
    sceVif1PkCnt(pk, 0);
    sceVif1PkOpenDirectCode(pk, 0);
    D_0013A144 = (D_0013A144 + 1) & 1;
    sceVif1PkOpenGifTag(pk, D_00137C40);
    sceVif1PkAddGsData(pk, prim | 0x40);
    sceVif1PkAddGsData(pk, (unsigned long)r | ((unsigned long)g << 8) | ((unsigned long)b << 16) |
                               ((unsigned long)a << 24) | ((unsigned long)D_0013A148 << 32));
    sceVif1PkCloseGifTag(pk);
    sceVif1PkCloseDirectCode(pk);
    sceVif1PkEnd(pk, 0);
    sceVif1PkTerminate(pk);
    sceGsSyncPath(0, 0);
    ch = sceDmaGetChan(1);
    *ch |= 0x40;
    sceDmaSend(ch, ((unsigned int)pk->pBase & 0x3FF0) | 0x80000000);
}

void PutFont(int c, int x, int y) {
    struct Vif1Packet pk;
    int *ch;
    int row;
    int bit;

    SetPrimColor(0, D_0013A150, D_0013A154, D_0013A158, 0x80);
    sceVif1PkInit(&pk, (u_long128 *)((D_0013A144 << 13) | 0x70000000));
    sceVif1PkReset(&pk);
    sceVif1PkCnt(&pk, 0);
    sceVif1PkOpenDirectCode(&pk, 0);
    D_0013A144 = (D_0013A144 + 1) & 1;
    sceVif1PkOpenGifTag(&pk, D_00132240);
    for (row = 0; row < 8; row++) {
        int yy = ((y + row) << 4) + 0x8000;
        for (bit = 0; bit < 8; bit++) {
            if ((D_00137440[c * 8 + row] >> bit) & 1) {
                int xx = ((x + bit) << 4) + 0x8000;
                sceVif1PkAddGsData(&pk, (unsigned long)xx | ((unsigned long)yy << 16) | 0x80000000000000UL);
                sceVif1PkAddGsData(&pk, (unsigned long)xx | ((unsigned long)(yy - 0x10) << 16) | 0x80000000000000UL);
            }
        }
    }
    sceVif1PkCloseGifTag(&pk);
    sceVif1PkCloseDirectCode(&pk);
    sceVif1PkEnd(&pk, 0);
    sceVif1PkTerminate(&pk);
    sceGsSyncPath(0, 0);
    ch = sceDmaGetChan(1);
    *ch |= 0x40;
    sceDmaSend(ch, ((unsigned int)pk.pBase & 0x3FF0) | 0x80000000);
}
