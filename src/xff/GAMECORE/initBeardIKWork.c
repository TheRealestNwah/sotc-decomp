void initBeardIKWork(void *a, void *b, char *w)
{
    int i;
    char *p = w + 0x3B0;

    for (i = 9; i >= 0; i--) {
        *(int *)p = 0;
        p -= 0x60;
    }
}
