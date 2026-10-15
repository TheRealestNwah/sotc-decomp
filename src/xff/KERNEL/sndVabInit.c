typedef struct { unsigned int flags; char pad[0x18]; } Vab;
extern Vab B_000C3718[];
void sndVabInit(void)
{
    int i;
    for (i = 0; i < 20; i++)
        B_000C3718[i].flags &= ~1;
}
