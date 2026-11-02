typedef struct Sheet {
    char pad0[0x2C];
    struct Sheet *next;
} Sheet;

typedef struct SheetList {
    Sheet *head;
    Sheet *last;
} SheetList;

extern int iosCreateSema(int, int, int);
extern int iosCreateThread(void *, void *, int, int, int);
extern void iosStartThread(int, int);
extern void waitVscheduler(void);
extern int B_00151860;
extern Sheet B_00151868[0x140];
extern SheetList B_00155468;
extern int B_00155498;
extern char B_001554A0[];
extern void T_000E3230(void);
extern int D_00139F28;

void sheetMgrInit(void)
{
    int i;
    int thread;
    Sheet *arr;

    B_00151860 = iosCreateSema(1, 1, 0);
    arr = B_00151868;
    {
        Sheet **link = &arr[0x13E].next;
        Sheet *next = &arr[0x13F];
        for (i = 0x13E; i >= 0; i--) {
            *link = next;
            link = (Sheet **)((char *)link - sizeof(Sheet));
            next--;
        }
    }
    {
        Sheet *list = B_00151868;
        list[0x13F].next = 0;
        B_00155468.head = list;
        B_00155468.last = &list[0x13F];
    }
    thread = iosCreateThread(T_000E3230, B_001554A0, 0x8000, 0x2B, 0);
    B_00155498 = thread;
    iosStartThread(thread, 0);
    while (D_00139F28 == 0)
        waitVscheduler();
}
