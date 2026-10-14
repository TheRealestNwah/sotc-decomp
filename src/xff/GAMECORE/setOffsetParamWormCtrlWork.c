extern void *GetLayoutClass(void *);

void setOffsetParamWormCtrlWork(void *actor, void *work, int mode, float first, float second)
{
    if (*(int *)((char *)work + 0xBC) != 4) {
        *(float *)((char *)work + 0xCC) =
            *(float *)((char *)*(void **)((char *)GetLayoutClass(actor) + 0x134) + 4);
    }
    *(float *)((char *)work + 0xC4) = second;
    *(int *)((char *)work + 0xBC) = mode;
    *(float *)((char *)work + 0xC0) = first;
    *(int *)((char *)work + 0xC8) = 0;
}
