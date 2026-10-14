extern int B_00149928[];

void resetMicroCodeManager(void)
{
    int i;
    for (i = 0; i < 32; i++)
        B_00149928[i] = 0xD;
}
