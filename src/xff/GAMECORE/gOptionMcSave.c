extern char B_00183E68[];
extern int mcWrite();

int gOptionMcSave(int a, int b, int c, int d)
{
    return mcWrite(a, (int)B_00183E68, 136, d);
}
