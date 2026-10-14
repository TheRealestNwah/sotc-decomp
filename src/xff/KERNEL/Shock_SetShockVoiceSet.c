typedef struct { unsigned int n; int *v; } ShockTab;
extern ShockTab *D_000408F8;
int Shock_SetShockVoiceSet(unsigned int i, int v)
{
    int r = -1;
    if (i < D_000408F8->n) {
        D_000408F8->v[i] = v;
        r = i;
    }
    return r;
}
