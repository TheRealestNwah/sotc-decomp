typedef struct { int a, b; } Flags;
extern int charrootdyn_slidecollisionCB(void *, void *, void *, void *, void *, void *, void *, Flags *);
extern int charrootdyn_slideExceptionJudgeCB();

int charrootdyn_slidecollision(void *a, void *b, void *c, void *d, void *e, void *f, char *o)
{
    Flags fl;
    if (o != 0) {
        fl.a = (*(unsigned int *)(o + 0x68) >> 11) & 1;
        fl.b = (*(unsigned int *)(o + 0x68) >> 15) & 1;
        return charrootdyn_slidecollisionCB(a, b, c, d, e, f, charrootdyn_slideExceptionJudgeCB, &fl);
    }
    return charrootdyn_slidecollisionCB(a, b, c, d, e, f, o, 0);
}
