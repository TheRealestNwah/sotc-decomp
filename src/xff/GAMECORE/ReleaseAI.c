extern char gcGlobalVar[];

void ReleaseAI(void)
{
    *(int *)(gcGlobalVar + 0x310) = 0;
}
