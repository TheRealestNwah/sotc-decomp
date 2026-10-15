extern void T_00031438(void *, int, int, void *);

int GetMotionRootDirInfoIntFrame(void *m, short *r, void *out)
{
    int d;
    if (r[0] >= 4) {
        d = *(int *)((char *)r + 0x24);
        if (d != 0) {
            T_00031438(m, *(int *)((char *)r + 0x20), d, out);
            return 1;
        }
    }
    return 0;
}
