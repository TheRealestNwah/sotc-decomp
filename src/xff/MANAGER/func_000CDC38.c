typedef struct {
    char created[8];
    char modified[8];
    unsigned int size;
    unsigned short attr;
    unsigned short reserve1;
    unsigned int reserve2;
    unsigned int pdaAplNo;
    unsigned char name[24];
} McDirEntry;

typedef struct {
    char name[0x88] __attribute__((aligned(8)));
    char name2[0x10] __attribute__((aligned(8)));
} McSaveSlot;

typedef struct {
    char pad0[0xD8];
    McSaveSlot slot[1];
} McSaveData;

typedef struct {
    int pad0;
    int port;
    int slot;
    char pad0C[8];
    int index;
    char pad18[0x10];
    McSaveData *data;
    int result;
} McWork;

extern void *memcpy(void *, const void *, unsigned int);
extern const char RO_00140D30[];
extern const long long RO_00140D48[];
extern const char RO_00140D58[];
extern const char RO_00140D70[];
extern void *memset(void *, int, unsigned int);
extern int iosMcChDir(int, int, const char *);
extern int iosMcGetDir(int, int, const char *, unsigned int, int, McDirEntry *, int *);
extern int iosMcWriteFile(int, int, const char *, void *, int, int);

#ifdef NONMATCHING
/* 22 diffs: slot pointer and file offset swap s0/s1 */
static void func_000CDC38(McWork *w)
{
    int port = w->port;
    int slot = w->slot;
    int count;
    int n = 0x12;
    McDirEntry list[n];
    McSaveSlot *s;
    const char *file;
    int offset;

    w->result = iosMcGetDir(port, slot, RO_00140D70, 0, n, list, &count);
    if (w->result != 0)
        return;
    w->result = iosMcChDir(port, slot, RO_00140D30);
    if (w->result != 0)
        return;
    file = RO_00140D58;
    s = &w->data->slot[w->index];
    offset = w->index * 0x5800 + 0x800;
    memset(s, 0, sizeof(McSaveSlot));
    memcpy(s->name2, RO_00140D48, 10);
    memcpy(s->name, RO_00140D48, 10);
    w->result = iosMcWriteFile(port, slot, file, s, offset, sizeof(McSaveSlot));
    if (w->result != 0)
        return;
    w->result = 0;
}
#endif
