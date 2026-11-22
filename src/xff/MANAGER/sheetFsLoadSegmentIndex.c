extern int D_00139F04;
extern int B_001517D8;
extern char *B_001517E0;
extern int sheetFsLanguageCode;
extern char RO_001419F0[];
extern char RO_001419F8[];
extern int strcmp(const char *, const char *);
extern int func_000E1030(int, void *);
extern void iosCdStStart(int);
extern void iosCdStStop(void);
extern void iosJumpRecoverPoint(void *, ...);

typedef struct {
    char c[6];
} Tag6;

typedef struct {
    char *name;
    char pad4[4];
    short *map;
    char padC[8];
    int *tab;
    int *langTab;
} SegEntry;

void sheetFsLoadSegmentIndex(char *name, int unused, int idx, void (*cb)(int, int))
{
    struct {
        char flag;
        char pad1[3];
        short idx;
        char pad6[2];
    } req;
    Tag6 tag;
    int pos = -1;
    SegEntry *e;

    if (D_00139F04 != 0) {
        tag = *(Tag6 *)RO_001419F0;
        req.idx = idx;
        if (strcmp((char *)&tag, name) == 0)
            req.flag = 0;
        else
            req.flag = 1;
        pos = func_000E1030(D_00139F04, &req);
    }
    if (pos < 0) {
        int i = 0;
        e = 0;
        for (; i < B_001517D8; i++) {
            e = &((SegEntry *)B_001517E0)[i];
            if (strcmp(name, e->name) == 0)
                goto found;
        }
        iosJumpRecoverPoint(RO_001419F8, name);
    found:
        {
            int m = e->map[idx];
            if ((m & 0x8000) == 0)
                pos = *(int *)((char *)e->tab + m * 8);
            else {
                int lang = sheetFsLanguageCode;
                int t = (int)e->langTab;
                int t2;
                m &= 0x7FFF;
                t2 = m * 8 + t;
                pos = *(int *)(lang * 8 + t2 - 8);
            }
        }
    }
    iosCdStStart(pos);
    cb(0, 0);
    iosCdStStop();
}
