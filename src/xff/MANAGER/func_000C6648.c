extern float B_00149A84;

static void func_000C6648(char *out, char *a, char *b)
{
    switch (*(unsigned int *)(b + 0xC8)) {
    case 0:
        break;
    case 1:
        *(float *)(out + 4) = *(float *)(a + 0x14C);
        break;
    case 2:
        *(float *)(out + 4) = B_00149A84;
        break;
    }
}
