extern char B_00149AB0[], B_00149BF0[];
extern char *g_asWindEffectDataName[50];
extern char D_00137638[];
extern void *memset(void *, int, unsigned int);

void init_wind_manager(void)
{
    int i;
    char **p;
    memset(B_00149AB0, 0, 0x140);
    memset(B_00149BF0, 0, 0xC8);
    p = g_asWindEffectDataName;
    for (i = 49; i >= 0; i--)
        p[i] = D_00137638;
}
