typedef struct {
    int obj;
    char pad04[0x34];
    int p8;
    int loaded;
    int f40;
    int f44;
    char pad48[8];
    int f50;
    int done;
} DemoSlot;

extern char SH_StageDataDEFAULT[];
extern int sheetMgrLoadSegmentIndex(char *, int, int *);
extern void sheetMgrUnloadSegmentIndex(char *, int, int);
extern void scrRun(void);
extern void *isysGetThisSubThread(void);
extern void *DisplayCaptionTableBlock(char *, void *, int, int *);
extern void isysRequestDeleteObj(void *);

static void T_00120848(DemoSlot *s)
{
    int st[2];
    char *sh = SH_StageDataDEFAULT;
    register char *e __asm__("$16");

    sheetMgrLoadSegmentIndex(sh, s->p8, &st[0]);
    while (!(st[0] == 0xDEAF || st[0] == 0xDEB0))
        scrRun();
    s->loaded = 1;
    e = *(char **)(sh + 0x10);
    e += s->p8 * 20;
    if (s->f44 == 0) {
        e = DisplayCaptionTableBlock(e + 4, isysGetThisSubThread(), 3, &st[1]);
        while (st[1] == 0 && s->f50 == 0)
            scrRun();
        if (st[1] == 0)
            isysRequestDeleteObj(e);
    }
    if (s->obj != 0)
        s->f40 = 1;
    sheetMgrUnloadSegmentIndex(sh, s->p8, 0);
    s->done = 0;
}
