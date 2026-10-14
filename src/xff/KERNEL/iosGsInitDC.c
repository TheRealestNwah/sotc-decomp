typedef struct { char d[400]; } DC;
extern DC *B_000655D8;
extern int iosDlGetWorkBufId(void);
extern void iosResetDC(DC *);

void iosGsInitDC(void)
{
    iosResetDC(&B_000655D8[iosDlGetWorkBufId()]);
}
