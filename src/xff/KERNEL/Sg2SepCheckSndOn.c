typedef struct { int mod; char pad[0x4C]; } Sg2Sep;
extern Sg2Sep B_000DD710[];
extern int Sg2ModCheckSndOn(int);

int Sg2SepCheckSndOn(unsigned int i)
{
    if (i < 32)
        Sg2ModCheckSndOn(B_000DD710[i].mod);
    return 0;
}
