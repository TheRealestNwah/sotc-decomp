extern char padManagerData[];

int demoscrCheckDemoFinish(void)
{
    if (*(int *)(padManagerData + 0x8) & 0x800) {
        return 1;
    }
    return 0;
}
