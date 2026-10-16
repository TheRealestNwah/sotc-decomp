extern void isysDeleteGroupAllObj(void *);
extern void iosFree(void *);

void FlushJudgeVolumeClassImmediate(int *v)
{
    int n;
    char *g = (char *)v[1];

    if (v[0] > 0) {
        n = v[0];
        do {
            isysDeleteGroupAllObj(g);
            g += 4;
        } while (--n);
    }
    if (v[1] != 0) {
        iosFree((void *)v[1]);
        v[1] = 0;
        v[0] = 0;
    }
}
