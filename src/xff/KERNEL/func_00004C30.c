typedef struct {
    int cid;
    unsigned int *buf;
    char client[0x3C];
} NetConn;
extern NetConn B_000508B0[];
extern int sceInetClose(void *, unsigned int *, int, int);
extern int sceLibnetTerminate(void *);
extern void iosFree(void *);

static int func_00004C30(int handle, int ms)
{
    sceInetClose(B_000508B0[handle].client, B_000508B0[handle].buf, B_000508B0[handle].cid, ms);
    B_000508B0[handle].cid = -1;
    sceLibnetTerminate(B_000508B0[handle].client);
    iosFree(B_000508B0[handle].buf);
    B_000508B0[handle].buf = 0;
    return 1;
}
