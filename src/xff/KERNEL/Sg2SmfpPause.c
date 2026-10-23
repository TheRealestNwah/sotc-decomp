typedef struct {
    int state;
    int pad4;
    int mod;
    char pad[0x74];
} Smfp;

extern Smfp B_000E0DC0[];
extern int Sg2ModSetParam(int mod, int param, int a, int b);

int Sg2SmfpPause(int handle, int pause)
{
    Smfp *p;

    if (handle >= 0) {
        if (pause) {
            p = (Smfp *)(handle << 7);
            p = (Smfp *)((char *)B_000E0DC0 + (int)p);
            Sg2ModSetParam(p->mod, 0x20, 1, 0);
            p->state = 3;
        } else {
            p = (Smfp *)(handle << 7);
            p = (Smfp *)((char *)B_000E0DC0 + (int)p);
            Sg2ModSetParam(p->mod, 0x40, 1, 0);
            p->state = 4;
        }
    }
    return 0;
}
