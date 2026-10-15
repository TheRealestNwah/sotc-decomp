typedef struct { int a; int col; int b; int cluster; } ResMan;
extern ResMan B_001498C0;
extern int IsClusterCollision(int);
extern int sheetFileGetSize(void *);
extern void isysRequestDeleteObj(void *);

void unloadCdColResFile(void *f, int b, char *o)
{
    if (IsClusterCollision(*(int *)(o + 0x20)))
        B_001498C0.col -= sheetFileGetSize(f);
    else
        B_001498C0.cluster -= sheetFileGetSize(f);
    isysRequestDeleteObj(o);
}
