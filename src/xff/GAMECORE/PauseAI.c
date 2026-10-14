extern char gcGlobalVar[];

void PauseAI(void)
{
    *(int *)(gcGlobalVar + 0x310) = 1;
}
