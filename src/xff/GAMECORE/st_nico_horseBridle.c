extern void *GetLayoutClass(int);
extern int isysGetThisSubThread();
extern void isysJumpSubThread(void *, int);
extern void nico_setHorseBridleObjToHorseWork(int, int);
extern unsigned char st_collisionalias[1];

void st_nico_horseBridle(int arg0)
{
    int temp_v0;

    temp_v0 = isysGetThisSubThread();
    nico_setHorseBridleObjToHorseWork((*(int *)((char *)(GetLayoutClass(temp_v0)) + 0x194)), temp_v0);
    isysJumpSubThread(&st_collisionalias, arg0);
}
