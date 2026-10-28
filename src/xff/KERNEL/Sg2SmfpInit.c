typedef struct {
    int status;
    char pad[0x7C];
} Smfp;

extern Smfp B_000E0DC0[];
extern int B_000E11C4, B_000E21E0, B_000E11C8;
extern void *memset(void *p, int c, unsigned int n);
extern void Sg2SmfpTickProc(void);
extern int Sg2CtrlEntryTickProcById(int id, void (*proc)(void));

int Sg2SmfpInit(int reserved)
{
    Smfp *s = B_000E0DC0;
    int i;

    for (i = 7; i >= 0; i--) {
        memset(s, -1, 0x80);
        s->status = 0;
        s++;
    }
    B_000E11C4 = 1;
    B_000E21E0 = 0;
    B_000E11C8 = 0;
    Sg2CtrlEntryTickProcById(0, Sg2SmfpTickProc);
    return 0;
}
