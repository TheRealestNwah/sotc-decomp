#ifdef NONMATCHING
/* Parked: 8 words differ (instruction scheduling only: the memset size
 * and the loop-invariant 0xAAAB constant are loaded later than in the
 * Original) */
typedef struct {
    char pad0[0xE];
    short next;
    char pad10[8];
} ObjSlot;

extern ObjSlot B_0006D640[];
extern int B_000BF6C0;
extern int B_000BF6C4;
extern int B_000BF6C8;
extern int B_000BF6CC;
extern void *memset(void *, int, unsigned int);
extern int iosCreateSema(int, int, int);


void isysInitObjSystem(void)
{
    char *base;
    char *first;
    char *nb;
    int d;
    int off;
    int n;

    B_000BF6C8 = 0;
    B_000BF6C4 = 0;
    memset(B_0006D640, 0, 0x52080);
    base = (char *)B_0006D640;
    first = base;
    __asm__("" : "+r"(base));
    nb = first + sizeof(ObjSlot);
    d = nb - base;
    off = 0;
    for (n = 0x36AE; n >= 0; n--) {
        ObjSlot *nx = (ObjSlot *)(off + (int)nb);
        ObjSlot *p = (ObjSlot *)(off + (int)base);
        if (nx)
            p->next = (ObjSlot *)(off + d) - (ObjSlot *)0;
        else
            p->next = 0;
        off += sizeof(ObjSlot);
    }
    *(ObjSlot **)&B_000BF6C0 = &B_0006D640[1];
    B_000BF6CC = iosCreateSema(1, 1, 0);
}
#endif
