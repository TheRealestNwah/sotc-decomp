#ifdef NONMATCHING
/* 27 diffs: the original keeps &B[1] and the byte offset as two induction variables (n - B computed as offset + (&B[1] - B)); gcc strength-reduces them into one pointer. The null check on the next slot is what leaves the odd else branch. */
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
    B_000BF6C0 = iosCreateSema(1, 1, 0);
    B_000BF6CC = B_000BF6C0;
}
#endif
