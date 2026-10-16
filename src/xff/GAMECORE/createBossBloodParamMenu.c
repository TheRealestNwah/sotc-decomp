extern int D_0017AB70[];
extern void createParamMenu(void *, int);

void createBossBloodParamMenu(void)
{
    if (D_0017AB70[12] == 0)
        createParamMenu(D_0017AB70, 0);
}
