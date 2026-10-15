typedef struct { int a; int n; int man[5]; } CameraMen;
extern CameraMen B_0019FD20;

int employ_cameraman(void *m)
{
    int i;
    for (i = 0; i < 5; i++) {
        if (B_0019FD20.man[i] == 0) {
            B_0019FD20.man[i] = (int)m;
            B_0019FD20.n++;
            return i;
        }
    }
    __asm__ __volatile__("break 0");
    return -1;
}
