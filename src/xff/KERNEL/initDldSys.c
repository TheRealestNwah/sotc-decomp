typedef struct { int id; int p; } Dld;
extern Dld B_000543A8[];

void initDldSys(void)
{
    int i;
    for (i = 0; i < 8; i++)
        B_000543A8[i].id = -1;
}
