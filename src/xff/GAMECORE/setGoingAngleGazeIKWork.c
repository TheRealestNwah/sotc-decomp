void setGoingAngleGazeIKWork(char *p, float a)
{
    char *w = *(char **)(p + 0x110C);

    if (w != 0) {
        *(float *)(w + 0x40) = a;
    }
}
