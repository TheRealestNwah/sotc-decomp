extern int T_00031438(void *, int, int, int);

int GetMotionNodeIntFrameDirectResource(void *a, char *n, int i, int d)
{
    return T_00031438(a, *(unsigned char *)(*(char **)(n + 8) + i), (*(int **)(n + 0x10))[i], d);
}
