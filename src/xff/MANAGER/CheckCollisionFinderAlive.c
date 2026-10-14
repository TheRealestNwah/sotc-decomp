int CheckCollisionFinderAlive(char *p)
{
    if (*(int *)(p + 0xC) == 0) {
        goto no;
    }
    if (*(int *)(p + 0x10) == 0) {
        goto no;
    }
    return 1;
no:
    return 0;
}
