extern void Sg2SepVabStopSndOff(int);
extern void Sg2SmfpVabStopSndOff(int);
extern int Sg2VabHdClose(int);
extern int vab_check_alive(int);

int Sg2VabClose(int arg0)
{
    if (vab_check_alive(arg0) == 0) {
        return -1;
    }
    Sg2SmfpVabStopSndOff(arg0);
    Sg2SepVabStopSndOff(arg0);
    return Sg2VabHdClose(arg0);
}
