void *getEditWorkDebugData(char *work)
{
    if (work != 0) {
        int ofs = *(int *)(work + 0xC);

        if (ofs != 0) {
            return work + ofs + 0x20;
        }
    }
    return 0;
}
