typedef struct {
    int type;
} AdpcmPackage;

extern AdpcmPackage *B_00188890[];
extern AdpcmPackage *B_001888A0[];
extern AdpcmPackage *B_001888B0[];
extern AdpcmPackage *B_001888B8[];

static inline void removePackage(AdpcmPackage **tbl, int n, AdpcmPackage *p)
{
    int i;
    for (i = 0; i < n; i++) {
        if (tbl[i] == p) {
            tbl[i] = 0;
            return;
        }
    }
    __asm__ __volatile__("break 0");
}

void deleteAdpcmPackage(char *a)
{
    AdpcmPackage *p = *(AdpcmPackage **)(a + 0x10);

    switch (p->type) {
    case 0:
        removePackage(B_00188890, 4, p);
        break;
    case 1:
        removePackage(B_001888B0, 1, p);
        break;
    case 2:
        removePackage(B_001888A0, 4, p);
        break;
    case 3:
        removePackage(B_001888B8, 5, p);
        break;
    }
}
