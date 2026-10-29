extern int D_00136CC0[];
extern int D_00136C88[];

void objectmanager_mallocerrorfunc(void)
{
    int i;

    if (D_00136CC0[0]) {
        for (i = 0; i < 14; i++) {
            /* Unused quotient: only the divide-by-zero trap survives. */
            int t = 1 / D_00136C88[i];
        }
    }
}
