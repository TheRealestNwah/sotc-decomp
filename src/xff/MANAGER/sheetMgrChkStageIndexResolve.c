extern unsigned char *B_0015D4A8;
int sheetMgrChkStageIndexResolve(int i)
{
    return (B_0015D4A8[i / 8] >> (i & 7)) & 1;
}
