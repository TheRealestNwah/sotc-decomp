extern unsigned char activedemoInfo[1];

int getActivedemoStage(void)
{
    return (*(int *)((char *)(&activedemoInfo) + 8));
}
