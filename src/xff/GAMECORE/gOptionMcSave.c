typedef struct {
    char pad0[0x20];
    int port;
    int slot;
    int reserved;
    int offset;
    int used;
} McFile;

extern char B_00183E68[];
extern int mcWrite(McFile *, void *, int);
int gOptionMcSave(McFile *file, int b, int c, int d)
{
    return mcWrite(file, B_00183E68, 136);
}
