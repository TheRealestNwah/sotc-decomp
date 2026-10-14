extern int **D_001360BC;
extern void iosDlChainTail(int, int *);

void modelResetLayer(int i)
{
    int *l = D_001360BC[i];
    if (l != 0)
        iosDlChainTail(i, l);
}
