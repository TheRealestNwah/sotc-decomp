int GetObjectAnimationParentNodeId(char *p, int i)
{
    int *t = *(int **)(p + 0x8);

    if (t == 0) {
        return -1;
    }
    return t[i];
}
