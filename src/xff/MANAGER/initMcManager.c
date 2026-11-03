#ifdef NONMATCHING /* register allocation and store order in the prologue differ (74 diffs) */
typedef struct McEntry {
    int file;
    int pad;
} McEntry;
typedef struct McSlot {
    int state;
    char pad[0x2C];
} McSlot;

extern int B_0014DB38;
extern int B_0014DB3C;
extern McEntry *B_0014DB40;
extern int B_0014DB44;
extern int mcMainNeedCluster;
extern char B_0014DB10[];
extern char B_0014DB30[];
extern char B_0014CB10[];
extern int B_0014CB04;
extern McSlot B_0014DB50[2];
extern int sheetFsGetDirectFileSize(int);
extern void iosCreateMsgQueue(void *, void *, int);
extern int iosCreateThread(void *, void *, int, int, int);
extern void iosStartThread(int, int);
extern void mcManager(void);
void initMcManager(McEntry *list, int a, int b)
{
    int n; int i;
    B_0014DB38 = a; B_0014DB3C = b; B_0014DB40 = list;
    mcMainNeedCluster = 0xE1;
    n = 0;
    while (list->file >= 0) {
        mcMainNeedCluster += (sheetFsGetDirectFileSize(list++->file) + 0x3FF) / 0x400;
        n++;
    }
    mcMainNeedCluster += (n + 2) / 2;
    B_0014DB44 = n + 1;
    iosCreateMsgQueue(B_0014DB10, B_0014DB30, 1);
    B_0014CB04 = iosCreateThread(mcManager, B_0014CB10, 0x1000, 0x2F, 0);
    for (i = 1; i >= 0; i--) B_0014DB50[i].state = 0;
    iosStartThread(B_0014CB04, 0);
}
#endif
