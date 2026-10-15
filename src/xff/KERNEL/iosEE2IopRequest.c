typedef struct { int data; int addr; int size; int mode; } SifDma;
extern void FlushCache(int);
extern void iosWaitIopSema(void);
extern void iosSignalIopSema(void);
extern int sceSifSetDma(SifDma *, int);
extern int sceSifDmaStat(int);

void iosEE2IopRequest(int data, int addr, int size)
{
    SifDma d;
    int id;
    d.data = data;
    d.addr = addr;
    d.size = size;
    d.mode = 0;
    FlushCache(0);
    iosWaitIopSema();
    id = sceSifSetDma(&d, 1);
    while (sceSifDmaStat(id) >= 0)
        ;
    iosSignalIopSema();
    FlushCache(0);
}
