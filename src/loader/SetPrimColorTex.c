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
extern unsigned int D_0013A14C;
extern u_long128 D_00137C50;

void SetPrimColorTex(int prim, int r, int g, int b, int a, int fst) {
    struct Vif1Packet pk;
    int *ch;

    sceVif1PkInit(&pk, (u_long128 *)((D_0013A144 << 13) | 0x70000000));
    sceVif1PkReset(&pk);
    sceVif1PkCnt(&pk, 0);
    sceVif1PkOpenDirectCode(&pk, 0);
    D_0013A144 = (D_0013A144 + 1) & 1;
    sceVif1PkOpenGifTag(&pk, D_00137C50);
    sceVif1PkAddGsData(&pk, (unsigned long)(prim | 0x10) | (fst ? 0x100UL : 0));
    sceVif1PkAddGsData(&pk, (unsigned long)r | ((unsigned long)g << 8) | ((unsigned long)b << 16) |
                                ((unsigned long)a << 24) | ((unsigned long)D_0013A14C << 32));
    sceVif1PkCloseGifTag(&pk);
    sceVif1PkCloseDirectCode(&pk);
    sceVif1PkEnd(&pk, 0);
    sceVif1PkTerminate(&pk);
    sceGsSyncPath(0, 0);
    ch = sceDmaGetChan(1);
    *ch |= 0x40;
    sceDmaSend(ch, ((unsigned int)pk.pBase & 0x3FF0) | 0x80000000);
}

