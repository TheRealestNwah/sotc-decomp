typedef struct {
    long v[8];
} Boundary;

extern int D_0017A890;
extern Boundary D_0017A8A0;
extern Boundary D_0017A8E0;
extern Boundary RO_0017CE40;

void PauseStageBoundaryManager(int pause)
{
    D_0017A890 = pause;
    if (pause == 0) {
        D_0017A8A0 = RO_0017CE40;
        D_0017A8E0 = RO_0017CE40;
    }
}
