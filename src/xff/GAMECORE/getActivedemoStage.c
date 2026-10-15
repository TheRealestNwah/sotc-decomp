extern unsigned char activedemoInfo[];

int getActivedemoStage(void)
{
    return (*(int *)((char *)(activedemoInfo) + 8));
}
