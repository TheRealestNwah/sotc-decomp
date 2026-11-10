typedef struct {
    void *buf[2];
    void *pkt[2];
    int ptr;
    int n;
    int cur;
    int last;
    int group[2];
    int x28[2];
} DLState;

extern DLState B_00065018;
extern int D_00040AFC;
extern char rootPtn[];
extern void *iosMallocAlign(void *, int, int);
extern void func_00012C30(void);
extern void isysInitGroup(void *);

static void func_00013050(int size, int n)
{
    int i;

    D_00040AFC = size;
    for (i = 0; i < 2; i++) {
        B_00065018.buf[i] = iosMallocAlign(rootPtn, D_00040AFC * 16, 0x10);
    }
    B_00065018.n = n;
    for (i = 0; i < 2; i++) {
        B_00065018.pkt[i] = iosMallocAlign(rootPtn, B_00065018.n * 48 + 0x30, 0x10);
    }
    for (i = 0; i < 2; i++) {
        B_00065018.cur = i;
        func_00012C30();
    }
    B_00065018.cur = 0;
    B_00065018.last = n - 1;
    for (i = 0; i < 2; i++) {
        isysInitGroup(&B_00065018.group[i]);
        B_00065018.x28[i] = 0;
    }
}
