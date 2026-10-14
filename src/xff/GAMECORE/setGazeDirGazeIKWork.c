typedef int s128 __attribute__((mode(TI)));

void setGazeDirGazeIKWork(char *p, s128 *v)
{
    char *w = *(char **)(p + 0x110C);

    if (w != 0) {
        *(s128 *)(w + 0x50) = *v;
    }
}
