#ifdef NONMATCHING
/* Parked: 29 diffs. The original keeps &B[1] and the byte offset as two induction
 * variables (t0 = a3 - s0); gcc strength-reduces them into one pointer. */
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
    int i;

    B_000BF6C8 = 0;
    B_000BF6C4 = 0;
    memset(B_0006D640, 0, 0x52080);
    for (i = 0; i < 0x36AF; i++) {
        ObjSlot *p = &B_0006D640[i];
        ObjSlot *n = p + 1;

        if (n)
            p->next = n - B_0006D640;
        else
            p->next = 0;
    }
    *(ObjSlot **)&B_000BF6C0 = &B_0006D640[1];
    B_000BF6CC = iosCreateSema(1, 1, 0);
}
#endif
