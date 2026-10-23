typedef struct {
    char pad[0xE];
    unsigned short next;
    char pad2[8];
} SysGroup;

extern SysGroup B_0006D640[];

SysGroup *isysGetGroupSrhNext(SysGroup *g)
{
    return g->next ? &B_0006D640[g->next] : 0;
}
