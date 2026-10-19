typedef struct { char bytes[96]; } FsEffect;
extern FsEffect *FsEffect_DEFAULT;
extern FsEffect B_00147310;
void fsEffectManagerInit(void)
{
    if (FsEffect_DEFAULT)
        B_00147310 = *FsEffect_DEFAULT;
}