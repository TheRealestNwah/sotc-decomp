typedef struct {
    void *fs;
    int size;
    int used;
    int pad;
} Ctx;

typedef struct {
    Ctx *ctx;
    int a;
    int b;
    int c;
    int pad[4];
} Reader;

typedef void (*LoadFn)(Reader *, void *, void *, int, int, int, int);

typedef struct {
    char pad[0x1C];
    LoadFn *fns;
} StageSegDef;

typedef struct {
    char pad[0x2C];
    void *header;
} TexSegDef;

extern StageSegDef _StageSegDef;
extern TexSegDef _TexSegDef;
extern int B_00151824;
extern int B_00151828;
extern void sheetFsDataRead(void *, void *, int);
extern void sheetFsSectorAlignSkip(void *);
extern char *sheetMgrSheetHeaderSearchSheetDataObj(void *, int);

#ifdef NONMATCHING
/* 85 diffs: VLA stack pointer copied into a saved register in the target */
static void T_000E1870(void *fs)
{
    Ctx ctx;
    Reader r0;
    Reader r1;
    char buf[0x1000];
    int type;
    int a;
    int b;
    int hash;
    int len;
    int size;
    int n;
    int i;
    int rem;
    int chunk;
    LoadFn fn;
    void *hdr;
    char *obj;

    n = B_00151828;
    for (i = 0; i < n; i++) {
        sheetFsDataRead(fs, &type, 4);
        if (type == 0) {
            fn = _StageSegDef.fns[1];
            sheetFsDataRead(fs, &a, 4);
            sheetFsDataRead(fs, &b, 4);
            ctx.fs = fs;
            ctx.size = 0;
            ctx.used = 0;
            if (fn != 0) {
                r0.ctx = &ctx;
                r0.a = 0;
                r0.b = 0;
                r0.c = 0;
                fn(&r0, 0, 0, 0, a, b, B_00151824);
            }
        } else {
            hdr = 0;
            sheetFsDataRead(fs, &a, 4);
            sheetFsDataRead(fs, &b, 4);
            sheetFsDataRead(fs, &hash, 4);
            sheetFsDataRead(fs, &len, 4);
            fn = _StageSegDef.fns[1];
            {
                char data[len];
                obj = sheetMgrSheetHeaderSearchSheetDataObj(_TexSegDef.header, hash);
                if (obj != 0)
                    hdr = *(void **)(obj + 0x38);
                sheetFsDataRead(fs, data, len);
                sheetFsDataRead(fs, &size, 4);
                ctx.fs = fs;
                ctx.size = size;
                ctx.used = 0;
                if (fn != 0 && size != 0) {
                    r1.ctx = &ctx;
                    r1.a = 0;
                    r1.b = 0;
                    r1.c = 0;
                    fn(&r1, data, hdr, size, a, b, B_00151824);
                }
                rem = ctx.size - ctx.used;
                while (rem > 0) {
                    chunk = rem > 0x1000 ? 0x1000 : rem;
                    rem -= chunk;
                    sheetFsDataRead(fs, buf, chunk);
                }
            }
        }
        if (i + 1 < n)
            sheetFsSectorAlignSkip(fs);
    }
}
#endif
