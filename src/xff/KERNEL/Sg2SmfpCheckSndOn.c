typedef struct { int mod; char pad[0x7C]; } Sg2Smfp;
extern Sg2Smfp B_000E0DC8[];
extern int Sg2ModCheckSndOn(int);

int Sg2SmfpCheckSndOn(int i)
{
    if (i >= 0)
        return Sg2ModCheckSndOn(B_000E0DC8[i].mod);
    return 0;
}
