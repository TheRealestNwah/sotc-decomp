extern int activedemoInfo[];

void activeDemoCancel(int id)
{
    int *d = activedemoInfo;

    if (d[3] != 0 && d[2] == id) {
        d[0] |= 4;
    }
}
