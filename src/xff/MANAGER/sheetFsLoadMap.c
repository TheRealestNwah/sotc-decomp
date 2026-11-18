extern int D_00139F04;
extern int strcmp(const char *, const char *);
extern int func_000E1030(int, void *);
extern void iosCdStStart(int);
extern void iosCdStStop(void);
extern void iosJumpRecoverPoint(const char *, ...);

typedef struct {
    char *name;
    char pad4[0xC];
    int *tab[6];
} MapEntry;

typedef struct {
    int count;
    MapEntry *entries;
} MapList;

extern MapList B_001517E8;

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
        pos = func_000E1030(D_00139F04, &req);
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
