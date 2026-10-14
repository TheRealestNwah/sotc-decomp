void setSubParamGazeIKWork(char *p, int a)
{
    char *w = *(char **)(p + 0x110C);

    if (w != 0) {
        *(int *)(w + 0xBC) = a;
    }
}
