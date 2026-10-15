extern char *GetSubLinkClass(void *);
extern void sndSepCont(int);
extern void sndSepPause(int);

void seSetKeyOnOff(void *obj, int on)
{
    int se = **(int **)(GetSubLinkClass(obj) + 0x10);
    if (on != 0)
        sndSepCont(se);
    else
        sndSepPause(se);
}
