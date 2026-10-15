typedef struct { int used; char pad[0x6C]; } SndSep;
extern SndSep B_000C2910[];
extern int B_000C3710;
extern int iosCreateSema(int, int, int);

void sndSepInit(void)
{
    int i;
    B_000C3710 = iosCreateSema(1, 1, 0);
    for (i = 31; i >= 0; i--)
        B_000C2910[i].used = 0;
}
