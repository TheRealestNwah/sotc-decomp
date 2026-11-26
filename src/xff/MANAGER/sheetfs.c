/* Sheet file system: finds files on the disc through the segment, map and
 * special-file tables, or through an override sheet when one is set. */

typedef struct {
    signed char type;
    char pad[3];
    short id;
    short pad2;
    int value[2];
} SheetEntry;

typedef struct {
    int pad;
    int count;
    SheetEntry *entries;
} Sheet;

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

typedef struct {
    char *name;
    char pad4[0xC];
    int *tab[6];
} MapEntry;

typedef struct {
    int count;
    MapEntry *entries;
} MapList;

typedef struct {
    int offset;
    int size;
} FileEntry;

typedef struct { const char *name; char unknown[8]; } SpecialFile;
typedef struct { int count; SpecialFile *entries; } SpecialFiles;

extern int D_00139F04;
extern int B_001517D8;
extern char *B_001517E0;
extern MapList B_001517E8;
extern int *B_001517F4;
extern FileEntry *B_001517FC;
extern SpecialFiles B_00151800;
extern int sheetFsLanguageCode;

extern int strcmp(const char *, const char *);
extern int memcmp(const void *, const void *, unsigned int);
extern void iosCdStStart(int);
extern void iosCdStStop(void);
extern void iosCdSetMode(int mode);
extern void iosIopRead(int, int, int);
extern void iosJumpRecoverPoint(const char *, ...);

static int func_000E1030(Sheet *sheet, SheetEntry *key);

static const char RO_001419E0[] = "stagetexseg_def";

/* Streams entry idx of the named segment table to cb. */
static inline void loadSeg(char *name, int idx, void (*cb)(int, int))
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
        tag = *(Tag6 *)"stage";
        req.idx = idx;
        if (strcmp((char *)&tag, name) == 0)
            req.flag = 0;
        else
            req.flag = 1;
        pos = func_000E1030((Sheet *)D_00139F04, (SheetEntry *)&req);
    }
    if (pos < 0) {
        int i = 0;
        e = 0;
        for (; i < B_001517D8; i++) {
            e = &((SegEntry *)B_001517E0)[i];
            if (strcmp(name, e->name) == 0)
                goto found;
        }
        iosJumpRecoverPoint("sheetFsLoadSegmentIndex: %s not foune", name);
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
        tag = *(Tag6 *)"stage";
        req.idx = idx;
        if (strcmp((char *)&tag, name) == 0)
            req.flag = 0;
        else
            req.flag = 1;
        pos = func_000E1030((Sheet *)D_00139F04, (SheetEntry *)&req);
    }
    if (pos < 0) {
        int i = 0;
        e = 0;
        for (; i < B_001517D8; i++) {
            e = &((SegEntry *)B_001517E0)[i];
            if (strcmp(name, e->name) == 0)
                goto found;
        }
        iosJumpRecoverPoint("sheetFsLoadSegmentIndex: %s not foune", name);
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

void sheetFsLoadMap(char *name, int dataType, int blockType, int idx, int e, void (*cb)(int, int))
{
    struct {
        char flag;
        char dataType;
        char blockType;
        char e;
        char pad4[2];
        short idx;
    } req;
    int pos = -1;
    MapEntry *ent = 0;
    int *tab = 0;

    if (D_00139F04 != 0) {
        req.flag = 2;
        req.e = e;
        req.dataType = dataType;
        req.blockType = blockType;
        req.idx = idx;
        pos = func_000E1030((Sheet *)D_00139F04, (SheetEntry *)&req);
    }
    if (pos < 0) {
        int i;
        for (i = 0; i < B_001517E8.count; i++) {
            ent = &B_001517E8.entries[i];
            if (strcmp(name, ent->name) == 0)
                goto found;
        }
        iosJumpRecoverPoint("sheetFsLoadMap:world name %s not found\n", name);
    found:
        if (dataType == 2 && blockType == 0)
            tab = ent->tab[0];
        else if (dataType == 2 && blockType == 1)
            tab = ent->tab[1];
        else if (dataType == 1 && blockType == 0)
            tab = ent->tab[2];
        else if (dataType == 1 && blockType == 1)
            tab = ent->tab[3];
        else if (dataType == 0 && blockType == 0)
            tab = ent->tab[4];
        else if (dataType == 0 && blockType == 1)
            tab = ent->tab[5];
        else
            iosJumpRecoverPoint("sheetFsLoadMap:world name %s param error dataType:%d blockType:%d\n", name, dataType, blockType);
        pos = tab[idx * 2];
    }
    iosCdStStart(pos);
    cb(0, 0);
    iosCdStStop();
}

static const char RO_00141A90[] = "DEFAULT";

void sheetFsLoadStageTex(int idx, void (*cb)(int, int))
{
    loadSeg((char *)RO_001419E0, idx, cb);
}

void sheetFsLoadAdpcmInt(int a, int i, int off, int buf, int size)
{
    int *t = B_001517F4 + i * 2;
    iosIopRead(*t + off, buf, size);
}

int sheetFsGetDirectFileSize(int i)
{
    return *(int *)((char *)B_001517FC + (i << 3) + 4);
}

SpecialFile *sheetFsSrhSpecialFs(const char *name)
{
    int i = 0;
    if (B_00151800.count > 0) {
        int offset = 0;
        do {
            SpecialFile *entry = (SpecialFile *)((char *)B_00151800.entries + offset);
            offset += sizeof(SpecialFile);
            if (strcmp(entry->name, name) == 0) return entry;
        } while (++i < B_00151800.count);
    }
    return 0;
}

void sheetFsSetSpecialFs(int fs, int mode)
{
    D_00139F04 = fs;
    iosCdSetMode(fs != 0 && mode != 0);
}

/* Looks a request up in the override sheet; returns the disc position or -1. */
static int func_000E1030(Sheet *sheet, SheetEntry *key)
{
    SheetEntry *e = sheet->entries;
    int i;

    for (i = 0; i < sheet->count; i++, e++) {
        signed char t = e->type;

        if (key->type != t)
            continue;
        switch (key->type) {
        case 0:
        case 1:
            if (key->id == e->id)
                goto found;
            break;
        case 3:
        case 4:
            if (key->id == e->id)
                goto found_lang;
            break;
        case 2:
            key->id = 0;
            if (memcmp(key, e, 8) == 0)
                goto found;
            break;
        }
    }
    return -1;
found:
    return e->value[0];
found_lang:
    return e->value[sheetFsLanguageCode * 2];
}
