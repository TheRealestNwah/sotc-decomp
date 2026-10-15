extern void iosJumpRecoverPoint(const char *);

int getEditWorkSize(int *p)
{
    if (p != 0) {
        if (p[0] == 0x53494442)
            return p[1];
        iosJumpRecoverPoint("edit Work Error!!\n");
    }
    return 0;
}
