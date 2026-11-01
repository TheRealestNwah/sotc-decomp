extern int func_000599B8(void *, void *, void *, void *, void *, float, float, void *);
extern void *func_00059EA0(void *, void *);

int charrootdyn_detectCharClimbableWall(char *p, void *a, void *b, void *c, void *d, void *e, float x, float y, float r, float h)
{
    int found;
    void *other;
    *(float *)(p + 0x38) = y;
    *(float *)(p + 0x3C) = x;
    *(int *)(p + 0x20) = 0;
    *(int *)(p + 0x80) = 0;
    *(int *)(p + 0x8C) = 0;
    found = func_000599B8(p, a, b, c, d, r, h, e);
    if (found == 0) {
        other = func_00059EA0(a, e);
        if (other != 0)
            found = func_000599B8(p, other, b, c, d, r, h, e);
    }
    return found;
}
