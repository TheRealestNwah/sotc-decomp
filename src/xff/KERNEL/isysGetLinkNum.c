typedef struct {
    char pad[0xE];
    unsigned short next;
    char pad2[8];
} SysGroup;

extern SysGroup *B_000BF6C0;
extern SysGroup B_0006D640[];

static inline SysGroup *getNext(SysGroup *g)
{
    return g->next ? &B_0006D640[g->next] : 0;
}

int isysGetLinkNum(void)
{
    SysGroup *g = B_000BF6C0;
    int n = 0;

    while (g != 0) {
        n++;
        g = getNext(g);
    }
    return 0x36B0 - n;
}
