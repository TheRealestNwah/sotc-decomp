typedef struct {
    char created[8];
    char modified[8];
    unsigned int size;
    unsigned short attr;
    unsigned short reserve1;
    unsigned int reserve2;
    unsigned int pdaAplNo;
    unsigned char name[32];
} McDirEntry;

typedef struct {
    int pad0;
    int port;
    int slot;
    char *path;
    char pad10[8];
    unsigned int size;
    char pad1C[0x10];
    int result;
} McWork;

extern unsigned int strlen(const char *);
extern char *strcpy(char *, const char *);
extern char *strrchr(const char *, int);
extern int iosMcMkDir(int, int, const char *);
extern int iosMcCreateFile(int, int, const char *);
extern int iosMcGetDir(int, int, const char *, unsigned int, int, McDirEntry *, int *);

static void func_000CDD98(McWork *w)
{
    McDirEntry entry;
    int count;

    {
        char dir[strlen(w->path) + 1];
        char *slash;

        strcpy(dir, w->path);
        slash = strrchr(dir, '/');
        if (slash) {
            *slash = 0;
            iosMcMkDir(w->port, w->slot, dir);
        }
        w->result = iosMcCreateFile(w->port, w->slot, w->path);
        iosMcGetDir(w->port, w->slot, w->path, 0, 1, &entry, &count);
    }
    w->size = count == 1 ? entry.size : 0;
}
