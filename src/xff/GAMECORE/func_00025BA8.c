/* Parked: 3 diffs. Everything matches except the two loads after the def pointer: the original loads entries (0x10) first and count (0xC) in the iosMallocAlign delay slot; gcc swaps them. Staff-roll layout pass: sums heights by entry type. */
#ifdef NONMATCHING
extern void *DldSysUndefSymbol;
extern char SH_StaffRollDefDEFAULT[];
extern char rootPtn[];
extern int D_0017A824;
extern float D_0017A834;
extern float D_0017A838;
extern float D_0017A83C;
extern void *iosMallocAlign(int, int, int);
extern void iosFree(void *);
extern int iosSPrintf(char *, const char *, ...);
extern int sscanf(const char *, const char *, ...);
extern unsigned int strlen(const char *);
extern int getDrawScreenHeight(void);

typedef struct {
    int type;
    char *name;
} StaffEntry;

typedef struct {
    char pad[0xC];
    int count;
    StaffEntry *entries;
} StaffDef;

int func_00025BA8(void)
{
    StaffDef *def = (StaffDef *)((void *)DldSysUndefSymbol == (void *)SH_StaffRollDefDEFAULT ? 0 : SH_StaffRollDefDEFAULT);
    StaffEntry *e;
    int count;
    int total = 0;
    int i = 0;
    int v = 0;
    unsigned char *buf;

    e = def->entries;
    count = def->count;
    buf = (unsigned char *)iosMallocAlign((int)rootPtn, 0x400, 0x10);
    for (; i < count; i++, e++) {
        unsigned int j;
        iosSPrintf((char *)buf, "%s", e->name);
        for (j = 0; j < strlen((char *)buf); j++) {
            if (buf[j] == '_')
                buf[j] = ' ';
        }
        switch (e->type) {
        case 0:
        case 2:
        case 4:
        case 10:
        case 11:
        case 12:
        case 14:
            break;
        case 15:
            sscanf((char *)buf, "%f", &D_0017A83C);
            break;
        case 16:
            sscanf((char *)buf, "%f", &D_0017A834);
            break;
        case 17:
            sscanf((char *)buf, "%f", &D_0017A838);
            break;
        case 13:
            sscanf((char *)buf, "%d", &D_0017A824);
            break;
        case 7:
            sscanf((char *)buf, "%d", &v);
            total += v << 4;
            break;
        case 6:
            sscanf((char *)buf, "%d", &v);
            total += (D_0017A824 * v) << 4;
            break;
        case 8:
            sscanf((char *)buf, "%d", &v);
            total += (getDrawScreenHeight() << 4) * v;
            break;
        case 9:
            sscanf((char *)buf, "%d", &v);
            total += (getDrawScreenHeight() << 3) * v;
            break;
        case 1:
        case 3:
        case 5:
            total += D_0017A824 << 4;
            break;
        }
    }
    iosFree(buf);
    return total;
}
#endif
