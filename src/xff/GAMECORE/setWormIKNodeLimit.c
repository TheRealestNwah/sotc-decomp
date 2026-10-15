void setWormIKNodeLimit(char *w, float limit)
{
    int i;
    char *p = w + 0x9F0;

    for (i = 31; i >= 0; i--) {
        *(float *)p = limit;
        p -= 0x50;
    }
}
