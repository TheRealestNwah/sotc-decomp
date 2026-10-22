extern unsigned char rootPtn[];
extern int D_001360C0;
extern int *D_001360B8;
extern int **D_001360BC;
extern void *iosMallocAlign(void *, int, int);

void modelInit(int count)
{
    D_001360C0 = count;
    D_001360B8 = iosMallocAlign(rootPtn, count * 4, 16);
    D_001360BC = iosMallocAlign(rootPtn, D_001360C0 * 4, 16);
}

