typedef struct { int on; char pad[0x9AC]; } Sg2Mod;
extern Sg2Mod B_000C5C18[];

int Sg2ModCheckSndOn(int i)
{
    if (i >= 0)
        return B_000C5C18[i].on != -1;
    return 0;
}
