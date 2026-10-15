extern void *GetLayoutClass(int);
extern int isysGetThisSubThread();
extern void isysJumpSubThread(void (*entry)(int arg), int arg);
extern void nico_setHorseBridleObjToHorseWork(int, int);
extern void st_collisionalias(int arg);

void st_nico_horseBridle(int arg0)
{
    int temp_v0;

    temp_v0 = isysGetThisSubThread();
    nico_setHorseBridleObjToHorseWork((*(int *)((char *)(GetLayoutClass(temp_v0)) + 0x194)), temp_v0);
    isysJumpSubThread(st_collisionalias, arg0);
}
