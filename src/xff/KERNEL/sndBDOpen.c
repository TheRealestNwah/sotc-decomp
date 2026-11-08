typedef struct { char pad0[4]; int vab; char pad8[8]; int spu; } SndBD;

extern char RO_00044940[];
extern int iosAllocIopHeap(int);
extern void iosFreeIopHeap(int);
extern void iosJumpRecoverPoint(void *);
extern void iosEE2IopRequest(int, int, int, void *);
extern int iosEE2IopEndChk(int);
extern void iosWaitIdleThread(void);
extern int Sg2DmaTransVoice(int, int, int);
extern int Sg2DmaTransStatus(int);
extern void Sg2VabBdOpen(int, int);

void sndBDOpen(SndBD *bd, int (*read)(void), int req, int size, void (*idle)(void))
{
    int id[4];
    int offset = 0;
    int buf = iosAllocIopHeap(size);
    int n;

    if (buf == 0) {
        iosJumpRecoverPoint(RO_00044940);
    }
    while ((n = read()) != 0) {
        int dma;

        iosEE2IopRequest(req, buf, n, id);
        while (iosEE2IopEndChk(id[0]) == 0) {
            if (idle != 0) {
                idle();
            }
        }
        dma = Sg2DmaTransVoice(buf, bd->spu + offset, n);
        while (Sg2DmaTransStatus(dma) != 0) {
            if (idle == 0) {
                iosWaitIdleThread();
            } else {
                idle();
            }
        }
        offset += n;
    }
    if (bd->vab >= 0 && bd->spu != 0) {
        Sg2VabBdOpen(bd->vab, bd->spu);
    }
    iosFreeIopHeap(buf);
}
