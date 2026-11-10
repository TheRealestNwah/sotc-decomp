#ifdef NONMATCHING
/* Parked: 13 words differ (base is built in $v0 then copied to $s0, and the
 * loop-invariant setup is scheduled in a different order) */
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
    char *base = (char *)B_0006D640;
    register char *nb __asm__("$7");
    register int d __asm__("$8");
    register int off __asm__("$4");
    register int n __asm__("$5");

    B_000BF6C8 = 0;
    B_000BF6C4 = 0;
    memset(base, 0, 0x52080);
    nb = base + sizeof(ObjSlot);
    d = nb - base;
    __asm__("" : "+r"(d));
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
