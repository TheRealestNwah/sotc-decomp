extern void Sg2VabBdOpen(int, int);
extern int Sg2VabHdOpen(int);

void sndVabHDOpen(void *arg0, int arg1, int arg2)
{
    int temp_a1;
    int temp_v0;

    (*(int *)((char *)(arg0) + 8)) = arg2;
    (*(int *)((char *)(arg0) + 0xC)) = arg1;
    temp_v0 = Sg2VabHdOpen(arg1);
    (*(int *)((char *)(arg0) + 4)) = temp_v0;
    if (temp_v0 >= 0) {
        temp_a1 = (*(int *)((char *)(arg0) + 0x10));
        if (temp_a1 != 0) {
            Sg2VabBdOpen(temp_v0, temp_a1);
        }
    }
}
