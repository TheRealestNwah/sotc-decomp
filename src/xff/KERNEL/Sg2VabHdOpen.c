typedef struct {
    int alive;
    int a, b, c, d;
    int *hd;
    char pad[0x14];
} Vab;

extern Vab B_000E2200[];
extern int DIntr(void);
extern void EIntr(void);
extern int get_vabid(void);
extern int func_0002D5A8(Vab *v, void *hd);

int Sg2VabHdOpen(void *hd)
{
    int intr = DIntr();
    int id = get_vabid();
    int r = func_0002D5A8(&B_000E2200[id], hd) != -1 ? id : -1;

    if (intr != 0) {
        EIntr();
    }
    return r;
}
