extern void CopyGeometryPointer(char *, int, int, int);
void SetClothSingleFixedChainLeafFixGeometryPointer(char *p, int a, int b, int c)
{
    char *g = p + 0x30;
    g[0x40] = 1;
    CopyGeometryPointer(g, a, b, c);
    g[0x41] = 0;
}
