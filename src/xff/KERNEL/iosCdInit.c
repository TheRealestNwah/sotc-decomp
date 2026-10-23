typedef struct {
    unsigned char a;
    unsigned char b;
    unsigned char c;
    unsigned char pad[5];
} CdState;

extern CdState B_00046540;
extern CdState B_00046548;
extern CdState *B_0004654C;
extern CdState *B_00046550;
extern int sceCdInit(int mode);
extern int sceCdMmode(int mode);

void iosCdInit(void)
{
    sceCdInit(0);
    sceCdMmode(2);
    B_00046540.a = 0;
    B_00046540.b = 1;
    B_00046540.c = 0;
    B_00046548.a = 0;
    B_00046548.c = 0;
    B_0004654C = B_00046550 = &B_00046540;
}
