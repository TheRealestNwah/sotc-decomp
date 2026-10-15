extern void T_00031438(void *, int, int, void *);

int GetMotionGazeDirInfoIntFrame(void *m, short *r, void *out)
{
    int d;
    if (r[0] >= 9) {
        d = *(int *)((char *)r + 0x3C);
        if (d != 0) {
            T_00031438(m, *(int *)((char *)r + 0x38), d, out);
            return 1;
        }
    }
    return 0;
}
