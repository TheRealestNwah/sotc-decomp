typedef struct SheetReq {
    int f0;
    unsigned f4;
    char pad8[8];
    int f10, f14, f18, f1C;
    char pad20[8];
    int *f28;
    struct SheetReq *next;
} SheetReq;

typedef struct {
    SheetReq *head;
    SheetReq *tail;
} SheetQ;

extern int B_00151860;
extern SheetQ B_00155468;
extern SheetQ B_00155470;
extern char RO_00141D10[];
extern void WaitSema(int);
extern void SignalSema(int);
extern void iosJumpRecoverPoint(char *);

#ifdef NONMATCHING
void sheetMgrDirectFileLoad(int a0, int a1, int a2, int a3, int *a4) {
    SheetReq *r;
    WaitSema(B_00151860);
    r = B_00155468.head;
    if (r != 0) {
        B_00155468.head = r->next;
        if (B_00155468.head == 0) B_00155468.tail = 0;
    }
    if (r == 0) iosJumpRecoverPoint(RO_00141D10);
    r->f0 = 8;
    r->f4 = r->f4 & ~1;
    r->f10 = a0;
    r->f14 = a1;
    r->f18 = a2;
    r->f1C = a3;
    r->f28 = a4;
    if (a4 != 0) *a4 = 0xDEAD;
    r->next = 0;
    if (B_00155470.tail == 0) B_00155470.head = r;
    else B_00155470.tail->next = r;
    B_00155470.tail = r;
    SignalSema(B_00151860);
}
#else
void sheetMgrDirectFileLoad(int a0, int a1, int a2, int a3, int *a4);
#endif
