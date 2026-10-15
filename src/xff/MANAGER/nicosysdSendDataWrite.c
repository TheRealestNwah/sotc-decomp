typedef struct { int a, b, pos; char *buf; int size; } SendBuf;
extern int D_00139EF0;
extern unsigned char RO_00141920[];
extern void *memcpy(void *, const void *, unsigned int);
extern void iosJumpRecoverPoint(void *);

void nicosysdSendDataWrite(SendBuf *b, void *src, int n)
{
    if (D_00139EF0 != 0) {
        memcpy(b->buf + b->pos, src, n);
        b->pos += n;
        if (b->size < b->pos) {
            iosJumpRecoverPoint(RO_00141920);
            b = 0;
        }
    }
}
