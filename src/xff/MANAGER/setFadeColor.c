extern int D_00130430[3];

void setFadeColor(int color)
{
    if (color != 0) {
        if (color == 1) {
            D_00130430[0] = 200;
            D_00130430[1] = 200;
            D_00130430[2] = 200;
        }
    } else {
        D_00130430[0] = 0;
        D_00130430[1] = 0;
        D_00130430[2] = 0;
    }
}
