extern char B_000E0DD0[];
extern int dptoli(long);
int Sg2SmfpGetParam(int id, int param)
{
    /* Unsupported selectors retain the original unspecified result. */
    int result;
    if (id >= 0) {
        switch (param) {
        case 2:
            result = *(int *)(B_000E0DD0 + id * 0x80);
            break;
        case 4:
            result = *(int *)(B_000E0DD0 + id * 0x80 + 8);
            break;
        case 8:
            result = *(int *)(B_000E0DD0 + id * 0x80 + 0xC);
            break;
        case 0x200:
            result = dptoli(*(long *)(B_000E0DD0 + id * 0x80 + 0x20));
            break;
        }
    } else {
        result = 0;
    }
    return result;
}