typedef struct {
    int type;
} AdpcmPackage;

extern AdpcmPackage *B_00188890[];
extern AdpcmPackage *B_001888A0[];
extern AdpcmPackage *B_001888B0[];
extern AdpcmPackage *B_001888B8[];
extern int B_001888E0;

static inline void addPackage(AdpcmPackage **tbl, int n, AdpcmPackage *p)
{
    int i;
    for (i = 0; i < n; i++) {
        if (tbl[i] == 0) {
            tbl[i] = p;
            return;
        }
    }
    __asm__ __volatile__("break 0");
}

void initAdpcmPackage(char *a)
{
    AdpcmPackage *p = *(AdpcmPackage **)(a + 0x10);

    switch (p->type) {
    case 0:
        addPackage(B_00188890, 4, p);
        break;
    case 1:
        addPackage(B_001888B0, 1, p);
        B_001888E0 = 0;
        break;
    case 2:
        addPackage(B_001888A0, 4, p);
        break;
    case 3:
        addPackage(B_001888B8, 5, p);
        break;
    }
}
