typedef struct {
    int unk0;
    int unk4;
    void *unk8;
} StageBuf;

typedef struct {
    int unk0;
    int unk4;
    int unk8;
} SeamlessObj;

extern StageBuf D_0017A340;
extern char D_0017A3AC[];
extern SeamlessObj *D_0017A3D4;
extern int func_0001EC38(SeamlessObj *);
extern void func_0001FA68(int, int, int);
extern void **isysGroupForFirst(void *, int);
extern void **isysGroupForNext(void **, int);
extern void isysGroupForExit(void *, int);
extern void isysSleepSubThread(void);
extern void iosFree(void *);

void WaitUnloadSeamlessStageObject(int keep)
{
    if (D_0017A340.unk8 != 0) {
        SeamlessObj *o = D_0017A3D4;

        while (o != 0) {
            if (func_0001EC38(o) != 0)
                func_0001FA68(o->unk8, o->unk0, o->unk4);
        }
    }
    while (1) {
        int n = 0;
        void *last = 0;
        void **it;

        for (it = isysGroupForFirst(D_0017A3AC, 0); it != 0; it = isysGroupForNext(it, 0)) {
            last = *it;
            n++;
        }
        if (last != 0)
            isysGroupForExit(last, 0);
        if (n == 0) {
            if (keep == 0 && D_0017A340.unk8 != 0) {
                iosFree(D_0017A340.unk8);
                D_0017A340.unk8 = 0;
            }
            return;
        }
        isysSleepSubThread();
    }
}
