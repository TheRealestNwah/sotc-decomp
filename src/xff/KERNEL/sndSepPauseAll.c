extern int D_00040FAC;

void sndSepPauseAll(int arg0)
{
    if (arg0 != 0) {
        D_00040FAC = 1;
        return;
    }
    D_00040FAC = 0;
}
