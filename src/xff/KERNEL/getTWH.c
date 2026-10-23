int getTWH(int n)
{
    int r = -1;
    int i;

    for (i = 0; i < 11; i++) {
        if (n <= 1 << i) {
            r = i;
            break;
        }
    }
    if (r <= 0) {
        r = 1;
    }
    return r;
}
