static int func_000C5D48(char *a, char *b)
{
    switch (*(unsigned int *)(b + 0x15C)) {
    case 0:
        *(float *)(a + 0x150) = 10000000.0f;
        break;
    case 1:
        *(float *)(a + 0x150) = *(float *)(b + 0xB4);
        break;
    case 2:
        *(float *)(a + 0x150) = *(float *)(b + 0xB4) + *(float *)(a + 0x14);
        break;
    default:
        *(float *)(a + 0x150) = *(float *)(b + 0xB4) + *(float *)(a + 0x14C);
        break;
    }
    switch (*(unsigned int *)(b + 0x160)) {
    case 0:
        *(float *)(a + 0x154) = -10000000.0f;
        break;
    case 1:
        *(float *)(a + 0x154) = *(float *)(b + 0x140);
        break;
    case 2:
        *(float *)(a + 0x154) = *(float *)(b + 0x140) + *(float *)(a + 0x14);
        break;
    default:
        *(float *)(a + 0x154) = *(float *)(b + 0x140) + *(float *)(a + 0x14C);
        break;
    }
    return 1;
}
